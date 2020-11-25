#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sample.h"


class MainWindow : public QMainWindow, private Ui::OpcodeGenerator
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
private slots:
    void onButtonClicked();
};

#endif // MAINWINDOW_H
