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
 *********************API this->OPCODE MAP***************************
 *************************************************************/

char ID_LUT[LUT_NUM_ITEMS][LUT_MAX_STRING] =
{
    LUT_VALUE_DEF()
};


/**************************************************************
 *********************Types this->OPCODE MAP*************************
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
 ************************SEND DATA******************************
 *************************************************************/

void MainWindow :: onButtonClicked()
{
    int set_get_state   = set_get_menu->currentIndex();
    int tx_rx_stare     = tx_rx_menu->currentIndex();
    std::string API_str = API_menu->currentText().toUtf8().constData();
    this->API_state       = 0;
    this->Params          = 0;
    this->OPCODE          = 0;
    char str_opcode[7]  = {0,0,0,0,0,0,0};
    for(int i=0;i<30;i++)
    {
        if(ID_LUT[i] == API_str)
        {
            this->API_state = i;
            break;
        }
    }
    this->Params = ID_to_TYPE_OPCODE[this->API_state];
    SPECIAL_CASE_FIR_BUTTON()
    this->OPCODE = set_get_state | (tx_rx_stare<<2) | (this->API_state<<4) | (Params<<10);
    sprintf(str_opcode,"0x%X",this->OPCODE);
    Opcode_input_text->setPlainText(str_opcode);
    

    std::cout<<"set_get_state: " << set_get_state << std::endl;
    std::cout<<"tx_rx_stare: " << tx_rx_stare << std::endl;
    std::cout<<"this->API_state: " << this->API_state << std::endl;
    std::cout<<"this->OPCODE: " << std::hex << this->OPCODE << std::endl;


    bridge->data_in.op =  this->OPCODE;

    if(Large_items_APIS_set.find(this->OPCODE) != Large_items_APIS_set.end())
    {
        Special_ones(set_get_state);
        return;// special ones, all is done here
    }
    else if(strcmp(API_menu->currentText().toUtf8().constData(), seter_strings[lo_freq]) == 0)
    {
        Write_64();
    }
    else if(set_get_state == Set_param || set_get_state == Do_param)
    {
        Load_Sliders_Val_to_bridge();
    }

    bridge->WriteData();
    
    if(set_get_state == Get_param)
    {
        uint32_t* p;
        bridge->ReadData();
        p = &(bridge->data_out.p1);
        this->Slider_Calc(API_str);
        
        for(int i=0;i < 1;i++,p++)
        {
            std::cout<<"read data: "<< *p << std::endl;
            (*(Param_N_val[i]))->setValue(*p);
            (*(Param_N_val[i]))->setSliderPosition(*p);
            //(*(Param_N_val[i]))->setEnabled(false);
        }
        if(strcmp(API_str.c_str(), seter_strings[rf_bandwidth])  == 0
        || strcmp(API_str.c_str(), seter_strings[sampling_freq]) == 0
        )
        {
            (*(ParamN_slider_val[0]))->setText(int_to_Sci(Param_1_val->value()).c_str());
            Show_get_result->setText(int_to_Sci(Param_1_val->value()).c_str());
        }
        else if(strcmp(API_str.c_str(), seter_strings[lo_freq]) == 0)
        {
            std::cout<<"get freq"<<std::endl;
            uint64_t p1_plus_p2 = (uint64_t)(bridge->data_out.p1)+(uint64_t)(bridge->data_out.p2);
            std::cout<<"data = "<<  p1_plus_p2 << std::endl;
            (*(ParamN_slider_val[0]))->setText(int_to_Sci(p1_plus_p2).c_str());
            Show_get_result->setText(int_to_Sci(p1_plus_p2).c_str());
        }
        else
        {
            (*(ParamN_slider_val[0]))->setText(std::to_string(Param_1_val->value()).c_str());
            Show_get_result->setText(std::to_string(Param_1_val->value()).c_str());
        }

        (*(ParamN_slider_val[1]))->setText(std::to_string(Param_2_val->value()).c_str());
        (*(ParamN_slider_val[0]))->setStyleSheet("QLabel { color : #00FFFF; font: bold 14px; }");
        (*(ParamN_slider_val[1]))->setStyleSheet("QLabel { color : #00FFFF; font: bold 14px; }");
        
    }
}

/**************************************************************
 ************************UPDATE MENU *************************
 *************************************************************/


void MainWindow :: set_get_menu_changed(const QString &text)
{
    std::string box_str = text.toUtf8().constData();
    static QStringList normal_state;
    static bool need_refresh = false;

    if( (*(Param_N_val[0]))->isEnabled() == false && box_str!="get")
    {
        (*(Param_N_val[0]))->setEnabled(true);
        (*(Param_N_val[1]))->setEnabled(true);
        (*(ParamN_slider_val[0]))->setStyleSheet("QLabel { color : #FFFFFF; font: 12px; }");
        (*(ParamN_slider_val[1]))->setStyleSheet("QLabel { color : #FFFFFF; font: 12px; }");
    }

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
   
    (*(ParamN_slider_val[0]))->setText(int_to_Sci(extend).c_str());
}
void MainWindow :: Scientific_display()
{
    (*(ParamN_slider_val[0]))->setText(int_to_Sci(Param_1_val->value()).c_str());
}

