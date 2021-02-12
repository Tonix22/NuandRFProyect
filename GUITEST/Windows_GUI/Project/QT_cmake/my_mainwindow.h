#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdint.h>
#include <string>
#include "sample.h"
/***************************************************
******************* CODE COMPRESION*******************
****************************************************/

#define TRANSLATE(Param) QApplication::translate("OpcodeGenerator", Param, Q_NULLPTR)

#define PUSH_TO_LIST(Param) <<TRANSLATE(Param)

#define CLR(box) box->clear()

#define Save_TX_RX_STATE() for(int i=0;i<tx_rx_menu->count();i++)\
                        {\
                            normal_state PUSH_TO_LIST(tx_rx_menu->itemText(i).toUtf8().constData());\
                        }\

/**************************************************************
 *********************SPECIAL CASE ***************************
 *************************************************************/

#define SPECIAL_CASE_FIR_BUTTON()   if(API_str == "get_fir_config")\
                                    {\
                                        if(tx_rx_stare == Rx_parm)\
                                        {\
                                            Params = RXFIR<<3 | u8int;\
                                        }\
                                        else if(tx_rx_stare == Tx_param)\
                                        {\
                                            Params = TXFIR<<3 | u8int;\
                                        }\
                                    }\
                                    if(API_str == "set_fir_config")\
                                    {\
                                        if(tx_rx_stare == Rx_parm)\
                                        {\
                                            Params = RXFIR;\
                                        }\
                                        else if(tx_rx_stare == Tx_param)\
                                        {\
                                            Params = TXFIR;\
                                        }\
                                    }
    
#define SPECIAL_CASE_FIR_LABELS()   if(box_str == "get_fir_config")\
                                    {\
                                        if(rx_tx_val == Rx_parm)\
                                        {\
                                            param2_label->setText(TRANSLATE(params_strings[RXFIR]));\
                                        }\
                                        else if(rx_tx_val == Tx_param)\
                                        {\
                                            param2_label->setText(TRANSLATE(params_strings[TXFIR]));\
                                        }\
                                    }\
                                    if(box_str == "set_fir_config")\
                                    {\
                                        if(rx_tx_val == Rx_parm)\
                                        {\
                                            param1_label->setText(TRANSLATE(params_strings[RXFIR]));\
                                        }\
                                        else if(rx_tx_val == Tx_param)\
                                        {\
                                            param1_label->setText(TRANSLATE(params_strings[TXFIR]));\
                                        }\
                                    }
/***************************************************
******************* MENUS SCREENS*******************
****************************************************/

/***************************************************
******************* DO AND NONE**********************
****************************************************/


#define DO_API_LIST PUSH_TO_LIST("mcs") \
                    PUSH_TO_LIST( "calib") \
                    PUSH_TO_LIST( "dcxo_tune_coarse") \
                    PUSH_TO_LIST( "dcxo_tune_fine")

#define NONE_TX_LIST PUSH_TO_LIST("fastlock_store")\
                     PUSH_TO_LIST("fastlock_recall")\
                     PUSH_TO_LIST("fastlock_load")\
                     PUSH_TO_LIST("fastlock_save")

#define NONE_RX_LIST PUSH_TO_LIST("fastlock_store")\
                     PUSH_TO_LIST("fastlock_recall")\
                     PUSH_TO_LIST("fastlock_load")\
                     PUSH_TO_LIST("fastlock_save")


/**************************************************************
 *********************SET SECTION******************************
 *************************************************************/
typedef enum
{
    en_state_machine_mode,
    rf_gain,
    rf_bandwidth,
    sampling_freq,
    lo_freq,
    lo_int_ex,
    gain_control_mode,
    set_fir_config,
    fir_en_dis,
    rfdc_track_en_dis,
    bbdc_track_en_dis,
    quad_track_en_dis,
    rf_port_input,
    no_ch_mode,
    attenuation,
    rf_port_output,
    auto_cal_en_dis,
    path_clk,
    rate_gov,
    set_cmd_size
}seters_enum;

#define MAX_SET_STRING_SIZE 22

#define SET_STRING_COLLECTION() "en_state_machine_mode",\
                                "rf_gain",\
                                "rf_bandwidth",\
                                "sampling_freq",\
                                "lo_freq",\
                                "lo_int_ex",\
                                "gain_control_mode",\
                                "set_fir_config",\
                                "fir_en_dis",\
                                "rfdc_track_en_dis",\
                                "bbdc_track_en_dis",\
                                "quad_track_en_dis",\
                                "rf_port_input",\
                                "no_ch_mode",\
                                "attenuation",\
                                "rf_port_output",\
                                "auto_cal_en_dis",\
                                "path_clks",\
                                "rate_gov"

