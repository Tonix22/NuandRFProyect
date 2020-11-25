/********************************************************************************
** Form generated from reading UI file 'Frameworkhelp.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SAMPLE_H
#define SAMPLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OpcodeGenerator
{
public:
    QWidget *centralwidget;
    QSlider *Param_1_val;
    QComboBox *set_get_menu;
    QLabel *do_set_get_label;
    QComboBox *tx_rx_menu;
    QComboBox *param_1_menu;
    QSlider *Param_2_val;
    QLabel *param2_up_label;
    QLabel *param2_up_label_2;
    QLabel *tx_rx_label;
    QLabel *param1_label;
    QLabel *param2_label;
    QPushButton *SendData;
    QComboBox *param_2_menu;
    QLabel *logo;
    QLabel *Param1_slider_val;
    QLabel *Param2_slider_val;
    QLabel *max_p1_val;
    QLabel *min_p1_val;
    QLabel *max_p2_val;
    QLabel *min_p2_val;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *OpcodeGenerator)
    {
        if (OpcodeGenerator->objectName().isEmpty())
            OpcodeGenerator->setObjectName(QStringLiteral("OpcodeGenerator"));
        OpcodeGenerator->resize(711, 455);
        centralwidget = new QWidget(OpcodeGenerator);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        Param_1_val = new QSlider(centralwidget);
        Param_1_val->setObjectName(QStringLiteral("Param_1_val"));
        Param_1_val->setGeometry(QRect(220, 250, 160, 24));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 249, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(127, 252, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(63, 250, 255, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(0, 124, 127, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(0, 166, 170, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush2);
        QBrush brush7(QColor(255, 255, 220, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        Param_1_val->setPalette(palette);
        Param_1_val->setValue(50);
        Param_1_val->setSliderPosition(50);
        Param_1_val->setOrientation(Qt::Horizontal);
        set_get_menu = new QComboBox(centralwidget);
        set_get_menu->setObjectName(QStringLiteral("set_get_menu"));
        set_get_menu->setGeometry(QRect(480, 130, 112, 38));
        do_set_get_label = new QLabel(centralwidget);
        do_set_get_label->setObjectName(QStringLiteral("do_set_get_label"));
        do_set_get_label->setGeometry(QRect(500, 100, 91, 22));
        tx_rx_menu = new QComboBox(centralwidget);
        tx_rx_menu->setObjectName(QStringLiteral("tx_rx_menu"));
        tx_rx_menu->setGeometry(QRect(340, 130, 112, 38));
        param_1_menu = new QComboBox(centralwidget);
        param_1_menu->setObjectName(QStringLiteral("param_1_menu"));
        param_1_menu->setGeometry(QRect(200, 130, 112, 38));
        Param_2_val = new QSlider(centralwidget);
        Param_2_val->setObjectName(QStringLiteral("Param_2_val"));
        Param_2_val->setGeometry(QRect(220, 330, 160, 24));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush8(QColor(126, 253, 255, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush8);
        QBrush brush9(QColor(63, 251, 255, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush9);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush4);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush2);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush8);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush9);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        Param_2_val->setPalette(palette1);
        Param_2_val->setValue(50);
        Param_2_val->setOrientation(Qt::Horizontal);
        param2_up_label = new QLabel(centralwidget);
        param2_up_label->setObjectName(QStringLiteral("param2_up_label"));
        param2_up_label->setGeometry(QRect(280, 210, 68, 22));
        param2_up_label_2 = new QLabel(centralwidget);
        param2_up_label_2->setObjectName(QStringLiteral("param2_up_label_2"));
        param2_up_label_2->setGeometry(QRect(270, 310, 68, 22));
        tx_rx_label = new QLabel(centralwidget);
        tx_rx_label->setObjectName(QStringLiteral("tx_rx_label"));
        tx_rx_label->setGeometry(QRect(360, 100, 68, 22));
        param1_label = new QLabel(centralwidget);
        param1_label->setObjectName(QStringLiteral("param1_label"));
        param1_label->setGeometry(QRect(220, 100, 68, 22));
        param2_label = new QLabel(centralwidget);
        param2_label->setObjectName(QStringLiteral("param2_label"));
        param2_label->setGeometry(QRect(80, 100, 68, 22));
        SendData = new QPushButton(centralwidget);
        SendData->setObjectName(QStringLiteral("SendData"));
        SendData->setGeometry(QRect(500, 280, 99, 38));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush10(QColor(115, 210, 22, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush10);
        QBrush brush11(QColor(170, 255, 87, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Light, brush11);
        QBrush brush12(QColor(142, 232, 54, 255));
        brush12.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Midlight, brush12);
        QBrush brush13(QColor(57, 105, 11, 255));
        brush13.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Dark, brush13);
        QBrush brush14(QColor(76, 140, 14, 255));
        brush14.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Mid, brush14);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        palette2.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush10);
        palette2.setBrush(QPalette::Active, QPalette::Shadow, brush);
        QBrush brush15(QColor(185, 232, 138, 255));
        brush15.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::AlternateBase, brush15);
        palette2.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette2.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush10);
        palette2.setBrush(QPalette::Inactive, QPalette::Light, brush11);
        palette2.setBrush(QPalette::Inactive, QPalette::Midlight, brush12);
        palette2.setBrush(QPalette::Inactive, QPalette::Dark, brush13);
        palette2.setBrush(QPalette::Inactive, QPalette::Mid, brush14);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush10);
        palette2.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush15);
        palette2.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette2.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush13);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush10);
        palette2.setBrush(QPalette::Disabled, QPalette::Light, brush11);
        palette2.setBrush(QPalette::Disabled, QPalette::Midlight, brush12);
        palette2.setBrush(QPalette::Disabled, QPalette::Dark, brush13);
        palette2.setBrush(QPalette::Disabled, QPalette::Mid, brush14);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush13);
        palette2.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush13);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush10);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush10);
        palette2.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush10);
        palette2.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette2.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        SendData->setPalette(palette2);
        param_2_menu = new QComboBox(centralwidget);
        param_2_menu->setObjectName(QStringLiteral("param_2_menu"));
        param_2_menu->setGeometry(QRect(60, 130, 112, 38));
        logo = new QLabel(centralwidget);
        logo->setObjectName(QStringLiteral("logo"));
        logo->setGeometry(QRect(270, 10, 141, 81));
        logo->setContextMenuPolicy(Qt::NoContextMenu);
        logo->setPixmap(QPixmap(QString::fromUtf8(":/icon/external-content.duckduckgo.com.png")));
        logo->setScaledContents(true);
        Param1_slider_val = new QLabel(centralwidget);
        Param1_slider_val->setObjectName(QStringLiteral("Param1_slider_val"));
        Param1_slider_val->setGeometry(QRect(290, 270, 68, 22));
        Param2_slider_val = new QLabel(centralwidget);
        Param2_slider_val->setObjectName(QStringLiteral("Param2_slider_val"));
        Param2_slider_val->setGeometry(QRect(280, 350, 68, 22));
        max_p1_val = new QLabel(centralwidget);
        max_p1_val->setObjectName(QStringLiteral("max_p1_val"));
        max_p1_val->setGeometry(QRect(400, 250, 68, 22));
        min_p1_val = new QLabel(centralwidget);
        min_p1_val->setObjectName(QStringLiteral("min_p1_val"));
        min_p1_val->setGeometry(QRect(130, 250, 68, 22));
        max_p2_val = new QLabel(centralwidget);
        max_p2_val->setObjectName(QStringLiteral("max_p2_val"));
        max_p2_val->setGeometry(QRect(400, 330, 68, 22));
        min_p2_val = new QLabel(centralwidget);
        min_p2_val->setObjectName(QStringLiteral("min_p2_val"));
        min_p2_val->setGeometry(QRect(130, 330, 68, 22));
        OpcodeGenerator->setCentralWidget(centralwidget);
        menubar = new QMenuBar(OpcodeGenerator);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 711, 30));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        OpcodeGenerator->setMenuBar(menubar);
        statusbar = new QStatusBar(OpcodeGenerator);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        OpcodeGenerator->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());

        retranslateUi(OpcodeGenerator);
        QObject::connect(Param_1_val, SIGNAL(sliderMoved(int)), Param1_slider_val, SLOT(setNum(int)));
        QObject::connect(Param_2_val, SIGNAL(sliderMoved(int)), Param2_slider_val, SLOT(setNum(int)));

        QMetaObject::connectSlotsByName(OpcodeGenerator);
    } // setupUi

    void retranslateUi(QMainWindow *OpcodeGenerator)
    {
        OpcodeGenerator->setWindowTitle(QApplication::translate("OpcodeGenerator", "MainWindow", Q_NULLPTR));
        set_get_menu->clear();
        set_get_menu->insertItems(0, QStringList()
         << QApplication::translate("OpcodeGenerator", "None", Q_NULLPTR)
         << QApplication::translate("OpcodeGenerator", "do", Q_NULLPTR)
         << QApplication::translate("OpcodeGenerator", "set", Q_NULLPTR)
         << QApplication::translate("OpcodeGenerator", "get", Q_NULLPTR)
        );
        do_set_get_label->setText(QApplication::translate("OpcodeGenerator", "Do,Set,Get", Q_NULLPTR));
        tx_rx_menu->clear();
        tx_rx_menu->insertItems(0, QStringList()
         << QApplication::translate("OpcodeGenerator", "other", Q_NULLPTR)
         << QApplication::translate("OpcodeGenerator", "tx", Q_NULLPTR)
         << QApplication::translate("OpcodeGenerator", "rx", Q_NULLPTR)
         << QApplication::translate("OpcodeGenerator", "trx", Q_NULLPTR)
        );
        param_1_menu->clear();
        param_1_menu->insertItems(0, QStringList()
         << QApplication::translate("OpcodeGenerator", "None", Q_NULLPTR)
         << QApplication::translate("OpcodeGenerator", "uint8_t", Q_NULLPTR)
         << QApplication::translate("OpcodeGenerator", "uint32_t", Q_NULLPTR)
         << QApplication::translate("OpcodeGenerator", "int32_t", Q_NULLPTR)
         << QApplication::translate("OpcodeGenerator", "uint64_t", Q_NULLPTR)
         << QApplication::translate("OpcodeGenerator", "struct", Q_NULLPTR)
         << QApplication::translate("OpcodeGenerator", "RXFIRConfig", Q_NULLPTR)
         << QApplication::translate("OpcodeGenerator", "TxFIRConfig", Q_NULLPTR)
        );
        param2_up_label->setText(QApplication::translate("OpcodeGenerator", "Param1", Q_NULLPTR));
        param2_up_label_2->setText(QApplication::translate("OpcodeGenerator", "Param2", Q_NULLPTR));
        tx_rx_label->setText(QApplication::translate("OpcodeGenerator", "Tx,Rx,TRX", Q_NULLPTR));
        param1_label->setText(QApplication::translate("OpcodeGenerator", "Param1", Q_NULLPTR));
        param2_label->setText(QApplication::translate("OpcodeGenerator", "Param2", Q_NULLPTR));
        SendData->setText(QApplication::translate("OpcodeGenerator", "Send", Q_NULLPTR));
        param_2_menu->clear();
        param_2_menu->insertItems(0, QStringList()
         << QApplication::translate("OpcodeGenerator", "None", Q_NULLPTR)
         << QApplication::translate("OpcodeGenerator", "uint8_t", Q_NULLPTR)
         << QApplication::translate("OpcodeGenerator", "uint32_t", Q_NULLPTR)
         << QApplication::translate("OpcodeGenerator", "int32_t", Q_NULLPTR)
         << QApplication::translate("OpcodeGenerator", "uint64_t", Q_NULLPTR)
         << QApplication::translate("OpcodeGenerator", "struct", Q_NULLPTR)
         << QApplication::translate("OpcodeGenerator", "RXFIRConfig", Q_NULLPTR)
         << QApplication::translate("OpcodeGenerator", "TxFIRConfig", Q_NULLPTR)
        );
        logo->setText(QString());
        Param1_slider_val->setText(QString());
        Param2_slider_val->setText(QString());
        max_p1_val->setText(QApplication::translate("OpcodeGenerator", "MaxP1", Q_NULLPTR));
        min_p1_val->setText(QApplication::translate("OpcodeGenerator", "MinP1", Q_NULLPTR));
        max_p2_val->setText(QApplication::translate("OpcodeGenerator", "MaxP2", Q_NULLPTR));
        min_p2_val->setText(QApplication::translate("OpcodeGenerator", "MinP2", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("OpcodeGenerator", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class OpcodeGenerator: public Ui_OpcodeGenerator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // SAMPLE_H
