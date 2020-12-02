#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include "my_mainwindow.h"


char seter_strings[set_cmd_size][22] = 
{
    SET_STRING_COLLECTION()
};

std::unordered_map<std::string, std::vector<std::pair<int, int>>> bounds = 
{
    {seter_strings[en_state_machine_mode], {std::make_pair(0,7)}},
    {seter_strings[rf_gain],               {std::make_pair(0,1),std::make_pair(-4,71)}},
    {seter_strings[rf_bandwidth],          {std::make_pair(0,56000000)}},
    {seter_strings[sampling_freq],         {std::make_pair(0,61440000)}},
    {seter_strings[lo_freq],               {std::make_pair(70000000,2147483647)}},
    {seter_strings[lo_int_ex],             {std::make_pair(0,1)}},
    {seter_strings[gain_control_mode],     {std::make_pair(0,1),std::make_pair(0,3)}},
    //the weird ones
    {seter_strings[fir_config],            {std::make_pair(0,0)}},
    {seter_strings[path_clk],              {std::make_pair(0,0)}},
    
    {seter_strings[fir_en_dis],            {std::make_pair(0,1)}},
    {seter_strings[rfdc_track_en_dis],     {std::make_pair(0,1)}},
    {seter_strings[bbdc_track_en_dis],     {std::make_pair(0,1)}},
    {seter_strings[quad_track_en_dis],     {std::make_pair(0,1)}},
    {seter_strings[rf_port_input],         {std::make_pair(0,11)}},
    {seter_strings[rf_port_output],        {std::make_pair(0,1)}},
    {seter_strings[attenuation],           {std::make_pair(0,1),std::make_pair(0,89750)}},
    {seter_strings[set_no_ch_mod],         {std::make_pair(1,2)}},
    {seter_strings[rate_gov],              {std::make_pair(0,1)}},
    {seter_strings[auto_cal_en_dis],       {std::make_pair(0,1)}},

};


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
        SLOT(set_get_menu_changed(QString))
    );
    connect(
        tx_rx_menu,
        SIGNAL(currentTextChanged(QString)),
        this,
        SLOT(tx_rx_menu_changed(QString))
    );
        connect(
        API_menu,
        SIGNAL(currentTextChanged(QString)),
        this,
        SLOT(API_menu_trigger(QString))
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
void MainWindow :: set_get_menu_changed(const QString &text)
{
    std::string box_str = text.toUtf8().constData();
    static QStringList normal_state;
    static bool need_refresh = false;
    if(box_str == "do")
    {
        if(!need_refresh)
        {
            need_refresh = true;
            
            Save_TX_RX_STATE();

            CLR(tx_rx_menu);
            tx_rx_menu->insertItems(0, QStringList() PUSH_TO_LIST("None"));

            CLR(API_menu);
            API_menu->insertItems(0, QStringList()
                DO_API_LIST
            );
        }
    }
    else
    {
        if(need_refresh)
        {
            need_refresh = false;
            API_menu->clear();
            tx_rx_menu->clear();
            tx_rx_menu->insertItems(0,normal_state); // get SAVED STATE
            normal_state.clear();
        }

    }
    
    //qDebug()<<text;
    
}

void MainWindow :: Slider_Calc(std::string& str)
{
    //printf("API-set menu trigger : %s\r\n",str.c_str());

    Param_1_val->setRange(bounds[str][0].first,bounds[str][0].second);
    min_p1_val->setText(QApplication::translate("OpcodeGenerator", std::to_string(bounds[str][0].first).c_str(), Q_NULLPTR));
    max_p1_val->setText(QApplication::translate("OpcodeGenerator", std::to_string(bounds[str][0].second).c_str(), Q_NULLPTR));

    if(bounds[str].size() == 2)
    {
        Param_2_val->setRange(bounds[str][1].first,bounds[str][1].second);
        min_p2_val->setText(QApplication::translate("OpcodeGenerator", std::to_string(bounds[str][1].first).c_str(), Q_NULLPTR));
        max_p2_val->setText(QApplication::translate("OpcodeGenerator", std::to_string(bounds[str][1].second).c_str(), Q_NULLPTR));
    }
    else
    {
        Param_2_val->setRange(0,0);
        min_p2_val->setText(QApplication::translate("OpcodeGenerator", "None", Q_NULLPTR));
        max_p2_val->setText(QApplication::translate("OpcodeGenerator", "None", Q_NULLPTR));
    }

    

}

void MainWindow :: tx_rx_menu_changed(const QString &text)
{
    std::string box_str = text.toUtf8().constData();
    //std::cout<<box_str<<std::endl;
    int set_get_state = set_get_menu->currentIndex();

    if(set_get_state == NONE_param)
    {
        if(box_str == "TRX")
        {
            API_menu->clear();
            API_menu->insertItems(0, QStringList() PUSH_TO_LIST("load_enable_fir") );
        }
        else if(box_str == "None")
        {
            API_menu->clear();
        }
        else
        {
            API_menu->clear();
            API_menu->insertItems(0, QStringList() NONE_TX_LIST );
        }
    }
    else if(set_get_state == Set_param)
    {
        API_menu->clear();
        //change slider values
        if(box_str == "TX")
        {
            API_menu->insertItems(0, QStringList() SET_API_TX_LIST );
        }
        else if(box_str == "RX")
        {
             API_menu->insertItems(0, QStringList() SET_API_RX_LIST );
        }
        else if(box_str == "TRX")
        {
             API_menu->insertItems(0, QStringList() SET_API_TRX_LIST );
        }
    }
    else if(set_get_state == Get_param)
    {
        API_menu->clear();
        if(box_str == "TX")
        {
            API_menu->insertItems(0, QStringList() GET_API_TX_LIST );
        }
        else if(box_str == "RX")
        {
             API_menu->insertItems(0, QStringList() GET_API_RX_LIST );
        }
        else if(box_str == "TRX")
        {
             API_menu->insertItems(0, QStringList() GET_API_TRX_LIST );
        }
        else
        {
            printf("NONE\r\n");
        }
    }
}
void MainWindow ::API_menu_trigger(const QString &text)
{
    int set_get_state = set_get_menu->currentIndex();
    std::string box_str = text.toUtf8().constData();
    if(set_get_state == Set_param && !box_str.empty())
    {
        this->Slider_Calc(box_str);
    }
}