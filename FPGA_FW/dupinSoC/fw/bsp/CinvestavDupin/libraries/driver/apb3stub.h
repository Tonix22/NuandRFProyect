#ifndef _APB3STUB_H_
#define _APB3STUB_H_
typedef struct
{
        volatile uint32_t read_result;
        volatile uint32_t write_port0;
        volatile uint32_t write_port1;
} Apb3Stub;
#endif
