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

std::map<string,int> first_level ={{"init",0},{"set",1},{"get",2},{"do",3}};

std::map<string,int> second_level={{"other",0},{"rx",1},{"tx",2},{"trx",3}};

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
        printf("\"\r\n");
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

        //cout<<str.substr(0,str.find("("))<<", ";

        found  = str.find("_");
        //first level  set_get
        action = str.substr(0,found);
        str = str.substr(found+1);
        mask|=first_level[action];
        
        
        
        //second level tx,rx,txrx
        if(mask)
        {
            found  = str.find("_",found);
            action = str.substr(0,found);

            found  = action.find("_",0);
            action = action.substr(0,found);
        }
        else
        {
            action = "";
            //parse parameters
        }

        if(second_level[action])
        {
            mask|=((second_level[action])-1)<<2;
            str  = str.substr(found+1);
        }

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
        }
        else
        {
           count = std::distance(API_names.begin(),find_it);
        }
        //cout<<API_names[count]<<", ";
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

            if(data_type[types])
            {
                //cout<<types;
                //if(!print_once++)
                    //cout<<", ";
                parms.push_back(data_type[types]);
            }
        }
        //cout<<endl;
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
        */
       printf("0x%X\r\n",mask);
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
