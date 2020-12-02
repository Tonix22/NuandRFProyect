#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <iostream>
#include <string>
#include "string.h"
#include <unordered_map>
#include <utility>
#include<cmath>
#include "my_mainwindow.h"

/**************************************************************
 *********************SETER STRING VARIABLES*******************
 *************************************************************/

char seter_strings[set_cmd_size][MAX_SET_STRING_SIZE] = 
{
    SET_STRING_COLLECTION()
};

std::unordered_map<std::string, std::vector<std::pair<int, int>>> bounds = 
{
    DATA_RANGES()
};

/**************************************************************
 *********************SIGNALS DECLARATION**********************
 *************************************************************/

MainWindow::MainWindow(QWidget *parent) :  QMainWindow(parent)
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
    connect(
        Param1_input_text,
        SIGNAL(textChanged()),
        this,
        SLOT(Text_param1_changed())

    );
    this->show();
}
MainWindow::~MainWindow()
{
    //delete ui;
}

/**************************************************************
 ************************ACTIONS******************************
 *************************************************************/


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
 
}

void MainWindow :: Slider_Calc(std::string& str)
{
    //printf("API-set menu trigger : %s\r\n",str.c_str());

    Param_1_val->setRange(bounds[str][0].first,bounds[str][0].second);
    
    min_p1_val->setText(TRANSLATE (std::to_string(bounds[str][0].first).c_str()));
    max_p1_val->setText(TRANSLATE (std::to_string(bounds[str][0].second).c_str()));

    if(bounds[str].size() == 2)
    {
        Param_2_val->setRange(bounds[str][1].first,bounds[str][1].second);
        min_p2_val->setText(TRANSLATE (std::to_string(bounds[str][1].first).c_str()));
        max_p2_val->setText(TRANSLATE (std::to_string(bounds[str][1].second).c_str()));
    }
    else
    {
        Param_2_val->setRange(0,0);
        min_p2_val->setText(TRANSLATE ("None"));
        max_p2_val->setText(TRANSLATE ("None"));
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

int MainWindow::Text_Processing(std::string& msg)
{
    int offset = 0;
    std::size_t found;
    int num = 0;
    bool notation = false;
    int multipliyer = 0;
    std::string left = "0";
    std::string right= "0";

    if(msg.find("M")!=std::string::npos
    || msg.find("K")!=std::string::npos)
    {
        notation = true;

        found  = msg.find(".");
        if (found != std::string::npos)
        {
            left   = msg.substr(0, found);
            offset = found+1;
            found  = msg.find("M");
            multipliyer = 1000000;
            if (found == std::string::npos)
            {
                found  = msg.find("K");
                multipliyer = 1000;
            }
            right  = msg.substr(offset, found-offset);
        }
        else
        {
            found  = msg.find("M");
            left   = msg.substr(0, found);
            multipliyer = 1000000;
            if (found == std::string::npos)
            {
                multipliyer = 1000;
            }
        }
    }
    try
    {
        if(notation)
        {
            num += std::stoi(left)*multipliyer;
            num += std::stoi(right)*multipliyer/pow(10,right.size());
        }
        else
        {
            num = std::stoi(msg);
        }
    }
    catch (const std::invalid_argument & e){
        std::cout << e.what() << "\n";
    }
    catch (const std::out_of_range & e){
        std::cout << e.what() << "\n";
    }
    return num;

}

void MainWindow :: Text_param1_changed()
{
    static std::string param1_str;
    std::string temp    = Param1_input_text->toPlainText().toUtf8().constData();
    int  set_get_state   = set_get_menu->currentIndex();
    std::string API_str = API_menu->currentText().toUtf8().constData();
    int value_proc = 0;
    
    if(temp.back() != '\n')
    {
        param1_str = temp;
    }
    else
    {
        std::cout<<param1_str<<std::endl;
        value_proc = Text_Processing(param1_str);    

        Param_1_val->setValue(value_proc);
        Param_1_val->setSliderPosition(value_proc);
        Param1_slider_val->setText(param1_str.c_str());
        if(set_get_state == Set_param )
        {
            if((bounds[API_str][0].first <= value_proc) && 
               (value_proc <= bounds[API_str][0].second))
            {
                Param1_slider_val->setText(param1_str.c_str());
            }
            else
            {
                Param1_slider_val->setText("Invalid");
            }
        }
            
        Param1_input_text->clear();
    }
    
}