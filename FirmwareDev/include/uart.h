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
#ifndef UART_H_
#define UART_H_

#include "type.h"

enum UartDataLength {BITS_8 = 8};
enum UartParity {NONE = 0,EVEN = 1,ODD = 2};
enum UartStop {ONE = 0,TWO = 1};

typedef struct
{
  volatile u32 DATA;
  volatile u32 STATUS;
  volatile u32 CLOCK_DIVIDER;
  volatile u32 FRAME_CONFIG;
} uart_dev_reg;

typedef struct {
	enum UartDataLength dataLength;
	enum UartParity parity;
	enum UartStop stop;
	u32 clockDivider;
} uart_config_reg;

/* Description: Write a single character over UART. */
extern void bsp_uart_write(uart_dev_reg *reg, char data);

/* Description: Write a string over UART. */
extern void bsp_uart_write_string(uart_dev_reg *reg, char* str);

/* Description: Read a single character over UART. */
extern char bsp_uart_read(uart_dev_reg *reg);

/* Description: Configure parameters of the UART device.
 * See uart_config_reg for available parameters. */
extern void bsp_uart_config(uart_dev_reg *reg, uart_config_reg *config);
#endif /* UART_H_ */