void MainWindow :: Slider_Calc(std::string& str)
{
    static bool sci_displayer = false;
    int set_get_state = set_get_menu->currentIndex();

    auto slider_update = [&](int i)
    {
        (*(ParamN_slider_val[i]))->setText((std::to_string(bounds[str][i].first).c_str()));
        (*(Param_N_val[i]))->setValue(bounds[str][i].first);
        (*(Param_N_val[i]))->setSliderPosition(bounds[str][i].first);
    };

    // lo frequency, is 64 bit long so it will be difirent
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
        QObject::connect(Param_1_val, &QSlider::valueChanged, this, Frequency_display);
        QObject::connect(Param_2_val, &QSlider::valueChanged, this, Frequency_display);
        sci_displayer = true;
        slider_update(0);
        (*(ParamN_slider_val[1]))->clear();
        return;  
    }

    if(sci_displayer)
    {
        sci_displayer = false;
        QObject::connect(Param_1_val, SIGNAL(valueChanged(int)), (*(ParamN_slider_val[0])), SLOT(setNum(int)));
        QObject::connect(Param_2_val, SIGNAL(valueChanged(int)), (*(ParamN_slider_val[1])), SLOT(setNum(int)));
    }

    if(strcmp(str.c_str(), seter_strings[rf_bandwidth])  == 0
    || strcmp(str.c_str(), seter_strings[sampling_freq]) == 0
    )
    {
        Param_1_val->disconnect();
        QObject::connect(Param_1_val, &QSlider::valueChanged, this, Scientific_display);
        sci_displayer = true;
    }
    if (set_get_state == NONE_param)
    {
        Param_1_val->setRange(0,7);
        min_p1_val->setText(TRANSLATE ("0"));
        max_p1_val->setText(TRANSLATE ("7"));
        (*(Param_N_val[0]))->setSliderPosition(0);

        Param_2_val->setRange(0,0);
        min_p2_val->setText(TRANSLATE ("None"));
        max_p2_val->setText(TRANSLATE ("None"));
        (*(ParamN_slider_val[1]))->setText("None");
        return;
    }
    if(str == "get_fir_config")
    {
        return;
    }

    // These are the functions that left
    Param_1_val->setRange(bounds[str][0].first,bounds[str][0].second);
    min_p1_val->setText(TRANSLATE (std::to_string(bounds[str][0].first).c_str()));
    max_p1_val->setText(TRANSLATE (std::to_string(bounds[str][0].second).c_str()));
    slider_update(0);
    
    if (set_get_state == Get_param)
    {
        if(bounds[str].size() == 2)
        {
            (*(Param_N_val[0]))->setEnabled(true);
            Param_2_val->setRange(bounds[str][1].first,bounds[str][1].second);
            min_p2_val->setText(TRANSLATE (std::to_string(bounds[str][1].first).c_str()));
            max_p2_val->setText(TRANSLATE (std::to_string(bounds[str][1].second).c_str()));
            (*(Param_N_val[1]))->setEnabled(false);
        }
        else
        {
            (*(Param_N_val[0]))->setEnabled(false);

            Param_2_val->setRange(0,0);
            min_p2_val->setText(TRANSLATE ("None"));
            max_p2_val->setText(TRANSLATE ("None"));
            (*(ParamN_slider_val[1]))->setText("None");
            (*(Param_N_val[1]))->setEnabled(false);
        }
    }
    else
    {
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
            (*(ParamN_slider_val[1]))->setText("None");
        }
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
    std::string box_str = text.toUtf8().constData();
    this->API_state       = 0;
    int rx_tx_val       = tx_rx_menu->currentIndex();


    for(int i=0; i < 30;i++)
    {
        if(ID_LUT[i] == box_str)
        {
            this->API_state = i;
            break;
        }
    }
    if(!box_str.empty())
    {
        this->Slider_Calc(box_str);
    }
    param1_label->setText(TRANSLATE(params_strings[Param_mask_1(ID_to_TYPE_OPCODE[this->API_state])]));
    param2_label->setText(TRANSLATE(params_strings[Param_mask_2(ID_to_TYPE_OPCODE[this->API_state])]));
    SPECIAL_CASE_FIR_LABELS()
    

}

/**************************************************************
 ************************TEXT INPUT RELATED *******************
 *************************************************************/

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



