#include <string>
#include <iostream>
#include <fstream>

using namespace std;

typedef enum
{
    lo_freq,
    sampling_freq,
    fir,
    rf_bandwidth,
    gain,
    mnemonics_size,
}mnemonics_keys;

typedef enum
{
    none,
    b_8,
    b_32,
    b_64,
}bit_size;

string device   = "ad9361";
string do_calib = "do_calib_run";
string action[] = {"do","set","get"};
string dir[]    = {"tx","rx"};


typedef struct parms_num
{
    char no_parms;
    bit_size tx_rx[2];
}parms_num;

typedef struct set_get
{
    parms_num tx;
    parms_num rx;
}set_get;

typedef struct word_and_parms
{
    string name;
    set_get set;
    set_get get;
}word_and_parms;


word_and_parms cmd[mnemonics_size] = {
    //string,           set_tx         set_rx        get_tx          get_rx              
    {"lo_freq"      ,{{1,b_64,none},{1,b_64,none}}, {{1,b_64,none},{1,b_64,none}}},
    {"sampling_freq",{{1,b_32,none},{1,b_32,none}}, {{1,b_32,none},{1,b_32,none}}},
    {"fir"          ,{{0,none,none},{0,none,none}}, {{0,none,none},{0,none,none}}},
    {"rf_bandwidth" ,{{1,b_32,none},{1,b_32,none}}, {{1,b_32,none},{1,b_32,none}}},
    {"gain"         ,{{0,none,none},{0,none,none}}, {{0,none,none},{0,none,none}}},

};

string mnemonics[mnemonics_size] = {
                                    "lo_freq",
                                    "sampling_freq",
                                    "fir",
                                    "rf_bandwidth",
                                    "gain",
                                    };
                  
string fir_config[2] = {"config","en_dis"};
string gain_ctrlmod_rx[2] = {"rf_gain", "gain_control_mode"};



void print_binary(int var)
{
    for(char k=6; k >=0 ;k--)
    {
        printf("%d",(var & 1<<k)>>k);
    }
    printf("\r\n");
}
void prediction ()
{
        //set
    string word;
    int mask;
    for(int set_get = 0;set_get<2;set_get++)
    {
        for(int tx_rx=0;tx_rx < 2; tx_rx++)
        {
            for(int j=0;j < mnemonics_size;j++)
            {
                word = device+"_"+action[set_get+1]+"_"+dir[tx_rx]+"_";

                if(j == gain)
                {
                    for(int k=0;k<2;k++)
                    {
                        cout<<word<<gain_ctrlmod_rx[k]<<" , ";
                        mask = 0;
                        mask |= (set_get+1);
                        mask |= tx_rx<<2;
                        mask |= (j)<<3;
                        mask |= (k)<<6;
                        print_binary(mask);
                    }
                }
                else if(j == fir)
                {
                    for(int k=0;k<2;k++)
                    {
                        cout<<word<<mnemonics[j]<<"_"<<fir_config[k]<<" , ";
                        mask = 0;
                        mask |= (set_get+1);
                        mask |= tx_rx<<2;
                        mask |= (j)<<3;
                        mask |= (k)<<6;
                        print_binary(mask);
                    }
                }
                else
                {
                    word +=mnemonics[j];
                    cout<<word<<" , ";
                    mask = 0;
                    mask |= (set_get+1);
                    mask |= tx_rx<<2;
                    mask |= (j)<<3;
                    print_binary(mask);
                }

            }
        }
    }
}

int main(int argc, char const *argv[])
{


    return 0;
}
