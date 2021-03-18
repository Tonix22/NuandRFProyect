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
#ifndef DUPIN_H_
#define DUPIN_H_

#include <soc.h>
#include "riscv.h"
#include "gpio.h"
#include "uart.h"
#include "noc.h"
#include "apb3stub.h"
#include "spi.h"
#include "i2c.h"
#include "plic.h"
#include "interrupt_port.h"
#include "machineTimer.h"

#define GPIO0  ((gpio_dev_reg*)(DUPIN_SOC_GPIO0_APB))
#define GPIO1  ((gpio_dev_reg*)(DUPIN_SOC_GPIO1_APB))
#define UART0 ((uart_dev_reg*)(DUPIN_SOC_UART0_APB))
#define I2C0 ((i2c_dev_reg*)(DUPIN_SOC_I2C_APB))
#define NOC_BASE ((noc_reg*)(DUPIN_SOC_NOC_INTERFACE_APB))
#define APB3_STUB ((Apb3Stub*)(DUPIN_SOC_APB3_STUB_APB))
#define SPI0_BASE ((spi_dev_reg*)(DUPIN_SOC_SPI0_APB))

#define UART_CONSOLE  UART0
#define PORTA         GPIO0
#define PORTB         GPIO1

#define MACHINE_TIMER   DUPIN_SOC_MACHINE_TIMER_APB
#define MACHINE_TIMER_HZ   DUPIN_SOC_MACHINE_TIMER_HZ

#define PLIC DUPIN_SOC_PLIC_APB
#define PLIC_CPU_0 DUPIN_SOC_PLIC_DUPIN_SOC_CPU_EXTERNAL_INTERRUPT


#endif
