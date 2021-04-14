
#include "bridge.h"
#include <QString>
#include <iostream>
#include <stdexcept>
#include <QMessageBox>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QTextStream>

#include<windows.h>
#include "Shlwapi.h"

#include "COM_finder.h"



/*config Data*/
QString addr  = "1:0";
//QString csvfile = "Z:\\Project\\Bridges\\id00004001.csv";


IPDI_Bridge :: IPDI_Bridge()
{

    QString csvfile;
    QString port;
    QString addr  = "1:0";

    uint32_t id = 0;
    int mode    = 1;
    bool success_COM = false;
    std::string COM_str;
    success_COM = get_COM_cypres_port(COM_str);

    if(success_COM)
    {
        int ret = 0;
        
        /*mw*/
        port = QString::fromStdString(COM_str);
        this->mw = new Qmw();
        this->mw->init(port, mode);

        /*aip*/
        this->aip = new qaip(mw);

        csvfile_try:
        //open File that contains the path
        {
            QString fileName = QDir::currentPath()+"\\CSVPATH.txt";
            QFile file(fileName);
            file.open(QFile::ReadOnly | QFile::Text);
            QTextStream in(&file);
            csvfile = in.readLine();
            file.close();
        }

        QByteArray ba = csvfile.toLocal8Bit();
        const char *lpStr1 = ba.data();

        ret = PathFileExists(lpStr1);

        if(ret == 1)
        {
            this->aip->readconfigs(csvfile, addr);
            aip->getID(&id, addr);

            /*debug*/
            std::cout<<"id : "<< id << std::endl;
            std::cout <<"USB port connected " << (mw->isBridgeConnected()?"YES":"NO") << std::endl;
        }
        else
        {
            QMessageBox messageBox;
            //ERROR MESSAGE
            QString filter = "Text File (*.csv*) ;; All File (*.*)";
            messageBox.critical(0,"Error","wrong .csv path, file path doesnt exist!, please select a valid path");
            messageBox.setFixedSize(500,200);
            //SELECT NEW PATH
            QString file_name = QFileDialog::getOpenFileName(NULL,"List of Parameters",QDir::currentPath(),filter);
            std::cout<<file_name.toStdString()<<std::endl;
            
            //OPEN FILE
            QString fileName = QDir::currentPath()+"\\CSVPATH.txt";
            QFile file(fileName);
            file.open(QIODevice::WriteOnly);
            QTextStream out(&file);
            out<<file_name<<"\n";

            file.flush();
            file.close();
            goto csvfile_try;
            //win->FilePathCheck();
            //this->mw->finish();
            //delete mw;
            //delete aip;
        }
    }
    else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Cypress COM port not found, verify USB is connected");
        messageBox.setFixedSize(500,200);
        throw std::invalid_argument("invalid COM PORT");
    }
    

    //Example();
}


void IPDI_Bridge :: WriteData()
{
    //uint32_t wr[]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    uint32_t* p = &data_in.op;
    aip->writeMem("MDATAIN", p, 10, 0, addr);
    aip->start(addr);
}
void IPDI_Bridge :: Wait_ACK()
{
    uint32_t mutex[4];
    do
    {
        Sleep(1);
        memset(mutex,0,sizeof(uint32_t)*4);
        aip->readMem("MDATAOUT", mutex, 4, 0, addr);
    }while(mutex[0]!='A' && mutex[1]!='C' && mutex[2]!='K');
}


void IPDI_Bridge :: ReadData()
{
    uint32_t p[10]={0};
    uint8_t tries = 0;
    uint32_t timeout = 0;
    do
    {
        Sleep(1);
        memset(p,0,sizeof(uint32_t)*10);
        aip->readMem("MDATAOUT", p, 10, 0, addr);

    }while(p[0]==0 && p[1]==0 && p[2]==0 && timeout++ < 30);

    timeout=0;
    data_out.p1 = p[0];
    data_out.p2 = p[1];

    aip->start(addr);

}

void IPDI_Bridge::Example()
{
    uint32_t id;
    aip->getID(&id, addr);
    std::cout <<"USB port connected" << (this->mw->isBridgeConnected()?"YES":"NO") << std::endl;

    uint32_t status;
    aip->getStatus(&status, addr);

    /* Write memory */
    uint32_t wr[]{3550, 4, 30,15, 7, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    aip->writeMem("MDATAIN", wr, 10, 0, addr);

    /* Start */
    aip->start(addr);

    /* Read memory */
    uint32_t rd[4];
    aip->readMem("MDATAOUT", rd, 4, 0, addr);
    std::cout << " data[0]"<< rd[0]<<std::endl;
}

IPDI_Bridge :: ~IPDI_Bridge()
{
    this->mw->finish();
    delete mw;
    delete aip;
}
