#include "classify.h"
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;

std::vector<string> API_names;
std::set<string> API_types;

std::map<string,int> first_level ={{"none",0},{"set",1},{"get",2},{"do",3}};

std::map<string,int> second_level={{"none",0},{"rx",1},{"tx",2},{"trx",3}};

std::map<string,int> data_type={
                                {"uint8_t",1},
                                {"uint32_t",2},
                                {"int32_t", 3},
                                {"uint64_t",4},
                                {"struct",5},// but size 11
                                {"AD9361_RXFIRConfig",6},
                                {"AD9361_TXFIRConfig",7},
                                };

void print_binary(int var,char begin,char end)
{
    printf("\"");
    for(char k=end; k >=begin ;k--)
    {
        printf("%d",(var & 1<<k)>>k);
    }
    if(end == 15 && begin == 0)
    {
        printf("\"");
    }
    else
    {
        printf("\"");
    }
}

void parser(string& str)
{
    std::size_t found = str.find("/* ");
    string action;
    string bare_API;
    string types;
    int  mask = 0;
    vector<int> parms;
    if(found == std::string::npos)
    {
       
        
        str    = str.substr(15);
        //cout<<"*****"<<endl;
        //cout<<str.substr(0,str.find("("))<<endl;

        found  = str.find("_");
        //first level  set_get
        action = str.substr(0,found);
        
        if(first_level.find(action) != first_level.end())
        {
            mask|=first_level[action];
            str = str.substr(found+1);
        }
        
        //second level tx,rx,txrx
        if(action!="do")
        {
            found  = str.find("_",found);
            action = str.substr(0,found);
            found  = action.find("_",0);
            action = action.substr(0,found);
            //cout<<action<<", ";
        }
        else
        {
            action = "none";
            //parse parameters
        }
        if(second_level.find(action) == second_level.end())
        {
            action = "none";
        }else
        {
            
            //cout<<str<<", "<<str.find("_")<<endl;
            std::size_t prefix_idx = str.find("_");
            if(prefix_idx <= 4)
            {
                str = str.substr(prefix_idx+1);
                //cout<<action<<endl;
            }
            //cout<<"*********"<<endl;
        }
        //cout<<str<<endl;
        //cout<<endl;
        mask|=((second_level[action]))<<2;
        
        
        
        //parse parameters
        found    = str.find("(",0);
        bare_API = str.substr(0,found);
        str      = str.substr(found+1);
        
     
       
        int count = 0;
        std::vector<string>::iterator find_it = std::find(API_names.begin(),API_names.end(), bare_API);

        if ( find_it == API_names.end())
        {
            API_names.push_back(bare_API);
            count = API_names.size()-1;
            cout<<API_names[count]<<", "<< count <<endl;
           
        }
        else
        {
           count = std::distance(API_names.begin(),find_it);
        }
        //cout<<API_names[count]<<", "<<endl;
        //cout<<"count: " <<count<<endl;
        mask|=(count)<<4;
        char print_once = false;
        while(found != string::npos)
        {
            found    = str.find(",",0);
            str      = str.substr(found+2);

            found    = str.find(' ',0);
            types    = str.substr(0,found);
            str      = str.substr(found+1);

            if(data_type.find(types) != data_type.end())
            {
                //cout<<types<<", ";
                //if(!print_once++)
                    //cout<<", ";
                parms.push_back(data_type[types]);
            }
        }
        //cout<<endl;
        //out<<"p_# "<< parms.size()<<endl;
        for(int i=0; i < parms.size();i++)
        {
            mask|=parms[i] <<(10+(3*i));
        }
        
        /*
        print_binary(mask,13,15);
        cout<<", ";
        print_binary(mask,10,12);        
        cout<<", ";
        print_binary(mask,4,9);
        cout<<", ";
        print_binary(mask,2,3);
        cout<<", ";
        print_binary(mask,0,1);
        cout<<", ";
        print_binary(mask,0,15);
        cout<<", ";

        printf("0x%X\r\n",mask);
        */
        
    }
}



int main(int argc, char const *argv[])
{
    string line;
    ifstream myfile ("functions.txt");
    bool first = true;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            if(first == true)
            {
                first = false;
            }else
            {
                parser(line);
            }
        }
        myfile.close();
    }

    else cout << "Unable to open file";

    return 0;
}
