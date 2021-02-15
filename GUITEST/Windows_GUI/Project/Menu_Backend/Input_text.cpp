
#include "my_mainwindow.h"


extern std::unordered_map<std::string, std::vector<std::pair<int, int>>> bounds;
extern char ID_LUT[LUT_NUM_ITEMS][LUT_MAX_STRING];
extern char seter_strings[set_cmd_size][MAX_SET_STRING_SIZE];

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
        value_proc = Sci_to_int(msg);    

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
        
        Opcode_input_text->clear();
    }
}

