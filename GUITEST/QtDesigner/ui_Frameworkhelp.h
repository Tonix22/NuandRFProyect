/********************************************************************************
** Form generated from reading UI file 'Frameworkhelp.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRAMEWORKHELP_H
#define UI_FRAMEWORKHELP_H

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
#include <QtWidgets/QPlainTextEdit>
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
    QSlider *Param_2_val;
    QLabel *param2_up_label;
    QLabel *param2_up_label_2;
    QLabel *tx_rx_label;
    QLabel *param1_label;
    QLabel *param2_label;
    QPushButton *SendData;
    QLabel *logo;
    QLabel *Param1_slider_val;
    QLabel *Param2_slider_val;
    QLabel *max_p1_val;
    QLabel *min_p1_val;
    QLabel *max_p2_val;
    QLabel *min_p2_val;
    QComboBox *API_menu;
    QLabel *API_label;
    QLabel *myname;
    QPlainTextEdit *Param1_input_text;
    QPlainTextEdit *plainTextEdit_2;
    QLabel *Insert_Opcode_label;
    QPlainTextEdit *Opcode_input_text;
    QLabel *Get_result_label;
    QLabel *Show_get_result;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *OpcodeGenerator)
    {
        if (OpcodeGenerator->objectName().isEmpty())
            OpcodeGenerator->setObjectName(QStringLiteral("OpcodeGenerator"));
        OpcodeGenerator->resize(738, 540);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(61, 60, 60, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(136, 138, 133, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(76, 75, 75, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(30, 30, 30, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(40, 40, 40, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush6(QColor(0, 0, 0, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        QBrush brush7(QColor(85, 87, 83, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush7);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush4);
        QBrush brush8(QColor(255, 255, 220, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        OpcodeGenerator->setPalette(palette);
        centralwidget = new QWidget(OpcodeGenerator);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        Param_1_val = new QSlider(centralwidget);
        Param_1_val->setObjectName(QStringLiteral("Param_1_val"));
        Param_1_val->setGeometry(QRect(150, 240, 160, 24));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        QBrush brush9(QColor(0, 249, 255, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush9);
        QBrush brush10(QColor(127, 252, 255, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush10);
        QBrush brush11(QColor(63, 250, 255, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush11);
        QBrush brush12(QColor(0, 124, 127, 255));
        brush12.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush12);
        QBrush brush13(QColor(0, 166, 170, 255));
        brush13.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush13);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush6);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush6);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush9);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush10);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush9);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush10);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush11);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush12);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush13);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush9);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush10);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush12);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush10);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush11);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush12);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush13);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush12);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush12);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        Param_1_val->setPalette(palette1);
        Param_1_val->setValue(50);
        Param_1_val->setSliderPosition(50);
        Param_1_val->setOrientation(Qt::Horizontal);
        set_get_menu = new QComboBox(centralwidget);
        set_get_menu->setObjectName(QStringLiteral("set_get_menu"));
        set_get_menu->setGeometry(QRect(590, 130, 110, 38));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        QBrush brush14(QColor(114, 159, 207, 255));
        brush14.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush14);
        QBrush brush15(QColor(196, 225, 255, 255));
        brush15.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Light, brush15);
        QBrush brush16(QColor(155, 192, 231, 255));
        brush16.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Midlight, brush16);
        QBrush brush17(QColor(57, 79, 103, 255));
        brush17.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Dark, brush17);
        QBrush brush18(QColor(76, 106, 138, 255));
        brush18.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Mid, brush18);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush6);
        palette2.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush6);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush14);
        palette2.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        QBrush brush19(QColor(184, 207, 231, 255));
        brush19.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::AlternateBase, brush19);
        palette2.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette2.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush14);
        palette2.setBrush(QPalette::Inactive, QPalette::Light, brush15);
        palette2.setBrush(QPalette::Inactive, QPalette::Midlight, brush16);
        palette2.setBrush(QPalette::Inactive, QPalette::Dark, brush17);
        palette2.setBrush(QPalette::Inactive, QPalette::Mid, brush18);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush14);
        palette2.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush19);
        palette2.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette2.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush17);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush14);
        palette2.setBrush(QPalette::Disabled, QPalette::Light, brush15);
        palette2.setBrush(QPalette::Disabled, QPalette::Midlight, brush16);
        palette2.setBrush(QPalette::Disabled, QPalette::Dark, brush17);
        palette2.setBrush(QPalette::Disabled, QPalette::Mid, brush18);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush17);
        palette2.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush17);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush14);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush14);
        palette2.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush14);
        palette2.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette2.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        set_get_menu->setPalette(palette2);
        do_set_get_label = new QLabel(centralwidget);
        do_set_get_label->setObjectName(QStringLiteral("do_set_get_label"));
        do_set_get_label->setGeometry(QRect(600, 100, 91, 22));
        QFont font;
        font.setFamily(QStringLiteral("Utopia"));
        font.setBold(true);
        font.setWeight(75);
        do_set_get_label->setFont(font);
        tx_rx_menu = new QComboBox(centralwidget);
        tx_rx_menu->setObjectName(QStringLiteral("tx_rx_menu"));
        tx_rx_menu->setGeometry(QRect(460, 130, 110, 38));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush14);
        palette3.setBrush(QPalette::Active, QPalette::Light, brush15);
        palette3.setBrush(QPalette::Active, QPalette::Midlight, brush16);
        palette3.setBrush(QPalette::Active, QPalette::Dark, brush17);
        palette3.setBrush(QPalette::Active, QPalette::Mid, brush18);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush6);
        palette3.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush6);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush14);
        palette3.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette3.setBrush(QPalette::Active, QPalette::AlternateBase, brush19);
        palette3.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette3.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush14);
        palette3.setBrush(QPalette::Inactive, QPalette::Light, brush15);
        palette3.setBrush(QPalette::Inactive, QPalette::Midlight, brush16);
        palette3.setBrush(QPalette::Inactive, QPalette::Dark, brush17);
        palette3.setBrush(QPalette::Inactive, QPalette::Mid, brush18);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush14);
        palette3.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette3.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush19);
        palette3.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette3.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush17);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush14);
        palette3.setBrush(QPalette::Disabled, QPalette::Light, brush15);
        palette3.setBrush(QPalette::Disabled, QPalette::Midlight, brush16);
        palette3.setBrush(QPalette::Disabled, QPalette::Dark, brush17);
        palette3.setBrush(QPalette::Disabled, QPalette::Mid, brush18);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush17);
        palette3.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush17);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush14);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush14);
        palette3.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette3.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush14);
        palette3.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette3.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        tx_rx_menu->setPalette(palette3);
        Param_2_val = new QSlider(centralwidget);
        Param_2_val->setObjectName(QStringLiteral("Param_2_val"));
        Param_2_val->setGeometry(QRect(150, 320, 160, 24));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        palette4.setBrush(QPalette::Active, QPalette::Button, brush9);
        QBrush brush20(QColor(126, 253, 255, 255));
        brush20.setStyle(Qt::SolidPattern);
        palette4.setBrush(QPalette::Active, QPalette::Light, brush20);
        QBrush brush21(QColor(63, 251, 255, 255));
        brush21.setStyle(Qt::SolidPattern);
        palette4.setBrush(QPalette::Active, QPalette::Midlight, brush21);
        palette4.setBrush(QPalette::Active, QPalette::Dark, brush12);
        palette4.setBrush(QPalette::Active, QPalette::Mid, brush13);
        palette4.setBrush(QPalette::Active, QPalette::Text, brush6);
        palette4.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette4.setBrush(QPalette::Active, QPalette::ButtonText, brush6);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush);
        palette4.setBrush(QPalette::Active, QPalette::Window, brush9);
        palette4.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette4.setBrush(QPalette::Active, QPalette::AlternateBase, brush10);
        palette4.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette4.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette4.setBrush(QPalette::Inactive, QPalette::Button, brush9);
        palette4.setBrush(QPalette::Inactive, QPalette::Light, brush20);
        palette4.setBrush(QPalette::Inactive, QPalette::Midlight, brush21);
        palette4.setBrush(QPalette::Inactive, QPalette::Dark, brush12);
        palette4.setBrush(QPalette::Inactive, QPalette::Mid, brush13);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush6);
        palette4.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::ButtonText, brush6);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Window, brush9);
        palette4.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette4.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush10);
        palette4.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette4.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush12);
        palette4.setBrush(QPalette::Disabled, QPalette::Button, brush9);
        palette4.setBrush(QPalette::Disabled, QPalette::Light, brush20);
        palette4.setBrush(QPalette::Disabled, QPalette::Midlight, brush21);
        palette4.setBrush(QPalette::Disabled, QPalette::Dark, brush12);
        palette4.setBrush(QPalette::Disabled, QPalette::Mid, brush13);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush12);
        palette4.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::ButtonText, brush12);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush9);
        palette4.setBrush(QPalette::Disabled, QPalette::Window, brush9);
        palette4.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette4.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush9);
        palette4.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette4.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        Param_2_val->setPalette(palette4);
        Param_2_val->setValue(50);
        Param_2_val->setOrientation(Qt::Horizontal);
        param2_up_label = new QLabel(centralwidget);
        param2_up_label->setObjectName(QStringLiteral("param2_up_label"));
        param2_up_label->setGeometry(QRect(210, 200, 68, 22));
        param2_up_label->setFont(font);
        param2_up_label_2 = new QLabel(centralwidget);
        param2_up_label_2->setObjectName(QStringLiteral("param2_up_label_2"));
        param2_up_label_2->setGeometry(QRect(200, 300, 68, 22));
        param2_up_label_2->setFont(font);
        tx_rx_label = new QLabel(centralwidget);
        tx_rx_label->setObjectName(QStringLiteral("tx_rx_label"));
        tx_rx_label->setGeometry(QRect(480, 100, 68, 22));
        tx_rx_label->setFont(font);
        param1_label = new QLabel(centralwidget);
        param1_label->setObjectName(QStringLiteral("param1_label"));
        param1_label->setGeometry(QRect(140, 140, 68, 22));
        param1_label->setFont(font);
        param2_label = new QLabel(centralwidget);
        param2_label->setObjectName(QStringLiteral("param2_label"));
        param2_label->setGeometry(QRect(30, 140, 68, 22));
        param2_label->setFont(font);
        SendData = new QPushButton(centralwidget);
        SendData->setObjectName(QStringLiteral("SendData"));
        SendData->setGeometry(QRect(550, 310, 99, 38));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        QBrush brush22(QColor(115, 210, 22, 255));
        brush22.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::Button, brush22);
        QBrush brush23(QColor(170, 255, 87, 255));
        brush23.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::Light, brush23);
        QBrush brush24(QColor(142, 232, 54, 255));
        brush24.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::Midlight, brush24);
        QBrush brush25(QColor(57, 105, 11, 255));
        brush25.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::Dark, brush25);
        QBrush brush26(QColor(76, 140, 14, 255));
        brush26.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::Mid, brush26);
        palette5.setBrush(QPalette::Active, QPalette::Text, brush6);
        palette5.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette5.setBrush(QPalette::Active, QPalette::ButtonText, brush6);
        palette5.setBrush(QPalette::Active, QPalette::Base, brush);
        palette5.setBrush(QPalette::Active, QPalette::Window, brush22);
        palette5.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        QBrush brush27(QColor(185, 232, 138, 255));
        brush27.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::AlternateBase, brush27);
        palette5.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette5.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette5.setBrush(QPalette::Inactive, QPalette::Button, brush22);
        palette5.setBrush(QPalette::Inactive, QPalette::Light, brush23);
        palette5.setBrush(QPalette::Inactive, QPalette::Midlight, brush24);
        palette5.setBrush(QPalette::Inactive, QPalette::Dark, brush25);
        palette5.setBrush(QPalette::Inactive, QPalette::Mid, brush26);
        palette5.setBrush(QPalette::Inactive, QPalette::Text, brush6);
        palette5.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::ButtonText, brush6);
        palette5.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Window, brush22);
        palette5.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette5.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush27);
        palette5.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette5.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush25);
        palette5.setBrush(QPalette::Disabled, QPalette::Button, brush22);
        palette5.setBrush(QPalette::Disabled, QPalette::Light, brush23);
        palette5.setBrush(QPalette::Disabled, QPalette::Midlight, brush24);
        palette5.setBrush(QPalette::Disabled, QPalette::Dark, brush25);
        palette5.setBrush(QPalette::Disabled, QPalette::Mid, brush26);
        palette5.setBrush(QPalette::Disabled, QPalette::Text, brush25);
        palette5.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::ButtonText, brush25);
        palette5.setBrush(QPalette::Disabled, QPalette::Base, brush22);
        palette5.setBrush(QPalette::Disabled, QPalette::Window, brush22);
        palette5.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette5.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush22);
        palette5.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette5.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        SendData->setPalette(palette5);
        QFont font1;
        font1.setFamily(QStringLiteral("Utopia"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setItalic(true);
        font1.setWeight(75);
        SendData->setFont(font1);
        logo = new QLabel(centralwidget);
        logo->setObjectName(QStringLiteral("logo"));
        logo->setGeometry(QRect(270, 10, 141, 81));
        logo->setContextMenuPolicy(Qt::NoContextMenu);
        logo->setPixmap(QPixmap(QString::fromUtf8(":/icon/external-content.duckduckgo.com.png")));
        logo->setScaledContents(true);
        Param1_slider_val = new QLabel(centralwidget);
        Param1_slider_val->setObjectName(QStringLiteral("Param1_slider_val"));
        Param1_slider_val->setGeometry(QRect(220, 260, 68, 22));
        Param2_slider_val = new QLabel(centralwidget);
        Param2_slider_val->setObjectName(QStringLiteral("Param2_slider_val"));
        Param2_slider_val->setGeometry(QRect(210, 340, 68, 22));
        max_p1_val = new QLabel(centralwidget);
        max_p1_val->setObjectName(QStringLiteral("max_p1_val"));
        max_p1_val->setGeometry(QRect(330, 240, 68, 22));
        max_p1_val->setFont(font);
        min_p1_val = new QLabel(centralwidget);
        min_p1_val->setObjectName(QStringLiteral("min_p1_val"));
        min_p1_val->setGeometry(QRect(60, 240, 68, 22));
        min_p1_val->setFont(font);
        max_p2_val = new QLabel(centralwidget);
        max_p2_val->setObjectName(QStringLiteral("max_p2_val"));
        max_p2_val->setGeometry(QRect(330, 320, 68, 22));
        max_p2_val->setFont(font);
        min_p2_val = new QLabel(centralwidget);
        min_p2_val->setObjectName(QStringLiteral("min_p2_val"));
        min_p2_val->setGeometry(QRect(60, 320, 68, 22));
        min_p2_val->setFont(font);
        API_menu = new QComboBox(centralwidget);
        API_menu->setObjectName(QStringLiteral("API_menu"));
        API_menu->setGeometry(QRect(230, 130, 201, 38));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        palette6.setBrush(QPalette::Active, QPalette::Button, brush14);
        palette6.setBrush(QPalette::Active, QPalette::Light, brush15);
        palette6.setBrush(QPalette::Active, QPalette::Midlight, brush16);
        palette6.setBrush(QPalette::Active, QPalette::Dark, brush17);
        palette6.setBrush(QPalette::Active, QPalette::Mid, brush18);
        palette6.setBrush(QPalette::Active, QPalette::Text, brush6);
        palette6.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette6.setBrush(QPalette::Active, QPalette::ButtonText, brush6);
        palette6.setBrush(QPalette::Active, QPalette::Base, brush);
        palette6.setBrush(QPalette::Active, QPalette::Window, brush14);
        palette6.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette6.setBrush(QPalette::Active, QPalette::AlternateBase, brush19);
        palette6.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette6.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette6.setBrush(QPalette::Inactive, QPalette::Button, brush14);
        palette6.setBrush(QPalette::Inactive, QPalette::Light, brush15);
        palette6.setBrush(QPalette::Inactive, QPalette::Midlight, brush16);
        palette6.setBrush(QPalette::Inactive, QPalette::Dark, brush17);
        palette6.setBrush(QPalette::Inactive, QPalette::Mid, brush18);
        palette6.setBrush(QPalette::Inactive, QPalette::Text, brush6);
        palette6.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::ButtonText, brush6);
        palette6.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Window, brush14);
        palette6.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette6.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush19);
        palette6.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette6.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush17);
        palette6.setBrush(QPalette::Disabled, QPalette::Button, brush14);
        palette6.setBrush(QPalette::Disabled, QPalette::Light, brush15);
        palette6.setBrush(QPalette::Disabled, QPalette::Midlight, brush16);
        palette6.setBrush(QPalette::Disabled, QPalette::Dark, brush17);
        palette6.setBrush(QPalette::Disabled, QPalette::Mid, brush18);
        palette6.setBrush(QPalette::Disabled, QPalette::Text, brush17);
        palette6.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::ButtonText, brush17);
        palette6.setBrush(QPalette::Disabled, QPalette::Base, brush14);
        palette6.setBrush(QPalette::Disabled, QPalette::Window, brush14);
        palette6.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette6.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush14);
        palette6.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette6.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        API_menu->setPalette(palette6);
        API_label = new QLabel(centralwidget);
        API_label->setObjectName(QStringLiteral("API_label"));
        API_label->setGeometry(QRect(320, 100, 68, 22));
        API_label->setFont(font);
        myname = new QLabel(centralwidget);
        myname->setObjectName(QStringLiteral("myname"));
        myname->setGeometry(QRect(540, 420, 131, 22));
        QFont font2;
        font2.setFamily(QStringLiteral("Utopia"));
        font2.setItalic(true);
        myname->setFont(font2);
        Param1_input_text = new QPlainTextEdit(centralwidget);
        Param1_input_text->setObjectName(QStringLiteral("Param1_input_text"));
        Param1_input_text->setGeometry(QRect(400, 240, 104, 31));
        plainTextEdit_2 = new QPlainTextEdit(centralwidget);
        plainTextEdit_2->setObjectName(QStringLiteral("plainTextEdit_2"));
        plainTextEdit_2->setGeometry(QRect(400, 310, 104, 31));
        Insert_Opcode_label = new QLabel(centralwidget);
        Insert_Opcode_label->setObjectName(QStringLiteral("Insert_Opcode_label"));
        Insert_Opcode_label->setGeometry(QRect(550, 200, 121, 22));
        Insert_Opcode_label->setFont(font);
        Opcode_input_text = new QPlainTextEdit(centralwidget);
        Opcode_input_text->setObjectName(QStringLiteral("Opcode_input_text"));
        Opcode_input_text->setGeometry(QRect(550, 240, 104, 31));
        Get_result_label = new QLabel(centralwidget);
        Get_result_label->setObjectName(QStringLiteral("Get_result_label"));
        Get_result_label->setGeometry(QRect(280, 370, 101, 22));
        Get_result_label->setFont(font);
        Show_get_result = new QLabel(centralwidget);
        Show_get_result->setObjectName(QStringLiteral("Show_get_result"));
        Show_get_result->setGeometry(QRect(200, 390, 241, 51));
        QFont font3;
        font3.setFamily(QStringLiteral("Utopia"));
        font3.setPointSize(11);
        font3.setBold(true);
        font3.setWeight(75);
        Show_get_result->setFont(font3);
        Show_get_result->setAlignment(Qt::AlignCenter);
        OpcodeGenerator->setCentralWidget(centralwidget);
        menubar = new QMenuBar(OpcodeGenerator);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 738, 30));
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
         << QApplication::translate("OpcodeGenerator", "None", Q_NULLPTR)
         << QApplication::translate("OpcodeGenerator", "TX", Q_NULLPTR)
         << QApplication::translate("OpcodeGenerator", "RX", Q_NULLPTR)
         << QApplication::translate("OpcodeGenerator", "TRX", Q_NULLPTR)
        );
        param2_up_label->setText(QApplication::translate("OpcodeGenerator", "Param1", Q_NULLPTR));
        param2_up_label_2->setText(QApplication::translate("OpcodeGenerator", "Param2", Q_NULLPTR));
        tx_rx_label->setText(QApplication::translate("OpcodeGenerator", "Tx,Rx,Trx", Q_NULLPTR));
        param1_label->setText(QApplication::translate("OpcodeGenerator", "Param1", Q_NULLPTR));
        param2_label->setText(QApplication::translate("OpcodeGenerator", "Param2", Q_NULLPTR));
        SendData->setText(QApplication::translate("OpcodeGenerator", "Send", Q_NULLPTR));
        logo->setText(QString());
        Param1_slider_val->setText(QString());
        Param2_slider_val->setText(QString());
        max_p1_val->setText(QApplication::translate("OpcodeGenerator", "MaxP1", Q_NULLPTR));
        min_p1_val->setText(QApplication::translate("OpcodeGenerator", "MinP1", Q_NULLPTR));
        max_p2_val->setText(QApplication::translate("OpcodeGenerator", "MaxP2", Q_NULLPTR));
        min_p2_val->setText(QApplication::translate("OpcodeGenerator", "MinP2", Q_NULLPTR));
        API_menu->clear();
        API_menu->insertItems(0, QStringList()
         << QApplication::translate("OpcodeGenerator", "None", Q_NULLPTR)
        );
        API_label->setText(QApplication::translate("OpcodeGenerator", "API", Q_NULLPTR));
        myname->setText(QApplication::translate("OpcodeGenerator", "Designed by Tonix", Q_NULLPTR));
        Param1_input_text->setPlaceholderText(QApplication::translate("OpcodeGenerator", "50", Q_NULLPTR));
        plainTextEdit_2->setPlaceholderText(QApplication::translate("OpcodeGenerator", "50", Q_NULLPTR));
        Insert_Opcode_label->setText(QApplication::translate("OpcodeGenerator", "Insert OpCode", Q_NULLPTR));
        Opcode_input_text->setPlaceholderText(QApplication::translate("OpcodeGenerator", "0x0000", Q_NULLPTR));
        Get_result_label->setText(QApplication::translate("OpcodeGenerator", "GET RESULT", Q_NULLPTR));
        Show_get_result->setText(QApplication::translate("OpcodeGenerator", "None", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("OpcodeGenerator", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class OpcodeGenerator: public Ui_OpcodeGenerator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRAMEWORKHELP_H
