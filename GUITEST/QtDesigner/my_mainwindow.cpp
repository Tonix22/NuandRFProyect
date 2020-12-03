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
 *********************API OPCODE MAP***************************
 *************************************************************/

std::unordered_map<std::string,int> ID_LUT =
{
    LUT_VALUE_DEF()
};

/**************************************************************
 *********************TX_RX OPCODE MAP*************************
 *************************************************************/
int tx_rx_map[tx_rx_size] = {NONE_param_tx_rx, Rx_parm, Tx_param, Trx_param};

/**************************************************************
 *********************Types OPCODE MAP*************************
 *************************************************************/

char params_strings[Params_set_size][9] = 
{
    TYPES_STR_SEQ()
};
char ID_to_TYPE_OPCODE[31] = 
{
    No_param << 3 | u32int, // en_state_machine_mode
    s32int   << 3 | u8int, // rf_gain
    No_param << 3 | u32int, // rf_bandwidth
    No_param << 3 | u32int, // sampling_freq
    No_param << 3 | u64int, // lo_freq
    No_param << 3 | u8int , //lo_int_ext
    struct_param << 3 | u8int , //rssi
    u8int    << 3 | u8int, // gain_control_mode
    No_param << 3 | RXFIR, // set_fir_config
    No_param << 3 | RXFIR, // get_fir_config
    No_param << 3 | u8int, // fir_en_dis
    No_param << 3 | u8int, // rfdc_track_en_dis
    No_param << 3 | u8int, // bbdc_track_en_dis
    No_param << 3 | u8int, // quad_track_en_dis
    No_param << 3 | u32int,//rf_port_input
    No_param << 3 | u32int,//fastlock_store
    No_param << 3 | u32int,//fastlock_recall
    u8int    << 3 | u32int,//fastlock_load
    u8int    << 3 | u32int, //fastlock_save
    u32int   << 3 | u8int, //attenuation
    No_param << 3 | u32int,//rf_port_output
    No_param << 3 | u8int, //auto_cal_en_dis
    u32int   << 3 | u32int,//path_clk
    No_param << 3 | u8int, //no_ch_mode
    No_param << 3 |struct_param,//mcs
    No_param << 3 | u8int, //fir_en_dis
    No_param << 3 | u32int,//rate_gov
    s32int   << 3 | u32int,//calib
    TXFIR    << 3 | RXFIR, //load_enable_fir
    No_param << 3 | u32int,//dcxo_tune_coarse
    No_param << 3 | u32int,//dcxo_tune_fine
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
    connect(
        Param2_input_text,
        SIGNAL(textChanged()),
        this,
        SLOT(Text_param2_changed())
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
    int set_get_state   = set_get_menu->currentIndex();
    int tx_rx_stare     = tx_rx_map[tx_rx_menu->currentIndex()];
    int API_state       = ID_LUT[API_menu->currentText().toUtf8().constData()];
    int Params          = ID_to_TYPE_OPCODE[API_state];
    int OPCODE          = set_get_state | (tx_rx_stare<<2) | (API_state<<4) | (Params<<10);
    printf("set_get_state: %d\r\n",set_get_state);
    printf("tx_rx_stare: %d\r\n",tx_rx_stare);
    printf("API_state: %d\r\n",API_state);
    printf("OPCODE: %X\r\n",OPCODE);
    
    //qDebug()<<" param1 "<< Param1_slider_val->text();
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
    int API_state       = ID_LUT[box_str];
    //printf("P1: %s, ",params_strings[Param_mask_1(ID_to_TYPE_OPCODE[API_state])] );
    //printf("P2: %s\r\n",params_strings[Param_mask_2(ID_to_TYPE_OPCODE[API_state])] );
    param1_label->setText(TRANSLATE(params_strings[Param_mask_1(ID_to_TYPE_OPCODE[API_state])]));
    param2_label->setText(TRANSLATE(params_strings[Param_mask_2(ID_to_TYPE_OPCODE[API_state])]));
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

void MainWindow :: Text_input_register(std::string& msg,int index)
{

    std::string temp    = (*(ParamN_input_text[index]))->toPlainText().toUtf8().constData();
    int  set_get_state  = set_get_menu->currentIndex();
    std::string API_str = API_menu->currentText().toUtf8().constData();
    int value_proc = 0;
    
    if(temp.back() != '\n')
    {
        msg = temp;
    }
    else
    {
        std::cout<<msg<<std::endl;
        value_proc = Text_Processing(msg);    

        (*(Param_N_val[index]))->setValue(value_proc);
        (*(Param_N_val[index]))->setSliderPosition(value_proc);
        (*(ParamN_slider_val[index]))->setText(msg.c_str());
        if(set_get_state == Set_param )
        {
            if((bounds[API_str][index].first <= value_proc) && 
               (value_proc <= bounds[API_str][index].second))
            {
               (*(ParamN_slider_val[index]))->setText(msg.c_str());
            }
            else
            {
                (*(ParamN_slider_val[index]))->setText("Invalid");
            }
        }
        (*(ParamN_input_text[index]))->clear();
    }
}

void MainWindow :: Text_param1_changed()
{
    static std::string param1_str;
    Text_input_register(param1_str,0);
    
}
void MainWindow :: Text_param2_changed()
{
    static std::string param2_str;
    Text_input_register(param2_str,1);
}