#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <iostream>
#include <string>
#include <stdint.h>
#include "string.h"
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <cmath>
#include "bridge.h"
#include "my_mainwindow.h"


IPDI_Bridge* bridge;
uint64_t frequency_set = 0x0LL;
uint64_t frequency_get = 0x0LL;
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

char ID_LUT[LUT_NUM_ITEMS][LUT_MAX_STRING] =
{
    LUT_VALUE_DEF()
};


/**************************************************************
 *********************Types OPCODE MAP*************************
 *************************************************************/

char params_strings[Params_set_size][9] = 
{
    TYPES_STR_SEQ()
};
char ID_to_TYPE_OPCODE[30] = 
{
    No_param << 3 | u32int, // en_state_machine_mode
    s32int   << 3 | u8int, // rf_gain
    No_param << 3 | u32int, // rf_bandwidth
    No_param << 3 | u32int, // sampling_freq
    No_param << 3 | u64int, // lo_freq
    No_param << 3 | u8int , //lo_int_ext
    struct_param << 3 | u8int , //rssi
    u8int    << 3 | u8int, // gain_control_mode
    No_param << 3 | TXFIR, // set_fir_config
    TXFIR << 3    | u8int, // get_fir_config
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
    No_param << 3 | u32int,//rate_gov
    s32int   << 3 | u32int,//calib
    TXFIR    << 3 | RXFIR, //load_enable_fir
    No_param << 3 | u32int,//dcxo_tune_coarse
    No_param << 3 | u32int,//dcxo_tune_fine
};


/**************************************************************
 ***********************Special Ones**************************
 *************************************************************/

std::unordered_set<int> Large_items_APIS_set = 
{
    Special_ones_IDS()
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
    connect(
        Opcode_input_text,
        SIGNAL(textChanged()),
        this,
        SLOT(Opcode_to_GUI())
    );

    bridge = new IPDI_Bridge();
    this->show();
}
MainWindow::~MainWindow()
{
    delete bridge;
}

/**************************************************************
 ************************FILE EXPLORER*************************
 *************************************************************/
void MainWindow ::Special_ones(int id)
{
    QString filter = "Text File (*.txt*) ;; All File (*.*)";
    QString file_name = QFileDialog::getOpenFileName(this,"List of Parameters",QDir::currentPath(),filter);
    QMessageBox::information(this,"struct selected",file_name);
    QFile file(file_name);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"title", "file not open");
    }
    QTextStream in(&file);
    QString text = in.readAll();
    file.close();
}

/**************************************************************
 ************************SEND DATA******************************
 *************************************************************/

void MainWindow :: onButtonClicked()
{
    int set_get_state   = set_get_menu->currentIndex();
    int tx_rx_stare     = tx_rx_menu->currentIndex();
    int API_state       = 0;
    std::string API_str = API_menu->currentText().toUtf8().constData();
    int Params          = 0;
    int OPCODE          = 0;
    char str_opcode[7]  = {0,0,0,0,0,0,0};
    for(int i=0;i<30;i++)
    {
        if(ID_LUT[i] == API_str)
        {
            API_state = i;
            break;
        }
    }
    Params = ID_to_TYPE_OPCODE[API_state];
    SPECIAL_CASE_FIR_BUTTON()
    OPCODE = set_get_state | (tx_rx_stare<<2) | (API_state<<4) | (Params<<10);
    sprintf(str_opcode,"0x%X",OPCODE);
    Opcode_input_text->setPlainText(str_opcode);
    

    std::cout<<"set_get_state: " << set_get_state << std::endl;
    std::cout<<"tx_rx_stare: " << tx_rx_stare << std::endl;
    std::cout<<"API_state: " << API_state << std::endl;
    std::cout<<"OPCODE: " << OPCODE << std::endl;


    bridge->data_in.op =  OPCODE;
    

    if(Large_items_APIS_set.find(OPCODE) != Large_items_APIS_set.end())
    {
        //bridge->data_in.large_data
        //bridge->data_in.ld_size
        Special_ones(API_state);
    }
    if(strcmp(API_menu->currentText().toUtf8().constData(), seter_strings[lo_freq]) == 0)
    {
        printf("set Frequency to %lu \r\n",frequency_set);
    }
    if(set_get_state == Set_param || set_get_state == Do_param)
    {
        Load_Sliders_Val_to_bridge();
        bridge->WriteData();
    }
    else if(set_get_state == Get_param)
    {
        bridge->ReadData();
    }
    
    //qDebug()<<" param1 "<< Param1_slider_val->text();
}

