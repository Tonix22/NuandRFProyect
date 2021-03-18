/*
 *      Dupin BSP
 *
 *  Copyright (C) 2021  Diego Hernandez <dhdezr@fpgaparadox.com>
 *
 *  Permission to use, copy, modify, and/or distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */
#ifndef _I2C_DEVICE_
#define _I2C_DEVICE_
#include "dupin.h"
#define CORE_HZ DUPIN_SOC_MACHINE_TIMER_HZ

/* Helper function for bsp_i2c_fast_init().
 * You are not expected to edit this manually.*/
void configure_i2c(i2c_dev_reg *reg, u32 frequency, u32 timeout, u32 tSU, u32 tLOW, u32 tHIGH, u32 tBUF)
{
    // Call the main configuration register
    i2c_config_reg i;
    // Configure the clock speed of the I2C
    i.samplingClockDivider = frequency;
    // Configure the timeout
    i.timeout = timeout;
    // Configure the setup time for a repeated start condition
    i.tsuDat = tSU;
    // Configure the LOW period of the SCLK clock
    i.tLow = tLOW;
    // Configure the HIGH period of the SCLK
    i.tHigh = tHIGH;
    // Configure the Bus Free time between a STOP and START condition
    i.tBuf = tBUF;
    // Apply configuration
    configure_i2c_device (reg, &i);
}

/* This function configures the I2C in fast mode (400 KHz)
 * Using a 50MHz system clock.
 * Please do not edit any of the values below.
 * >>> Description:
 * frequency: Sampling bewteen sda and scl to avoid loosing data.
 * timeout: Time after a transmission will be droped due missing ACK.
 * tSU: set-up time for a repeated START condition.
 * tLOW: LOW period of the SCL clock.
 * tHIGH: HIGH period of the SCL clock.
 * tBUF: bus free time between a STOP and START condition.
 * <<< end
 */
void bsp_i2c_fast_init(i2c_dev_reg *reg)
{
    u32 frequency = 3;
    u32 timeout = CORE_HZ/500;
    u32 tSU = CORE_HZ/1000000;
    u32 tLOW = CORE_HZ/400000;
    u32 tHIGH = CORE_HZ/400000;
    u32 tBUF = CORE_HZ/200000;
    configure_i2c(reg, frequency, timeout, tSU, tLOW, tHIGH, tBUF);
}

/* Description: If one of the transactions done using the I2C
 * commands is unsuccessful, this function will flag 
 * it as incorrect, It is used for debugging purposes. */
void check_status(int A)
{
    if (!A) {
        bsp_uart_write_string(UART_CONSOLE, "ERROR: Failed to execute this task correctly.\n.");
        while (1); // stop
    }
}

/* Description: Construct an I2C trama to send data
 * over the I2C bus. The function expects as arguments
 * the I2C peripheral base address, the address of the device
 * that the sender wants to communicate with, and the data to be transmitted. */ 
void bsp_transmit_byte_i2c(i2c_dev_reg *reg, u8 address, u8 data)
{
    i2c_claim_bus_blocking(reg);
    i2c_tx_byte (reg, address);
    i2c_tx_nack_block(I2C0);
    check_status(i2c_rx_ack(I2C0));
    i2c_tx_byte (reg, data);
    i2c_tx_nack_block(I2C0);
    check_status(i2c_rx_ack(I2C0));
    i2c_master_release_blocking(I2C0);
}

/* Description: When two consecutive packets are needed by the 
 * receiver (such as when configuring certain registers of I2C devices), two
 * packets must be sent. This function extends bsp_transmit_byte_i2c
 * to achieve this. */
void bsp_transmit_twobytes(i2c_dev_reg *reg, u8 address, u8 data0, u8 data1)
{
    i2c_claim_bus_blocking(reg);
    i2c_tx_byte (reg, address);
    i2c_tx_nack_block(I2C0);
    check_status(i2c_rx_ack(I2C0));
    i2c_tx_byte (reg, data0);
    i2c_tx_nack_block(I2C0);
    check_status(i2c_rx_ack(I2C0));
    i2c_tx_byte (reg, data1);
    i2c_tx_nack_block(I2C0);
    check_status(i2c_rx_ack(I2C0));
    i2c_master_release_blocking(I2C0);
}

/* Description: The function receives a transaction from an I2C
 * device, and returns such information. */
u8 bsp_receive_byte_i2c(i2c_dev_reg *reg, u8 address)
{
    u8 data = 0x00;
    i2c_claim_bus_blocking(reg);
    i2c_tx_byte(I2C0, address);
    i2c_tx_nack_block(I2C0);
    check_status(i2c_rx_ack(I2C0));
    i2c_tx_byte(I2C0, 0xFF);
    i2c_tx_nack_block(I2C0);
    data = i2c_rx_byte(I2C0);
    i2c_master_release_blocking(I2C0);
    return data;
}

/* Write multiple and read multiple
 * bytes can be derived from
 * bsp_transmit_byte_i2c and 
 * bsp_receive_byte_i2c functions. */

#endif /* _I2C_DEVICE_ */
