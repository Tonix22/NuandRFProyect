#include "my_mainwindow.h"

std::string MainWindow :: int_to_Sci(uint64_t temp)
{
    char power = 0;
    int integers = 0;
    std::string merge;
    char scientific = 0;
    uint64_t original_value = temp;
    if(temp < 1000)
        return std::to_string(temp);
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
    
    merge = std::to_string(original_value).substr(0, integers) +"."+ std::to_string(original_value).substr(integers);
    merge.erase ( merge.find_last_not_of('0') + 1, std::string::npos );
    merge = merge.substr(0,std::min(5,(int)merge.size()));
    merge+=Sci_units[scientific-1];

    return merge;
}

uint64_t MainWindow::Sci_to_int(std::string& msg)
{
    int offset = 0;
    std::size_t found;
    uint64_t num = 0;
    bool notation = false;
    uint64_t multipliyer = 0;
    std::string left = "0";
    std::string right= "0";

    auto unit_selector = [&]()
    {
        for(int i=0;i < 3;i++)
        {
            found = msg.find(Sci_units[i]);
            if (found != std::string::npos)
            {
                multipliyer = (uint64_t)pow(10,(i+1)*3);
                break;
            }
        }
    };

    if(msg.find("M")!=std::string::npos
    || msg.find("K")!=std::string::npos
    || msg.find("G")!=std::string::npos)
    {
        notation = true;

        found  = msg.find(".");
        if (found != std::string::npos) // with dot
        {
            left   = msg.substr(0, found);
            offset = found+1; // dot
            unit_selector();
            right  = msg.substr(offset, found-offset);
        }
        else // not dot
        {
            unit_selector();
            left   = msg.substr(0, found);
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