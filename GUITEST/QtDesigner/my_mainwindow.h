#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
                                "path_clk",\
                                "rate_gov"



#define SET_API_RX_LIST PUSH_TO_LIST (seter_strings[en_state_machine_mode])\
                        PUSH_TO_LIST (seter_strings[rf_gain])\
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
                        PUSH_TO_LIST (seter_strings[rf_port_input])\
                        PUSH_TO_LIST (seter_strings[no_ch_mode])

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

#define GET_API_RX_LIST PUSH_TO_LIST("en_state_machine_mode")\
                        PUSH_TO_LIST("rf_gain")\
                        PUSH_TO_LIST("rf_bandwidth")\
                        PUSH_TO_LIST("sampling_freq")\
                        PUSH_TO_LIST("lo_freq")\
                        PUSH_TO_LIST("rssi")\
                        PUSH_TO_LIST("gain_control_mode")\
                        PUSH_TO_LIST("fir_confi")\
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
#define LUT_VALUE_DEF() {"en_state_machine_mode",0},\
                        {"rf_gain",1,}, \
                        {"rf_bandwidth",2,}, \
                        {"sampling_freq",3}, \
                        {"lo_freq",4}, \
                        {"lo_int_ext",5},\
                        {"rssi",6}, \
                        {"gain_control_mode",7}, \
                        {"set_fir_config",8}, \
                        {"get_fir_config",9},\
                        {"fir_en_dis",10}, \
                        {"rfdc_track_en_dis",11}, \
                        {"bbdc_track_en_dis",12}, \
                        {"quad_track_en_dis",13}, \
                        {"rf_port_input",14}, \
                        {"fastlock_store",15},\
                        {"fastlock_recall",16},\
                        {"fastlock_load",17},\
                        {"fastlock_save",18},\
                        {"attenuation",19}, \
                        {"rf_port_output",20}, \
                        {"auto_cal_en_dis",21}, \
                        {"path_clk",22},\
                        {"no_ch_mode",23},\
                        {"mcs",24},\
                        {"fir_en_dis",25}, \
                        {"rate_gov",26}, \
                        {"calib",27},\
                        {"load_enable_fir",28},\
                        {"dcxo_tune_coarse",29},\
                        {"dcxo_tune_fine",30},



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
    Rx_parm    = 0,
    Tx_param,
    Trx_param,
    tx_rx_size = 4,
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
    int Text_Processing(std::string& msg);
    void Text_input_register(std::string& msg,int index);
    QPlainTextEdit** ParamN_input_text[2] = {&Param1_input_text, &Param2_input_text};
    QSlider** Param_N_val[2]      = {&Param_1_val,&Param_2_val};
    QLabel**  ParamN_slider_val[2]= {&Param1_slider_val,&Param2_slider_val};

private slots:
    void onButtonClicked();
    void set_get_menu_changed(const QString &text);
    void tx_rx_menu_changed(const QString &text);
    void API_menu_trigger(const QString &text);
    void Text_param1_changed();
    void Text_param2_changed();
};




#endif // MAINWINDOW_H