#define SET_API_NONE_LIST PUSH_TO_LIST (seter_strings[en_state_machine_mode])\
                          PUSH_TO_LIST (seter_strings[no_ch_mode])


#define SET_API_RX_LIST PUSH_TO_LIST (seter_strings[rf_gain])\
                        PUSH_TO_LIST (seter_strings[rf_bandwidth])\
                        PUSH_TO_LIST (seter_strings[sampling_freq])\
                        PUSH_TO_LIST (seter_strings[lo_freq])\
                        PUSH_TO_LIST (seter_strings[lo_int_ex])\
                        PUSH_TO_LIST (seter_strings[gain_control_mode])\
                        PUSH_TO_LIST (seter_strings[set_fir_config])\
                        PUSH_TO_LIST (seter_strings[fir_en_dis])\
                        PUSH_TO_LIST (seter_strings[rfdc_track_en_dis])\
                        PUSH_TO_LIST (seter_strings[bbdc_track_en_dis])\
                        PUSH_TO_LIST (seter_strings[quad_track_en_dis])\
                        PUSH_TO_LIST (seter_strings[rf_port_input])
                       

#define SET_API_TX_LIST PUSH_TO_LIST (seter_strings[attenuation])\
                        PUSH_TO_LIST (seter_strings[rf_bandwidth])\
                        PUSH_TO_LIST (seter_strings[sampling_freq])\
                        PUSH_TO_LIST (seter_strings[lo_freq])\
                        PUSH_TO_LIST (seter_strings[lo_int_ex])\
                        PUSH_TO_LIST (seter_strings[set_fir_config])\
                        PUSH_TO_LIST (seter_strings[fir_en_dis])\
                        PUSH_TO_LIST (seter_strings[rf_port_output])\
                        PUSH_TO_LIST (seter_strings[auto_cal_en_dis])

#define SET_API_TRX_LIST PUSH_TO_LIST (seter_strings[path_clk])\
                         PUSH_TO_LIST (seter_strings[fir_en_dis])\
                         PUSH_TO_LIST (seter_strings[rate_gov])

/**************************************************************
 *********************GET SECTION******************************
 *************************************************************/

#define GET_API_RX_LIST PUSH_TO_LIST("rf_gain")\
                        PUSH_TO_LIST("rf_bandwidth")\
                        PUSH_TO_LIST("sampling_freq")\
                        PUSH_TO_LIST("lo_freq")\
                        PUSH_TO_LIST("rssi")\
                        PUSH_TO_LIST("gain_control_mode")\
                        PUSH_TO_LIST("get_fir_config")\
                        PUSH_TO_LIST("fir_en_dis")\
                        PUSH_TO_LIST("rfdc_track_en_dis")\
                        PUSH_TO_LIST("bbdc_track_en_dis")\
                        PUSH_TO_LIST("quad_track_en_dis")\
                        PUSH_TO_LIST("rf_port_input")

#define GET_API_TX_LIST PUSH_TO_LIST("attenuation")\
                        PUSH_TO_LIST("rf_bandwidth")\
                        PUSH_TO_LIST("sampling_freq")\
                        PUSH_TO_LIST("lo_freq")\
                        PUSH_TO_LIST("get_fir_config")\
                        PUSH_TO_LIST("fir_en_dis")\
                        PUSH_TO_LIST("rssi")\
                        PUSH_TO_LIST("rf_port_output")\
                        PUSH_TO_LIST("auto_cal_en_dis")

#define GET_API_TRX_LIST PUSH_TO_LIST("path_clks")\
                         PUSH_TO_LIST("rate_gov")



/**************************************************************
 ***********************MENU LIMITS***************************
 *************************************************************/

#define DATA_RANGES() {seter_strings[en_state_machine_mode], {std::make_pair(0,7)}},\
                    {seter_strings[rf_gain],               {std::make_pair(0,1),std::make_pair(-4,71)}},\
                    {seter_strings[rf_bandwidth],          {std::make_pair(0,56000000)}},\
                    {seter_strings[sampling_freq],         {std::make_pair(0,61440000)}},\
                    {seter_strings[lo_freq],               {std::make_pair(70000000,2147483647)}},\
                    {seter_strings[lo_int_ex],             {std::make_pair(0,1)}},\
                    {seter_strings[gain_control_mode],     {std::make_pair(0,1),std::make_pair(0,3)}},\
                    {seter_strings[set_fir_config],            {std::make_pair(0,0)}},\
                    {seter_strings[path_clk],              {std::make_pair(0,0)}},\
                    {seter_strings[fir_en_dis],            {std::make_pair(0,1)}},\
                    {seter_strings[rfdc_track_en_dis],     {std::make_pair(0,1)}},\
                    {seter_strings[bbdc_track_en_dis],     {std::make_pair(0,1)}},\
                    {seter_strings[quad_track_en_dis],     {std::make_pair(0,1)}},\
                    {seter_strings[rf_port_input],         {std::make_pair(0,11)}},\
                    {seter_strings[rf_port_output],        {std::make_pair(0,1)}},\
                    {seter_strings[attenuation],           {std::make_pair(0,1),std::make_pair(0,89750)}},\
                    {seter_strings[no_ch_mode],             {std::make_pair(1,2)}},\
                    {seter_strings[rate_gov],              {std::make_pair(0,1)}},\
                    {seter_strings[auto_cal_en_dis],       {std::make_pair(0,1)}},\


