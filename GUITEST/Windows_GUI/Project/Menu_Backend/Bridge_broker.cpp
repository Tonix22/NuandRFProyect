
#include "my_mainwindow.h"

bool isNumeric(std::string& str) {
   for (int i = 0; i < str.length(); i++)
      if (isdigit(str[i]) == false)
         return false; //when one non numeric value is found, return false
      return true;
}  

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

void MainWindow :: Write_64()
{
    std::string label_val = (*(ParamN_slider_val[0]))->text().toUtf8().constData();
    uint64_t frequency    = Sci_to_int(label_val);
    std::cout<<"lable str "<< label_val<<std::endl;
    std::cout<<"label int " << frequency<<std::endl;
    bridge->data_in.p1    = (uint32_t) frequency;
    bridge->data_in.p2    = (uint32_t) (frequency>>32);
}
