/*
 * This file is part of the bladeRF project
 *
 * bladeRF command line interface
 * Copyright (C) 2013 Nuand LLC
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <libbladeRF.h>
#include <pthread.h>
#include "input/input.h"
#include "common.h"
#include "board/board.h"
#include "cmd/rxtx_impl.h"
#include <unistd.h>

#include "range.h"
#include "board/bladerf2/common.h"
#include "test_config.h"



/* Runtime configuration items */
struct rc_config {
    bool interactive_mode;
    bool flash_fw;
    bool flash_fpga;
    bool load_fpga;
    bool probe;
    bool show_help;
    bool show_help_interactive;
    bool show_version;
    bool show_lib_version;
    bool reopen_device;

    bladerf_log_level verbosity;

    char *device;
    char *fw_file;
    char *flash_fpga_file;
    char *fpga_file;
    char *script_file;
};

static void init_rc_config(struct rc_config *rc)
{
    rc->interactive_mode      = false;
    rc->flash_fw              = false;
    rc->flash_fpga            = false;
    rc->load_fpga             = false;
    rc->probe                 = false;
    rc->show_help             = false;
    rc->show_help_interactive = false;
    rc->show_version          = false;
    rc->show_lib_version      = false;
    rc->reopen_device         = false;

    rc->verbosity = BLADERF_LOG_LEVEL_INFO;

    rc->device          = NULL;
    rc->fw_file         = NULL;
    rc->flash_fpga_file = NULL;
    rc->fpga_file       = NULL;
    rc->script_file     = NULL;
}

static void deinit_rc_config(struct rc_config *rc)
{
    free(rc->device);
    free(rc->fw_file);
    free(rc->flash_fpga_file);
    free(rc->fpga_file);
    free(rc->script_file);
}


static void print_error_need_devarg()
{
    printf("\nError: Either no devices are present, or multiple devices are\n"
            "        present and -d was not specified. Aborting.\n\n");
}

static int open_device(struct rc_config *rc,
                       struct cli_state *state)
{
    int status = bladerf_open(&state->dev, rc->device);
    return status;
}

static int flash_fw(struct rc_config *rc, struct cli_state *state, int status)
{
    if (!status && rc->fw_file) {
        if (!state->dev) {
            print_error_need_devarg();
            status = -1;
        } else {
            printf("Flashing firmware...\n");
            status = bladerf_flash_firmware(state->dev, rc->fw_file);
            if (status) {
                fprintf(stderr, "Error: failed to flash firmware: %s\n",
                        bladerf_strerror(status));
            } else {
                printf("Successfully wrote firmware to flash!\n");
                printf("NOTE: A power cycle is required to load the new "
                       "firmware.\n");
            }
            bladerf_close(state->dev);
            state->dev = NULL;
        }
    }

    return status;
}

static int flash_fpga(struct rc_config *rc, struct cli_state *state, int status)
{
    if (!status && rc->flash_fpga_file) {
        if (!state->dev) {
            print_error_need_devarg();
            status = -1;
        } else {
            if (!strcmp("X", rc->flash_fpga_file)) {
                printf("Erasing stored FPGA to disable autoloading...\n");
                status = bladerf_erase_stored_fpga(state->dev);
            } else {
                printf("Writing FPGA to flash for autoloading...\n");
                status = bladerf_flash_fpga(state->dev, rc->flash_fpga_file);
            }

            if (status) {
                fprintf(stderr, "Error: %s\n", bladerf_strerror(status));
            } else {
                if (!strcmp("X", rc->flash_fpga_file)) {
                    printf("Successfully erased FPGA bitstream from flash!\n");
                } else {
                    printf("Successfully wrote FPGA bitstream to flash!\n");
                }
            }
        }
    }

    return status;
}

static int load_fpga(struct rc_config *rc, struct cli_state *state, int status)
{
    if (!status && rc->fpga_file) {
        if (!state->dev) {
            print_error_need_devarg();
            status = -1;
        } else {
            printf("Loading fpga...\n");
            status = bladerf_load_fpga(state->dev, rc->fpga_file);
            if (status) {
                fprintf(stderr, "Error: failed to load FPGA: %s\n",
                        bladerf_strerror(status));
            } else {
                printf("Successfully loaded FPGA bitstream!\n");
                /* bladerf_load_fpga does initialization, so we don't need to
                 * re-open the device. */
                rc->reopen_device = false;
            }
        }
    }

    return status;
}

