#include "app.h"

int APP_init(int argc, char *argv[])
{
    QApplication theApp (argc, argv);
    MainWindow opg;
    return theApp.exec();
}