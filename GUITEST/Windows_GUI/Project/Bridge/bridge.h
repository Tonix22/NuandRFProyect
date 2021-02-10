#ifndef BRIDGE_H
#define BRIDGE_H
#include "qtmw.h"
#include "qaip.h"


class IPDI_Bridge
{
    Qmw *mw;
    qaip *aip;
    public:
    IPDI_Bridge();
    ~IPDI_Bridge();
};


#endif