void check_for_bootloader_devs()
{
    int num_devs;
    struct bladerf_devinfo *list;

    num_devs = bladerf_get_bootloader_list(&list);

    if (num_devs <= 0) {
        if (num_devs != BLADERF_ERR_NODEV) {
            fprintf(stderr, "Error: failed to check for bootloader devices.\n");
        }

        return;
    }

    bladerf_free_device_list(list);
    printf("NOTE: One or more FX3-based devices operating in bootloader mode\n"
           "      were detected. Run 'help recover' to view information about\n"
           "      downloading firmware to the device(s).\n\n");
}
static int tx_cmd_start(struct cli_state *s)
{
    int status = 0;

    /* Check that we're able to start up in our current state */
    status = rxtx_cmd_start_check(s, s->tx, "tx");
    if (status != 0) {
        return status;
    }

    /* Perform file conversion (if needed) and open input file */
    MUTEX_LOCK(&s->tx->file_mgmt.file_meta_lock);

    if (s->tx->file_mgmt.format == RXTX_FMT_CSV_SC16Q11) {
        status = tx_csv_to_sc16q11(s);

        if (status == 0) {
            printf("  Converted CSV to SC16 Q11 file and "
                   "switched to converted file.\n\n");
        }
    }

    if (status == 0) {
        MUTEX_LOCK(&s->tx->file_mgmt.file_lock);

        assert(s->tx->file_mgmt.format == RXTX_FMT_BIN_SC16Q11);
        status = expand_and_open(s->tx->file_mgmt.path, "rb",
                                 &s->tx->file_mgmt.file);
        MUTEX_UNLOCK(&s->tx->file_mgmt.file_lock);
    }

    MUTEX_UNLOCK(&s->tx->file_mgmt.file_meta_lock);

    if (status != 0) {
        return status;
    }

    /* Request thread to start running */
    rxtx_submit_request(s->tx, RXTX_TASK_REQ_START);
    status = rxtx_wait_for_state(s->tx, RXTX_STATE_RUNNING, 3000);

    /* This should never occur. If it does, there's likely a defect
     * present in the tx task */
    if (status != 0) {
        cli_err(s, "tx", "TX did not start up in the alloted time\n");
        status = CLI_RET_UNKNOWN;
    }

    return status;
}

static int rx_cmd_start(struct cli_state *s)
{
    int status;

    /* Check that we can start up in our current state */
    status = rxtx_cmd_start_check(s, s->rx, "rx");
    if (status != 0) {
        return status;
    }

    /* Set up output file */
    MUTEX_LOCK(&s->rx->file_mgmt.file_lock);
    if (s->rx->file_mgmt.format == RXTX_FMT_CSV_SC16Q11) {
        status =
            expand_and_open(s->rx->file_mgmt.path, "w", &s->rx->file_mgmt.file);

    } else {
        /* RXTX_FMT_BIN_SC16Q11, open file in binary mode */
        status = expand_and_open(s->rx->file_mgmt.path, "wb",
                                 &s->rx->file_mgmt.file);
    }
    MUTEX_UNLOCK(&s->rx->file_mgmt.file_lock);

    if (status != 0) {
        return status;
    }

    /* Request thread to start running */
    rxtx_submit_request(s->rx, RXTX_TASK_REQ_START);
    status = rxtx_wait_for_state(s->rx, RXTX_STATE_RUNNING, 3000);

    /* This should never occur. If it does, there's likely a defect
     * present in the rx task */
    if (status != 0) {
        cli_err(s, "rx", "RX did not start up in the allotted time.\n");
        status = CLI_RET_UNKNOWN;
    }

    return status;
}

