#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sample.h"

#define PUSH_TO_LIST(Param) <<QApplication::translate("OpcodeGenerator", Param, Q_NULLPTR)

#define CLR(box) box->clear()

#define Save_TX_RX_STATE() for(int i=0;i<tx_rx_menu->count();i++)\
                        {\
                            normal_state PUSH_TO_LIST(tx_rx_menu->itemText(i).toUtf8().constData());\
                        }\

/***************************************************
******************* MENUS SCREENS*******************
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
    fir_config,
    fir_en_dis,
    rfdc_track_en_dis,
    bbdc_track_en_dis,
    quad_track_en_dis,
    rf_port_input,
    set_no_ch_mod,
    attenuation,
    rf_port_output,
    auto_cal_en_dis,
    path_clk,
    rate_gov,
    set_cmd_size
}seters_enum;


#define SET_STRING_COLLECTION() "en_state_machine_mode",\
                                "rf_gain",\
                                "rf_bandwidth",\
                                "sampling_freq",\
                                "lo_freq",\
                                "lo_int_ex",\
                                "gain_control_mode",\
                                "fir_config",\
                                "fir_en_dis",\
                                "rfdc_track_en_dis",\
                                "bbdc_track_en_dis",\
                                "quad_track_en_dis",\
                                "rf_port_input",\
                                "set_no_ch_mod",\
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
                        PUSH_TO_LIST (seter_strings[fir_config])\
                        PUSH_TO_LIST (seter_strings[fir_en_dis])\
                        PUSH_TO_LIST (seter_strings[rfdc_track_en_dis])\
                        PUSH_TO_LIST (seter_strings[bbdc_track_en_dis])\
                        PUSH_TO_LIST (seter_strings[quad_track_en_dis])\
                        PUSH_TO_LIST (seter_strings[rf_port_input])\
                        PUSH_TO_LIST (seter_strings[set_no_ch_mod])

#define SET_API_TX_LIST PUSH_TO_LIST (seter_strings[attenuation])\
                        PUSH_TO_LIST (seter_strings[rf_bandwidth])\
                        PUSH_TO_LIST (seter_strings[sampling_freq])\
                        PUSH_TO_LIST (seter_strings[lo_freq])\
                        PUSH_TO_LIST (seter_strings[lo_int_ex])\
                        PUSH_TO_LIST (seter_strings[fir_config])\
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
                        PUSH_TO_LIST("fir_config")\
                        PUSH_TO_LIST("fir_en_dis")\
                        PUSH_TO_LIST("rssi")\
                        PUSH_TO_LIST("rf_port_output")\
                        PUSH_TO_LIST("auto_cal_en_dis")

#define GET_API_TRX_LIST PUSH_TO_LIST("path_clks")\
                         PUSH_TO_LIST("rate_gov")





typedef enum
{
    NONE_param,
    Do_param,
    Set_param,
    Get_param,
}set_get_enum;



class MainWindow : public QMainWindow, private Ui::OpcodeGenerator
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    void Slider_Calc(std::string& str);

private slots:
    void onButtonClicked();
    void set_get_menu_changed(const QString &text);
    void tx_rx_menu_changed(const QString &text);
    void API_menu_trigger(const QString &text);

};

#endif // MAINWINDOW_H
