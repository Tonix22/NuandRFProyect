#include "bridge.h"
#include "my_mainwindow.h"
#include <QString>
#include <iostream>

IPDI_Bridge :: IPDI_Bridge()
{
    /*config Data*/
    QString port  = "COM8";
    QString addr  = "1:0";
    QString csvfile = "Z:\\GUI_WINDOWS\\Project\\Bridge\\id00001001.csv";
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
IPDI_Bridge :: ~IPDI_Bridge()
{
    this->mw->finish();
    delete mw;
    delete aip;
}