/**************************************************************
 ************************UPDATE MENU *************************
 *************************************************************/


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
        tx_rx_menu->setCurrentIndex(1);
        tx_rx_menu->setCurrentIndex(0);
    }
 
}


void MainWindow :: Frequency_display()
{
    uint64_t extend  = ((uint64_t)Param_1_val->value())+Param_2_val->value();
    uint64_t temp = extend;
    char power = 0;
    int integers = 0;
    std::string ouput_string;
    std::string merge;
    char scientific = 0;
    while(temp!=0)
    {
        power++;
        temp/=10;
    }
    scientific = power/3;
    integers   = power%3;

    if(integers == 0)
    {
        integers = 3;
        scientific--;
    }
    
    merge = std::to_string(extend).substr(0, integers) +"."+ std::to_string(extend).substr(integers);
    merge.erase ( merge.find_last_not_of('0') + 1, std::string::npos );
    merge = merge.substr(0,std::min(5,(int)merge.size()));


    switch (scientific)  {
    case 1:
        merge+="K";
        break;

    case 2:
        merge+="M";
        break;

    case 3:
        merge+="G";
        break;

    }

    (*(ParamN_slider_val[0]))->setText(merge.c_str());
}

void MainWindow :: Slider_Calc(std::string& str)
{
    //printf("API-set menu trigger : %s\r\n",str.c_str());
    static bool frecuency_displayer = false;
    if(strcmp(str.c_str(), seter_strings[lo_freq]) == 0)
    {
        Param_1_val->setRange(bounds[str][0].first,bounds[str][0].second);
        min_p1_val->setText(TRANSLATE (std::to_string(bounds[str][0].first).c_str()));
        max_p1_val->setText(TRANSLATE ("5 GHz"));
        Param_2_val->setRange(0,2147483647);
        min_p2_val->setText(TRANSLATE ("Offset +"));
        max_p2_val->setText(TRANSLATE ("Offset +"));
        
        Param_2_val->disconnect();
        Param_1_val->disconnect();
        QObject::connect(Param_1_val, &QSlider::sliderMoved, this, Frequency_display);
        QObject::connect(Param_2_val, &QSlider::sliderMoved, this, Frequency_display);
        frecuency_displayer = true;
        return;  
    }
    if(frecuency_displayer)
    {
        frecuency_displayer = false;
        QObject::connect(Param_1_val, SIGNAL(sliderMoved(int)), (*(ParamN_slider_val[0])), SLOT(setNum(int)));
        QObject::connect(Param_2_val, SIGNAL(sliderMoved(int)), (*(ParamN_slider_val[1])), SLOT(setNum(int)));
    }

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
        API_menu->clear();
        if(box_str == "TRX")
        {
            API_menu->insertItems(0, QStringList() PUSH_TO_LIST("load_enable_fir") );
        }
        else if(box_str == "TX" || box_str == "RX")
        {
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
        else
        {
            API_menu->insertItems(0, QStringList() SET_API_NONE_LIST );
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
            API_menu->insertItems(0, QStringList() PUSH_TO_LIST("en_state_machine_mode"));
        }
    }
}
void MainWindow ::API_menu_trigger(const QString &text)
{
    int set_get_state = set_get_menu->currentIndex();
    std::string box_str = text.toUtf8().constData();
    int API_state       = 0;
    int rx_tx_val       = tx_rx_menu->currentIndex();


    for(int i=0; i < 30;i++)
    {
        if(ID_LUT[i] == box_str)
        {
            API_state = i;
            break;
        }
    }
    param1_label->setText(TRANSLATE(params_strings[Param_mask_1(ID_to_TYPE_OPCODE[API_state])]));
    param2_label->setText(TRANSLATE(params_strings[Param_mask_2(ID_to_TYPE_OPCODE[API_state])]));
    SPECIAL_CASE_FIR_LABELS()
    
    if(set_get_state == Set_param && !box_str.empty())
    {
        this->Slider_Calc(box_str);
    }
}
/**************************************************************
 ************************TEXT RELATED *************************
 *************************************************************/
