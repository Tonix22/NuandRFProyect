#include <QApplication>
#include <QDebug>
#include "sample.h"
#include "my_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :   QMainWindow(parent)
{
    setupUi(this);

    connect(
        SendData,
        SIGNAL( clicked()),
        this,
        SLOT(onButtonClicked())
    );
    connect(
        set_get_menu,
        SIGNAL(currentTextChanged(QString)),
        this,
        SLOT(writetext(QString))
    );

    this->show();
}
MainWindow::~MainWindow()
{
    //delete ui;
}
void MainWindow :: onButtonClicked()
{
    qDebug()<<" param1 "<< Param1_slider_val->text();
    
}
void MainWindow :: writetext(const QString &text)
{
    qDebug()<<text;
}

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
