/*
 ============================================================================
 Name        : main.c
 Author      : Edgardo Serna-Enciso
 Version     :
 Copyright   : Your copyright notice
 Description : Hello RISC-V World in C
 ============================================================================
 */

#include <stdio.h>

#include "dupin.h"

void delay()
{
    for(uint32_t idx = 0;idx < 5000000;idx++) asm volatile("");
}

int main(void)
{
    uint8_t dataTxSPI = 0;
    Spi_Config spiConfig;

    spiConfig.cpol = 1;
    spiConfig.cpha = 1;
    spiConfig.mode = 0;
    spiConfig.clkDivider = 10;
    spiConfig.ssSetup = 2;
    spiConfig.ssHold = 2;
    spiConfig.ssDisable = 2;

    // Set GPIO LSB as outputs
    GPIO1->OUTPUT_ENABLE = 0x00000001;

    // Set initial value of GPIO
    GPIO1->OUTPUT = 0x00000001;

    spi_applyConfig(SPI0_BASE, &spiConfig);

    dataTxSPI = 0x55;
    spi_select(SPI0_BASE, 0);
    spi_write(SPI0_BASE, dataTxSPI);
    spi_deselect(SPI0_BASE, 0);

    dataTxSPI = 0xaa;
    spi_select(SPI0_BASE, 0);
    spi_write(SPI0_BASE, dataTxSPI);
    spi_deselect(SPI0_BASE, 0);

    while(1)
    {
        GPIO1->OUTPUT ^= 0x0000000F;
        delay();

        dataTxSPI = ~dataTxSPI;

        spi_select(SPI0_BASE, 0);
        spi_write(SPI0_BASE, dataTxSPI);
        spi_deselect(SPI0_BASE, 0);
    }

    return 0;
}
