#ifndef BRIDGE_H
#define BRIDGE_H
#include "qtmw.h"
#include "qaip.h"

typedef struct
{
    uint32_t op;
    uint32_t p1;
    uint32_t p2;
    void* large_data;
    short ld_size;
}Param_chunk;

class IPDI_Bridge
{
    public:
    Qmw *mw;
    qaip *aip;
    Param_chunk data_in;
    Param_chunk data_out;
    char block_size = 10;
    IPDI_Bridge();
    void ReadData();
    void WriteData();
    ~IPDI_Bridge();
};


#endif