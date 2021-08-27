#include "plic_metal.h"
void configure_interrupts()
{
	// See the documentation provided in this release
	plic_set_threshold(PLIC, PLIC_CPU_0, 0);

	plic_set_enable(PLIC, PLIC_CPU_0, PLIC_INT_0, 1);
	plic_set_priority(PLIC, PLIC_INT_0, 1);

	plic_set_enable(PLIC, PLIC_CPU_0, PLIC_INT_1, 1);
	plic_set_priority(PLIC, PLIC_INT_1, 1);

	plic_set_enable(PLIC, PLIC_CPU_0, PLIC_INT_2, 1);
	plic_set_priority(PLIC, PLIC_INT_2, 1);

	plic_set_enable(PLIC, PLIC_CPU_0, PLIC_INT_3, 1);
	plic_set_priority(PLIC, PLIC_INT_3, 1);

	PORTA->INTERRUPT_RISE_ENABLE = 0xff;

	initTimer();

	//enable interrupts
	csr_write(mtvec, trap_entry);
	csr_set(mie, MIE_MTIE | MIE_MEIE);
	csr_write(mstatus, MSTATUS_MPP | MSTATUS_MIE);
}

uint64_t timerCmp;

void initTimer()
{
    timerCmp = timer_get_time(MACHINE_TIMER);
    scheduleTimer();
}

void scheduleTimer()
{
    timerCmp += TIMER_TICK_DELAY;
    timer_set_comparator(MACHINE_TIMER, timerCmp);
}

//Used on unexpected trap/interrupt codes
void crash()
{
	// bsp_uart_write_string(UART_CONSOLE, "\n*** YIKESS!!. System Crashed. ***\n");
	while(1);
}