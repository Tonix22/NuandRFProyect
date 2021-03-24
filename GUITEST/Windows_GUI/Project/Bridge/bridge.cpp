#include "bridge.h"
#include "my_mainwindow.h"
#include <QString>
#include <iostream>

/*config Data*/
QString port  = "COM8";
QString addr  = "1:0";
QString csvfile = "Z:\\GUI_WINDOWS\\Project\\Bridge\\id00001001.csv";

IPDI_Bridge :: IPDI_Bridge()
{

    uint32_t id = 0;
    int mode    = 1;
    /*mw*/
    this->mw = new Qmw();
    this->mw->init(port, mode);

    /*aip*/
    this->aip = new qaip(mw);
    this->aip->readconfigs(csvfile, addr);
    aip->getID(&id, addr);
    
    /*debug*/
    std::cout<<"id : "<< id << std::endl;
    std::cout <<"USB port connected " << (mw->isBridgeConnected()?"YES":"NO") << std::endl;
}


void IPDI_Bridge :: WriteData()
{
    //uint32_t wr[]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    uint32_t* p = &data_in.op;
    aip->writeMem("MDATAIN", p, 3, 0, addr);
    aip->start(addr);
}
void IPDI_Bridge :: ReadData()
{
    uint32_t* p = &data_out.op;
    //data_out.p1;
    //// pass data from input memory to output one
    aip->readMem("MDATAOUT", p, 3, 0, addr);
}


IPDI_Bridge :: ~IPDI_Bridge()
{
    this->mw->finish();
    delete mw;
    delete aip;
}
