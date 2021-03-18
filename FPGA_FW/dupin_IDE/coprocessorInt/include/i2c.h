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
#ifndef I2C_H_
#define I2C_H_
#include "type.h"

// Programmers view of the I2C device
typedef struct
{
	volatile u32 TX_DATA;
	volatile u32 TX_ACK;
	volatile u32 RX_DATA;
	volatile u32 RX_ACK;
	volatile u32 _a[4];
	volatile u32 INTERRUPT_ENABLE;
	volatile u32 INTERRUPT_FLAG;
	volatile u32 SAMPLING_CLOCK_DIVIDER;
	volatile u32 TIMEOUT;
	volatile u32 TSUDAT;
	volatile u32 _c[3];
	volatile u32 MASTER_STATUS;
	volatile u32 _d[3];
	volatile u32 TLOW;
	volatile u32 THIGH;
	volatile u32 TBUF;
	volatile u32 _e[9];
	volatile u32 FILTERING_HIT;
	volatile u32 FILTERING_STATUS;
	volatile u32 FILTERING_CONFIG[];
} i2c_dev_reg;

/* Description:
 * For a sender configuration, set all of the
 * values in the structure. For a receiver, set
 * samplingClockDivider, timeout and tsuDAT. */
typedef struct {
    // Master/slave
    u32 samplingClockDivider; // Oversampling value of I2C bus.
    u32 timeout; // Max cycles to wait before flagging a timeout.
    u32 tsuDat; // Set-up time for a repeated START condition.
    // Master
    u32 tLow; // LOW period of the SCL clock.
    u32 tHigh; // HIGH period of the SCL clock.
    u32 tBuf; // Bus free time between a STOP and START condition
} i2c_config_reg;

// Setup related functions
/* Description: This function is used to configure
 * parameters of the I2C sender/receiver device.
 * it receives the I2C base address and the i2c_config_reg
 * parameters (samplingClockDivider, timeout, tsuDAT, tLOW
 * tHIGH and tBUF). */
extern void configure_i2c_device(i2c_dev_reg *reg, i2c_config_reg *config);

/* Description: Issue a START command. */
extern void i2c_claim_bus(i2c_dev_reg *reg);

// Interrupt related functions
/* Description: Enable filtering for interrupt controller. */
extern void i2c_enable_filter(i2c_dev_reg *reg, u32 filterId, u32 config);

// Master related functions
/* Description: Returns true if the transmitter is busy. */
extern int i2c_master_is_busy(i2c_dev_reg *reg);

/* Description: Issue a START command in a blocking manner. */
extern void i2c_claim_bus_blocking(i2c_dev_reg *reg);

/* Description: Issue a STOP command. */
extern void i2c_master_release(i2c_dev_reg *reg);

/* Description: Issue a STOP command but waiting for the sender to
 * be free. */
extern void i2c_master_release_wait(i2c_dev_reg *reg);

/* Description: Drop the packet. */
extern void i2c_master_drop(i2c_dev_reg *reg);

/* Description: Issue a STOP command in a blocking manner. */
extern void i2c_master_release_blocking(i2c_dev_reg *reg);

/* Description: Listen only ACK for received transaction.
 * Useful for monitor mode I2C. */
extern void i2c_listen_ack(i2c_dev_reg *reg);

/* Description: Transmit a byte (u8 data). */
extern void i2c_tx_byte(i2c_dev_reg *reg,u8 byte);

/* Description: Send an ACK command. */
extern void i2c_tx_ack(i2c_dev_reg *reg);

/* Description: Send a NACK command. */
extern void i2c_tx_nack(i2c_dev_reg *reg);

/* Description: Wait for ACK command to be transmitted. */
extern void i2c_tx_ack_wait(i2c_dev_reg *reg);

/* Description: Enforce the transmission of an ACK command.
 * This function is the conjunction of i2c_tx_ack and 
 * i2c_tx_ack_wait. */
extern void i2c_tx_ack_block(i2c_dev_reg *reg);

/* Description: Enforce the transmission of a NACK command.
 * This function is the conjunction of i2c_tx_ack and 
 * i2c_tx_ack_wait. */
extern void i2c_tx_nack_block(i2c_dev_reg *reg);

/* Description: Receive data from the transmitter. */
extern u32 i2c_rx_byte(i2c_dev_reg *reg);

/* Description: Check for NACK command in the receive side. */
extern int i2c_rx_nack(i2c_dev_reg *reg);

/* Description: Check for ACK command in the receive side. */
extern int i2c_rx_ack(i2c_dev_reg *reg);

/* Description: Transmit a byte until is accepted and
 * acknowledged. Repeat the command if the packet is not
 * received correctly. */
extern void i2c_tx_byte_repeat(i2c_dev_reg *reg,u8 byte);

/* Description: Transmit a NACK command until is accepted.
 * Repeat the command if it is not
 * received correctly. */
extern void i2c_tx_nack_repeat(i2c_dev_reg *reg);

#endif /* I2C_H_ */
