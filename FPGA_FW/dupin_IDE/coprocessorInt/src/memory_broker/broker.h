#ifndef BROKER_H
#define BROKER_H

#include "ad9361.h"

#define STANDAR_READ_SIZE 3
#define MAX_READ_SIZE 16
// AIP indexes 
#define OPCODE_IDX 0
#define P1_IDX 1
#define P2_IDX 2
// This index are for the array in the parser
#define P1_NUM 0 
#define P2_NUM 1

void Subscribe_broker(struct ad9361_rf_phy *ad9361_phy);


typedef enum
{
    IDLE ,
    READ ,
    WRITE
}DataStat;

typedef enum
{
    NORMAL,
    SPECIAL_SET,
    SPECIAL_GET
}InternatlStates;



#endif