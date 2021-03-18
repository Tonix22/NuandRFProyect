
#include "aip.h"
#include "dupin.h"

static void aip_setConfig(uint32_t config);

static void aip_writeData(uint32_t data);

static uint32_t aip_readData(void);

static void wait (int cycles);


void aip_read (uint32_t config, uint32_t * data, uint32_t size, uint32_t offset)
{
    if (AIP_CONFIG_IPID != config && AIP_CONFIG_STATUS != config)
    {
        aip_setConfig(config+1);
        aip_writeData(offset);   
    }

    aip_setConfig(config);

    for (uint32_t idx = 0; idx < size; idx++)
    {
        data[idx] = aip_readData();
    }
    
}

void aip_write (uint32_t config, uint32_t * data, uint32_t size, uint32_t offset)
{
    if (AIP_CONFIG_IPID != config && AIP_CONFIG_STATUS != config)
    {
        aip_setConfig(config+1);

        aip_writeData(offset);
    }

    aip_setConfig(config);

    for (uint32_t idx = 0; idx < size; idx++)
    {
        aip_writeData(data[idx]);
    }
}

void aip_start (void)
{
    NOC_BASE->start = 0x00000001;

    NOC_BASE->start = 0x00000000;
}

static void aip_setConfig(uint32_t config)
{
    NOC_BASE->write_conf = config;
}

static void aip_writeData(uint32_t data)
{
    NOC_BASE->write_data = data;
}

static uint32_t aip_readData(void)
{
    uint32_t data;

    data = NOC_BASE->read_data;

    return data;
}

static void wait (int cycles)
{
  for(uint32_t idx = 0; idx < cycles ;idx++) asm volatile("");
}