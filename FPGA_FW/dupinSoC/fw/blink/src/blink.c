#include <stdio.h>
#include <stdlib.h>

#include "dupin.h"
void delay()
{
	for(uint32_t idx = 0;idx < 5000000;idx++) asm volatile("");
}

void main() {
	// Set GPIO LSB as outputs
    GPIO1->OUTPUT_ENABLE = 0x0000000F;

	// Set initial value of GPIO
    GPIO1->OUTPUT = 0x00000005;

	while(1)
	{
		GPIO1->OUTPUT ^= 0x0000000F;
        delay();
	}
}
