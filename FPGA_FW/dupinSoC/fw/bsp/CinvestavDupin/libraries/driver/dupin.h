#ifndef DUPIN_H_
#define DUPIN_H_

#include <soc.h>
#include "riscv.h"
#include "gpio.h"
#include "uart.h"
#include "noc.h"
#include "apb3stub.h"
#include "spi.h"

#define GPIO0  ((Gpio_Reg*)(DUPIN_SOC_GPIO0_APB))
#define GPIO1  ((Gpio_Reg*)(DUPIN_SOC_GPIO1_APB))
#define UART0 ((Uart_Reg*)(DUPIN_SOC_UART0_APB))
#define I2C0 ((I2c_Reg*)(DUPIN_SOC_I2C_APB))
#define NOC_BASE ((noc_reg*)(DUPIN_SOC_NOC_INTERFACE_APB))
#define APB3_STUB ((Apb3Stub*)(DUPIN_SOC_APB3_STUB_APB))
#define SPI0_BASE ((Spi_Reg*)(DUPIN_SOC_SPI0_APB))

#define UART_CONSOLE  UART0
#define PORTA         GPIO0
#define PORTB         GPIO1

#ifdef SYSTEM_MACHINE_TIMER_APB
#define MACHINE_TIMER   DUPIN_SOC_MACHINE_TIMER_APB
#define MACHINE_TIMER_HZ   DUPIN_SOC_MACHINE_TIMER_HZ
#endif

#ifdef SYSTEM_PLIC_APB
#define PLIC DUPIN_SOC_PLIC_APB
#define PLIC_CPU_0 DUPIN_SOC_PLIC_DUPIN_SOC_CPU_EXTERNAL_INTERRUPT
#endif

#endif
