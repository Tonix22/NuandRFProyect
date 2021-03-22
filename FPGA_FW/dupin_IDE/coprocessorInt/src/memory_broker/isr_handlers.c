#include <stdint.h>
#include "dupin.h"
#include "plic_metal.h"
#include "config.h"
#include "isr_handler.h"
#include <stdbool.h>
#include "aip.h"
#include "broker.h"

volatile DataStat ISR_FLAG = IDLE;

void trap()
{
	int32_t mcause = csr_read(mcause);
	int32_t interrupt = mcause < 0;
	int32_t cause     = mcause & 0xF;
	if(interrupt){
		switch(cause){
		case CAUSE_MACHINE_TIMER: timerInterrupt(); break;
		case CAUSE_MACHINE_EXTERNAL: externalInterrupt(); break;
		default: crash(); break;
		}
	} else {
		crash();
	}
}

void timerInterrupt() {
    static uint32_t counter = 0;
	scheduleTimer();

	GPIO1->OUTPUT = 0x0f;

	// bsp_uart_write_string(UART_CONSOLE, "TIMER SECONDS = ");
	// bsp_uart_write(UART_CONSOLE, '0' + counter);
	// bsp_uart_write(UART_CONSOLE, '\n');
	if(++counter == 10) counter = 0;
}

void externalInterrupt ()
{
	uint32_t claim;
	while((claim = plic_claim(PLIC, PLIC_CPU_0))) {
        bsp_uart_write (UART_CONSOLE, '0' + claim + ' ');
		switch(claim){
			case PLIC_INT_0:
				// bsp_uart_write_string(UART_CONSOLE, "PLIC_INT_0\n");
				ISR_FLAG = READ;
				break;
			case PLIC_INT_1:
				// bsp_uart_write_string(UART_CONSOLE, "PLIC_INT_1\n");
				break;
			case PLIC_INT_2:
				// bsp_uart_write_string(UART_CONSOLE, "PLIC_INT_2\n");
				break;
			case PLIC_INT_3:
				// bsp_uart_write_string(UART_CONSOLE, "PLIC_INT_3\n");
				break;
			default: crash(); break;
		}
		plic_release(PLIC, PLIC_CPU_0, claim);
	}
}

void dummy (void)
{
	uint32_t data = 0;

	/* busy */ 
	data = 0x100;
	aip_write(0x1e, &data, 1, 0);
	

	for (uint32_t i = 0; i < 32; i++)
	{
		aip_read(0x0, &data, 1, i);

		aip_write(0x4, &data, 1, i);
	}

	/* done */
	data = 0x01;
	aip_write(0x1e, &data, 1, 0);
}
void int_isr()
{
	configure_interrupts();
}
/*
int main ()
{
	configure_interrupts();

	GPIO1->OUTPUT_ENABLE = 0xF;
	GPIO1->OUTPUT = 0x1;

	// bsp_uart_write_string(UART_CONSOLE, "*** Interrupts demo ***\n");
	// bsp_uart_write_string(UART_CONSOLE, "Press a button\n");

	while(1)
	{
		if (ISR_FLAG)
		{
			GPIO1->OUTPUT = 0x2;
			
			dummy();
			
			GPIO1->OUTPUT = 0x3;

			ISR_FLAG = 0;
		}
	}
}*/