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
#ifndef SPI_H_
#define SPI_H_

#include "type.h"

typedef struct
{
  volatile u32 DATA;
  volatile u32 BUFFER;
  volatile u32 CONFIG;
  volatile u32 INTERRUPT;

  volatile u32 _a[4];

  volatile u32 CLK_DIVIDER;
  volatile u32 SS_SETUP;
  volatile u32 SS_HOLD;
  volatile u32 SS_DISABLE;
} spi_dev_reg;

typedef struct {
	u32 cpol;
	u32 cpha;
	u32 mode;
	u32 clkDivider;
	u32 ssSetup;
	u32 ssHold;
	u32 ssDisable;
} spi_config_reg;

/* Description: Transmit a byte over the SPI selected device. */
extern void spi_txbyte(spi_dev_reg *reg, u8 data);

/* Description: Receive data over the SPI selected device. */
extern u8 spi_rxdat(spi_dev_reg *reg);

/* Description: Select a SPI device from the bus.
 * asserting the CSn pin. */
extern void spi_select_device(spi_dev_reg *reg, u32 slaveId);

/* Description: Deselect a SPI device from the bus.
 * deasserting the CSn pin. */
extern void spi_deselect_device(spi_dev_reg *reg, u32 slaveId);

/* Description: Configure the parameters of the SPI device.
 *  See spi_config_reg for available parameters. */
extern void spi_configure(spi_dev_reg *reg, spi_config_reg *config);

#endif /* SPI_H_ */

