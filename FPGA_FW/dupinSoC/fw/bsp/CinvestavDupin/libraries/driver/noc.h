#ifndef _NOC_H_
#define _NOC_H_
typedef struct
{
	volatile uint32_t read_data;
       	volatile uint32_t write_data;
	volatile uint32_t write_conf;
	volatile uint32_t start;
} noc_reg;
#endif