uint64_t MainWindow::Text_Processing(std::string& msg)
{
    int offset = 0;
    std::size_t found;
    uint64_t num = 0;
    bool notation = false;
    uint64_t multipliyer = 0;
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
    uint64_t value_proc = 0;
    
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
                if(strcmp(API_menu->currentText().toUtf8().constData(), seter_strings[lo_freq]) == 0)
                {
                    frequency_set = value_proc;
                    (*(ParamN_slider_val[index]))->setText(msg.c_str());
                }else
                {
                    (*(ParamN_slider_val[index]))->setText("Invalid");
                }
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


void MainWindow :: Opcode_to_GUI()
{
    static std::string GUI_Opcode_str;
    std::string temp = Opcode_input_text->toPlainText().toUtf8().constData();
    if(temp.back() != '\n')
    {
        GUI_Opcode_str = temp;
    }
    else
    {
        char * pEnd;
        long int dec_opcode = strtol (GUI_Opcode_str.c_str(),&pEnd,16);
        int mask ;
        mask = (dec_opcode & 3);
        set_get_menu->setCurrentIndex(mask) ;// set get do
        mask = (dec_opcode & (3<<2))>>2;
        tx_rx_menu->setCurrentIndex(mask);// other, rx,tx, trx
        mask =(dec_opcode & (63<<4))>>4;
        API_menu->setCurrentText(ID_LUT[mask]);// ID
        
        //param1_label->setText(TRANSLATE(params_strings[Param_mask_1(ID_to_TYPE_OPCODE[API_state])]));
        //param2_label->setText(TRANSLATE(params_strings[Param_mask_2(ID_to_TYPE_OPCODE[API_state])]));
//
        //(dec_opcode & (7<<10))>>10; // p1
        //(dec_opcode & (7<<13))>>13; // p2

        //printf("%lu\r\n",dec_opcode);
        
        Opcode_input_text->clear();
    }
}

/**************************************************************
 ************************BRIDGE HELPERS *************************
 *************************************************************/

void MainWindow ::Load_Sliders_Val_to_bridge()
{
    std::string slider_text = (*(ParamN_slider_val[0]))->text().toUtf8().constData();
    if(isNumeric(slider_text))
    {
        bridge->data_in.p1 = (uint32_t)strtol (slider_text.c_str(),NULL,10);
    }
    else
    {
        bridge->data_in.p1 = UINT32_MAX;
    }
    //param2
    slider_text = (*(ParamN_slider_val[1]))->text().toUtf8().constData();
    if(isNumeric(slider_text))
    {
        bridge->data_in.p2 = (uint32_t)strtol (slider_text.c_str(),NULL,10);
    }
    else
    {
        bridge->data_in.p2 = UINT32_MAX;
    }
}
/**************************************************************
 ************************Validation *************************
 *************************************************************/

bool isNumeric(std::string& str) {
   for (int i = 0; i < str.length(); i++)
      if (isdigit(str[i]) == false)
         return false; //when one non numeric value is found, return false
      return true;
}  
