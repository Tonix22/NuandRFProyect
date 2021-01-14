#include <QApplication>
#include <QDebug>
#include "sample.h"
#include "my_mainwindow.h"
#include <QMessageBox>


int main(int argc, char *argv[])
{
    QApplication theApp (argc, argv);
    //QMainWindow widget;
    //Ui::OpcodeGenerator ui;
    //ui.setupUi(&widget);
//
    //widget.show();
    MainWindow opg;

    return theApp.exec();
}
