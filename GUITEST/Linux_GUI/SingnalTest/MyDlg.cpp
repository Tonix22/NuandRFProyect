#include "MyDlg.h"


MyDlg::MyDlg()
{
    pLayout = new QHBoxLayout(this);
    pBttn   = new QPushButton ("CLICK me");

    pLayout->addWidget(pBttn);
    setLayout (pLayout);
    setWindowTitle("Signal and Slots");

    connect(
        pBttn,
        SIGNAL( clicked()),
        this,
        SLOT(onButtonClicked())
    );
}
void MyDlg :: onButtonClicked()
{
    qDebug()<<"Button clicked"
}