int main(int argc, char *argv[])
{
    int status = 0;
    struct rc_config rc;
    struct cli_state *state;
   
    init_rc_config(&rc);

    rc.verbosity = BLADERF_LOG_LEVEL_SILENT;

    state = cli_state_create();

    bladerf_log_set_verbosity(rc.verbosity);

    check_for_bootloader_devs();

    /* Conditionally performed items, depending on runtime config */
    // =========================================================================
    // OPEN DEVICE
    // =========================================================================
    bladerf_open(&state->dev, rc.device);
    // =========================================================================
    // RX AND TX Threads init
    // =========================================================================
    
    cli_start_tasks(state);


    // =========================================================================
    // GENERAL
    // =========================================================================
    struct bladerf2_board_data *board_data = state->dev->board_data;
    struct ad9361_rf_phy *phy              = board_data->phy;
    // =========================================================================
    // Frequency
    // =========================================================================
    
    bladerf_frequency frequency = FREQ; // 150MHZ

    /* Set up band selection */
    CHECK_STATUS(board_data->rfic->select_band(state->dev, BLADERF_CHANNEL_TX(0), frequency));

    ad9361_set_tx_lo_freq(phy, frequency);
    ad9361_set_rx_lo_freq(phy, FREQ);//950MHZ

    board_data->rfic->set_gain(state->dev, BLADERF_CHANNEL_TX(0),60);
    // =========================================================================
    // Sample Rate
    // 520,834 KHz - 61.440Mhz
    // =========================================================================
    bladerf_sample_rate current;
    bladerf_rfic_rxfir  rxfir;
    bladerf_rfic_txfir  txfir;
    bladerf_sample_rate rate = SAMPLE_RATE; // 10Mhz

    /*Range for interpolation required*/
    int max_range            = 2083334; //2MHZ
    int min_range            = 520834; // 520KHz
    bool old_rate, new_rate;

    /*Check if data doesnt need interpolation*/

    /* Sample rates requiring a 4x interpolation/decimation */
    ad9361_get_tx_sampling_freq(phy, &current);
    
    old_rate = (current >= min_range) && ( current <= max_range);
    new_rate = (rate    >= min_range) && ( rate    <= max_range);
    
    ///* Get current filter status */
    if (old_rate || new_rate) {
        rxfir = board_data->rxfir;
        txfir = board_data->txfir;
    }
    if(new_rate) // check if rfic needs configuration
    {
        if (rxfir != BLADERF_RFIC_RXFIR_DEC4 ||
            txfir != BLADERF_RFIC_TXFIR_INT4) {
            //fpga_common/src/ad936x_params.c:604
            ad9361_set_rx_fir_config(phy,bladerf2_rfic_rx_fir_config_dec4);
            ad9361_set_rx_fir_en_dis(phy, 1);//1 = enable

            ad9361_set_tx_fir_config(phy,bladerf2_rfic_tx_fir_config_int4);
            ad9361_set_tx_fir_en_dis(phy,1);// 1 = enable
        }
    }
    ad9361_set_tx_sampling_freq(phy, rate);        
    ad9361_set_rx_sampling_freq(phy, rate);

    // =========================================================================
    // bandwidth
    // 200000 -- 56000000 bladerf2_bandwidth_range-bladerf2_common.h
    // =========================================================================
    ad9361_set_tx_rf_bandwidth(phy,BANDWIDTH_RX); 
    ad9361_set_rx_rf_bandwidth(phy,BANDWIDHT_TX);
    // =========================================================================
    // RX AGC MODE OFF
    // =========================================================================

    enum rf_gain_ctrl_mode gc_mode;
    gc_mode = RF_GAIN_MGC; // MANUAL GAIN CONTROL
    ad9361_set_rx_gain_control_mode(phy, 0, RF_GAIN_MGC); // RX channel 0
    ad9361_set_rx_gain_control_mode(phy, 1, RF_GAIN_MGC); // RX channel 1

    //// =========================================================================
    //// RX GAIN VALUES
    //// =========================================================================
    int val;
    int gain = 10;
    float offset = -17.0f; // depends on frequency bladerf2_rx_gain_ranges, bladerf2_common.h
    struct bladerf_range const *range      = NULL;
    gain = gain - offset;
    state->dev->board->get_gain_stage_range(state->dev, 0, "full", &range);
    val = __scale_int(range, gain);
    ad9361_set_rx_rf_gain(phy, 0, val);
    ad9361_set_rx_rf_gain(phy, 1, val);

    // =========================================================================
    // Read data
    // =========================================================================
    
    rxtx_set_file_path(state->tx, "/home/tonix/Documents/CINVESTAV/Sept2020/Proyecto_Tolteca/Nuand_modified/NuandRFProyect/raw.csv");
    rxtx_set_file_format(state->tx,RXTX_FMT_CSV_SC16Q11);
    rxtx_set_file_path(state->rx, "/home/tonix/Documents/CINVESTAV/Proyecto_Tolteca/samples/rxAGgain.csv");
    rxtx_set_file_format(state->rx,RXTX_FMT_CSV_SC16Q11);
    struct tx_params *tx_params = state->tx->params;
    tx_params->repeat = 0;
    //tx_params->repeat_delay = 1000;
    //tx_cmd_start(state);
    rx_cmd_start(state);
    //usleep(1000*2000);
    //rxtx_cmd_stop(state,state->rx);
#if TEST

#if FREQUENCY
    for(long i=150000000; i < 150050000;i+=1000)
    {
        rxtx_cmd_stop(state,state->tx);
        
       
        CHECK_STATUS(board_data->rfic->select_band(state->dev, BLADERF_CHANNEL_TX(0), frequency+i));
        ad9361_set_tx_lo_freq(board_data->phy, frequency+i);
        

        tx_cmd_start(state);
        usleep(1000*150);
    }
#endif

#if AUTOGAIN
    printf("AUTOGAIN TEST\r\n");

    usleep(2000*1000);
    gc_mode = RF_GAIN_FASTATTACK_AGC; // auto mode
    ad9361_set_rx_gain_control_mode(phy, 0, gc_mode); // RX channel 0
    ad9361_set_rx_gain_control_mode(phy, 1, gc_mode); // RX channel 1
    usleep(2000*1000);

    gc_mode = RF_GAIN_MGC; // MANUAL GAIN CONTROL
    ad9361_set_rx_gain_control_mode(phy, 0, gc_mode); // RX channel 0
    ad9361_set_rx_gain_control_mode(phy, 1, gc_mode); // RX channel 1

#endif


#if GAIN
    struct bladerf_range const *range      = NULL;
    for(long i=0; i < 1000;i++)
    {
        rxtx_cmd_stop(state,state->tx);
        state->dev->board->get_gain_range(state->dev, BLADERF_CHANNEL_TX(0), &range);

        board_data->rfic->set_gain(state->dev, BLADERF_CHANNEL_TX(0), clamp_to_range(range, gain));        

        tx_cmd_start(state);
        usleep(1000*150);
    }

#endif
#if BANDWIDHT
    usleep(1000*2000);
    rxtx_cmd_stop(state,state->tx);
    usleep(1000*500);
    ad9361_set_tx_rf_bandwidth(phy,1500000); // 1.5Mhz -- reach to 56Mh
    usleep(1000*1000);
    tx_cmd_start(state);
    usleep(1000*2000);
    rxtx_cmd_stop(state,state->tx);
    usleep(1000*500);
    ad9361_set_tx_rf_bandwidth(phy,56000000);
    usleep(1000*1000);
    tx_cmd_start(state);

#endif

#if SAMPLERATE

    for(long i=5000000; i < 20000000; i+=1000000)
    {
        rxtx_cmd_stop(state,state->tx);
        usleep(1000*300);
        ad9361_set_tx_sampling_freq(phy, i);
        usleep(1000*300);
        tx_cmd_start(state);
        usleep(1000*1000);
    }
#endif

#endif
    //status = input_loop(state, true); // leave this when debu is needed
    // =========================================================================
    // Format to end C script
    // =========================================================================
    printf("\r\n");
    printf("press any key to end");
    system ("/bin/stty raw");
    getc(stdin);
    system ("/bin/stty cooked");
    printf("\r\n");
    // =========================================================================
    // Free Resources
    // =========================================================================

    rxtx_cmd_stop(state,state->tx);
    cli_state_destroy(state);
    deinit_rc_config(&rc);
    return status;
}
