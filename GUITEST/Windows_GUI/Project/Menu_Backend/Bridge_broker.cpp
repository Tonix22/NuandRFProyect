
#include "my_mainwindow.h"
#include<windows.h>
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
    
    //TODO FIX BUG HERE String type 23.5M must be converted to numeric one
    uint64_t var = 0;
    
    if(isNumeric(slider_text))
    {
        bridge->data_in.p1 = (uint32_t)strtol (slider_text.c_str(),NULL,10);
    }
    else
    {
        var = Sci_to_int(slider_text);
        bridge->data_in.p1 = (uint32_t)var;
    }
    //param2
    slider_text = (*(ParamN_slider_val[1]))->text().toUtf8().constData();
    if(isNumeric(slider_text))
    {
        bridge->data_in.p2 = (uint32_t)strtol (slider_text.c_str(),NULL,10);
    }
    else
    {
        var = Sci_to_int(slider_text);
        bridge->data_in.p2 = (uint32_t)var;
    }
}

void MainWindow :: Write_64()
{
    std::string msg    = (*(ParamN_input_text[0]))->toPlainText().toUtf8().constData();
    uint64_t value_proc = 0;
    value_proc = Sci_to_int(msg);
    std::string label_val = (*(ParamN_slider_val[0]))->text().toUtf8().constData();
    uint64_t frequency    = Sci_to_int(label_val);
    if(value_proc >frequency)
    {
        frequency = value_proc;
    }

    std::cout<<"lable str "<< label_val<<std::endl;
    std::cout<<"label int " << frequency<<std::endl;
    bridge->data_in.p1    = (uint32_t) frequency;
    bridge->data_in.p2    = (uint32_t) (frequency>>32);
}

void MainWindow :: Read_special(QTextStream& out)
{
    //QString text =;
    uint32_t* p = new uint32_t[bridge->block_size];
    std::string output_data;
    bool first_time =true;
    uint32_t* tx = &(bridge->data_in.op);
    uint32_t max_count = 0;
    uint32_t timeout   = 0;
    bridge->aip->writeMem("MDATAIN", (tx), 1, 0, addr);

    while(1)
    {
        max_count++;
        //wait to data being different from 0
        do
        {
            Sleep(1);
            memset(p,0,sizeof(uint32_t)*bridge->block_size);
            bridge->aip->readMem("MDATAOUT", p, bridge->block_size, 0, addr);
            timeout++;
        } while(!(p[0]|p[1]|p[2]) && timeout < 30);

        // loop ends when EOF is reached of prevent counting reaches 1000
        if(max_count >1000){break;}
        if(p[0]=='E' && p[1]=='O' && p[2] == 'F')
        {
            break;
        }

        //read data and send it to file
        output_data.clear();
        for(int i=0; i < bridge->block_size;i++){
            output_data+= std::to_string(p[i]);
            output_data+=", ";
        }
        output_data+="\n";
        out<<output_data.c_str();
        bridge->aip->start(addr);
    }

    
}   

void MainWindow :: Write_Special(std::vector<uint32_t>& data)
{
    
    uint32_t* p ;
    std::vector<uint32_t>::iterator it;
    int curr_pos = 0;
    int estimate = 0;
    int data_size = data.size();

    bool Sync = true;
    uint32_t data_ack[4];

    it = data.begin();
    while(curr_pos <= data_size)
    {
        p = &(*it);
        curr_pos = it - data.begin();
        estimate = (data.end()-1)-it;

        if(estimate < bridge->block_size)
        {
            bridge->aip->writeMem("MDATAIN", (uint32_t*)p, estimate+1, 0, addr);
            bridge->aip->start(addr);

            for (int i=curr_pos;i<=(curr_pos+estimate);i++)
                std::cout << data[i] << " ,";
            std::cout<<std::endl;

            break;
        }
        else
        {

            bridge->aip->writeMem("MDATAIN", (uint32_t*)p, bridge->block_size - 1, 0, addr);
            bridge->aip->start(addr);

            for (int i=curr_pos;i<=curr_pos+(bridge->block_size - 1);i++)
                std::cout << data[i] << " ,";
            std::cout<<std::endl;

            it+=(bridge->block_size - 1);

            Sync = true;

            while(Sync)
            {
                Sleep(1);
                bridge->aip->readMem("MDATAOUT", data_ack, 4, 0, addr);

                if(data_ack[0]=='A' && data_ack[1]=='C' && data_ack[2]=='K')
                {
                    Sync = false;
                    memset(data_ack,0,sizeof(uint32_t)*4);
                    bridge->aip->writeMem("MDATAOUT", data_ack, 4, 0, addr);
                }else
                {
                   memset(data_ack,0,sizeof(uint32_t)*4);
                }

            }
        }   
    }

}
