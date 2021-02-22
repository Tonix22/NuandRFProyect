
#include "my_mainwindow.h"

extern QString addr;

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

void MainWindow :: Write_Special(std::vector<int>& data)
{
    int* p ;
    std::vector<int>::iterator it;
    int curr_pos = 0;
    int estimate = 0;
    int data_size = data.size();

    data.insert(data.begin(),bridge->data_in.op);
    it = data.begin();
    while(curr_pos <= data_size)
    {
        p = (int*)&(*it);
        curr_pos = it - data.begin();
        estimate = (data.end()-1)-it;

        if(estimate < bridge->block_size)
        {
            bridge->aip->writeMem("MDATAIN", (uint32_t*)p, estimate, 0, addr);
            for (int i=curr_pos;i<=(curr_pos+estimate);i++)
                std::cout << data[i] << " ,";
            std::cout<<std::endl;
            break;
        }
        else
        {
            bridge->aip->writeMem("MDATAIN", (uint32_t*)p, bridge->block_size - 1, 0, addr);
            for (int i=curr_pos;i<=curr_pos+(bridge->block_size - 1);i++)
                std::cout << data[i] << " ,";
            std::cout<<std::endl;
            it+=(bridge->block_size - 1);
        }   
    }
}
