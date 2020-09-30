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


#include "board/bladerf2/common.h"

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

    if (status) //NUAND ERROR
    {

        /* Just warn if no device is attached; don't error out */
        if (!rc->device && status == BLADERF_ERR_NODEV){
            fprintf(stderr, "\n");
            fprintf(stderr, "No bladeRF device(s) available.\n");
            status = 0;
        } 
        else {
            fprintf(stderr, "Failed to open device (%s): %s\n",
                    rc->device ? rc->device : "first available",
                    bladerf_strerror(status));
            status = -1;
        }
    } 
    else {
        status = bladerf_get_fpga_size(state->dev, &state->dev_info.fpga_size);

        if (status != 0) {
            fprintf(stderr, "Could not determine FPGA size.\n");
        } else {
            if (state->dev_info.fpga_size == BLADERF_FPGA_40KLE ||
                    state->dev_info.fpga_size == BLADERF_FPGA_115KLE) {
                state->dev_info.is_bladerf_x40_x115 = true;
            }

            if (state->dev_info.fpga_size == BLADERF_FPGA_A4 ||
                    state->dev_info.fpga_size == BLADERF_FPGA_A9) {
                state->dev_info.is_bladerf_micro = true;
            }
        }
    }

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
    
    status = open_device(&rc, state);
    
    // =========================================================================
    // RX AND TX Threads init
    // =========================================================================
    
    cli_start_tasks(state);
    
    // =========================================================================
    // Frequency
    // =========================================================================
    
    MUTEX_LOCK(&(state->dev->lock));
    //state->dev->board->set_frequency(state->dev,BLADERF_CHANNEL_TX(0),1500000000);
    //state->dev->board_data->rfic->set_frequency(state->dev,BLADERF_CHANNEL_TX(0),1500000000);
    struct bladerf2_board_data *board_data = state->dev->board_data;
    struct controller_fns const * fanfic = board_data->rfic;
    board_data->rfic->set_frequency(state->dev,BLADERF_CHANNEL_TX(0),1500000000);
    MUTEX_UNLOCK(&(state->dev->lock));
    
    // =========================================================================
    // Sample Rate
    // =========================================================================
    
    struct bladerf_rational_rate rate;
    rate.integer = 1500000;
    rate.num = 0;
    rate.den = 1;
    state->dev->board->set_rational_sample_rate(state->dev,BLADERF_CHANNEL_TX(0), &rate, &rate);
    
    // =========================================================================
    // bandwidth
    // =========================================================================
    state->dev->board->set_bandwidth(state->dev,BLADERF_CHANNEL_TX(0), 1500000, NULL);
    
    // =========================================================================
    // Read data
    // =========================================================================
    rxtx_set_file_path(state->tx, "/home/tonix/Documents/CINVESTAV/setp-dic_2020/bladeRF/raw.csv");
    rxtx_set_file_format(state->tx,RXTX_FMT_CSV_SC16Q11);
    struct tx_params *tx_params = state->tx->params;
    tx_params->repeat = 0;
    tx_params->repeat_delay = 1000;
    tx_cmd_start(state);

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

    
    
    cli_state_destroy(state);
    deinit_rc_config(&rc);
    return status;
}
