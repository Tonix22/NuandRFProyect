#ifndef BROKER_H
#define BROKER_H

#include "ad9361.h"
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