/**************************************************************
 ***********************LUT VALUES*****************************
 *************************************************************/
#define LUT_NUM_ITEMS 30
#define LUT_MAX_STRING 22

#define LUT_VALUE_DEF() {"en_state_machine_mode"}, \
                        {"rf_gain"}, \
                        {"rf_bandwidth"}, \
                        {"sampling_freq"}, \
                        {"lo_freq"}, \
                        {"lo_int_ext"}, \
                        {"rssi"}, \
                        {"gain_control_mode"}, \
                        {"set_fir_config"}, \
                        {"get_fir_config"}, \
                        {"fir_en_dis"}, \
                        {"rfdc_track_en_dis"}, \
                        {"bbdc_track_en_dis"}, \
                        {"quad_track_en_dis"}, \
                        {"rf_port_input"}, \
                        {"fastlock_store"}, \
                        {"fastlock_recall"}, \
                        {"fastlock_load"}, \
                        {"fastlock_save"}, \
                        {"attenuation"}, \
                        {"rf_port_output"}, \
                        {"auto_cal_en_dis"}, \
                        {"path_clks"}, \
                        {"no_ch_mode"}, \
                        {"mcs"}, \
                        {"rate_gov"}, \
                        {"calib"}, \
                        {"load_enable_fir"}, \
                        {"dcxo_tune_coarse"}, \
                        {"dcxo_tune_fine"}, 


/**************************************************************
 ***********************Special Ones**************************
 *************************************************************/
 #define Special_ones_IDS()   0xA466,\
                              0x1885,\
                              0xC496,\
                              0x2914,\
                              0x1C89,\
                              0xE49A,\
                              0x2918,\
                              0x496D,\
                              0xF9BC



/**************************************************************
 ***********************TYPEDEF*********************************
 *************************************************************/
typedef enum
{
    NONE_param,
    Set_param,
    Get_param,
    Do_param,
}set_get_enum;

typedef enum
{
    NONE_param_tx_rx = 0,
    Rx_parm   ,
    Tx_param,
    Trx_param,
    tx_rx_size ,
}tx_rx_trx_enum;


typedef enum
{
    No_param,
    u8int,
    u32int,
    s32int,
    u64int,
    struct_param,
    RXFIR,
    TXFIR,
    Params_set_size,
}Param_size_t;

#define Param_mask_1(DATA)  DATA&7
#define Param_mask_2(DATA)  (DATA&(7<<3))>>3


#define TYPES_STR_SEQ() "No_param",\
                        "uint8",\
                        "uint32",\
                        "int32",\
                        "int64",\
                        "struct",\
                        "RXFIR",\
                        "TXFIR",\

bool isNumeric(std::string& str);

/**************************************************************
 *********************CLASS DEFINITION************************
 *************************************************************/


class MainWindow : public QMainWindow, private Ui::OpcodeGenerator
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    void Slider_Calc(std::string& str);
    uint64_t Text_Processing(std::string& msg);
    void Load_Sliders_Val_to_bridge();
    void Text_input_register(std::string& msg,int index);
    void Special_ones(int id);
    std::string Scientific_Units(uint64_t val);
    void Scientific_display();
    void Write_64();

    QPlainTextEdit** ParamN_input_text[2] = {&Param1_input_text, &Param2_input_text};
    QSlider** Param_N_val[2]      = {&Param_1_val,&Param_2_val};
    QLabel**  ParamN_slider_val[2]= {&Param1_slider_val,&Param2_slider_val};
    std::string Sci_units[3] = {"K","M","G"};


private slots:
    void onButtonClicked();
    void set_get_menu_changed(const QString &text);
    void tx_rx_menu_changed(const QString &text);
    void API_menu_trigger(const QString &text);
    void Text_param1_changed();
    void Text_param2_changed();
    void Opcode_to_GUI();
    void Frequency_display();
};




#endif // MAINWINDOW_H
