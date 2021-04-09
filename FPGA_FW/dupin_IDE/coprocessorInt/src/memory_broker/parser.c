#include "stdio.h"
#include "parser.h"
#include <stdint.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "broker.h"

/*
========================================================
   EXTERN
========================================================
*/
extern InternatlStates Current_state;
/*
========================================================
    GLOBALS
========================================================
*/

paramaters_pair foo_params;
uint32_t        FLIP_VALUES[2];
/*
========================================================
    SPECIAL GLOBALS
========================================================
*/

AD9361_RXFIRConfig   RX_FIR;
AD9361_TXFIRConfig   TX_FIR;
uint8_t              fastLock [16];
uint32_t             rx_path_clk[6];
uint32_t             tx_path_clk[6];
struct rf_rssi       rssi;

/*
========================================================
    SPECIALS
========================================================
*/

Special_ids_t Special_Opcodes[SPECIAL_SIZE] = 
{
    GET_RX_RSSI_ID,
    
    SET_RX_FIR_CONFIG_ID,
    GET_RX_FIR_CONFIG_ID,
    SET_TX_FIR_CONFIG_ID,
    GET_TX_FIR_CONFIG_ID,
    TRX_LOAD_ENABLE_FIR_ID,

    RX_FASTLOCK_LOAD_ID,
    TX_FASTLOCK_LOAD_ID,
    RX_FASTLOCK_SAVE_ID,
    TX_FASTLOCK_SAVE_ID,

    SET_TRX_PATH_CLKS_ID
};



/*
========================================================
    OPCODE TO CALLBACK----ONE PARAMETER
========================================================
*/

typedef int32_t u08_t_callback (struct ad9361_rf_phy* , uint8_t);
typedef int32_t u08_t_callback_get (struct ad9361_rf_phy* , uint8_t*);
Caller One_Param_u08[16] = 
{   
    {0x455, &ad9361_set_rx_lo_int_ext        },
    {0x4A5, &ad9361_set_rx_fir_en_dis        },
    {0x4B5, &ad9361_set_rx_rfdc_track_en_dis },
    {0x4C5, &ad9361_set_rx_bbdc_track_en_dis },
    {0x4A9, &ad9361_set_tx_fir_en_dis        },
    {0x459, &ad9361_set_tx_lo_int_ext        },
    {0x559, &ad9361_set_tx_auto_cal_en_dis   },
    {0x571, &ad9361_set_no_ch_mode           },
    {0x4AD, &ad9361_set_trx_fir_en_dis       },
    {0x4D5, &ad9361_set_rx_quad_track_en_dis },
    {0x4A6, &ad9361_get_rx_fir_en_dis        },
    {0x4B6, &ad9361_get_rx_rfdc_track_en_dis },
    {0x4C6, &ad9361_get_rx_bbdc_track_en_dis },
    {0x4D6, &ad9361_get_rx_quad_track_en_dis },
    {0x4AA, &ad9361_get_tx_fir_en_dis        },
    {0x55A, &ad9361_get_tx_auto_cal_en_dis   },
};

typedef int32_t u32_t_callback (struct ad9361_rf_phy* , uint32_t);
typedef int32_t u32_t_callback_get (struct ad9361_rf_phy* , uint32_t*);

Caller One_Param_u32 [22] = {

    {0x801, &ad9361_set_en_state_machine_mode },
    {0x802, &ad9361_get_en_state_machine_mode },
    {0x825, &ad9361_set_rx_rf_bandwidth       },
    {0x826, &ad9361_get_rx_rf_bandwidth       },
    {0x835, &ad9361_set_rx_sampling_freq      },
    {0x836, &ad9361_get_rx_sampling_freq      },
    {0x8E5, &ad9361_set_rx_rf_port_input      },
    {0x8E6, &ad9361_get_rx_rf_port_input      },
    {0x8F4, &ad9361_rx_fastlock_store         },
    {0x904, &ad9361_rx_fastlock_recall        },
    {0x829, &ad9361_set_tx_rf_bandwidth       },
    {0x82A, &ad9361_get_tx_rf_bandwidth       },
    {0x839, &ad9361_set_tx_sampling_freq      },
    {0x83A, &ad9361_get_tx_sampling_freq      },
    {0x949, &ad9361_set_tx_rf_port_output     },
    {0x94A, &ad9361_get_tx_rf_port_output     },
    {0x8F8, &ad9361_tx_fastlock_store         },
    {0x908, &ad9361_tx_fastlock_recall        },
    {0x98D, &ad9361_set_trx_rate_gov          },
    {0x98E, &ad9361_get_trx_rate_gov          },
    {0x9B3, &ad9361_do_dcxo_tune_coarse       },
    {0x9C3, &ad9361_do_dcxo_tune_fine         },
};

typedef int32_t u64_t_callback (struct ad9361_rf_phy *, uint64_t);
typedef int32_t u64_t_callback_get (struct ad9361_rf_phy *, uint64_t*);

Caller One_Param_u64 [4] = 
{
    {0x1045, &ad9361_set_rx_lo_freq},
    {0x1046, &ad9361_get_rx_lo_freq},
    {0x1049, &ad9361_set_tx_lo_freq},
    {0x104A, &ad9361_get_tx_lo_freq},
};

/*
========================================================
    OPCODE TO CALLBACK----TWO PARAMETERS
========================================================
*/

typedef int32_t u08_u08_callback (struct ad9361_rf_phy *, uint8_t, uint8_t);
typedef int32_t u08_u08_callback_get (struct ad9361_rf_phy *, uint8_t, uint8_t*);
Caller Two_Param_u08_u08 [2] = 
{
    {0x2475,&ad9361_set_rx_gain_control_mode},
    {0x2476,&ad9361_get_rx_gain_control_mode},
};

typedef int32_t u32_u08_callback (struct ad9361_rf_phy *, uint32_t, uint8_t*);

Caller Two_Param_u32_u08 [4]=
{
    {0x2914, &ad9361_rx_fastlock_load},
    {0x2924, &ad9361_rx_fastlock_save},
    {0x2918, &ad9361_tx_fastlock_load},
    {0x2928, &ad9361_tx_fastlock_save},
};

typedef int32_t u08_u32_callback (struct ad9361_rf_phy *, uint8_t, uint32_t);
typedef int32_t u08_u32_callback_get (struct ad9361_rf_phy *, uint8_t, uint32_t*);
Caller Two_Param_u08_u32 [3]=
{
    {0x4539,&ad9361_set_tx_attenuation },
    {0x453A,&ad9361_get_tx_attenuation },
    {0x446A,&ad9361_get_tx_rssi },
};

typedef int32_t u32_u32_callback (struct ad9361_rf_phy *, uint32_t*, uint32_t*);


Caller Two_Param_u32_u32 [2]=
{
    {0x496D,&ad9361_set_trx_path_clks},
    {0x496E,&ad9361_get_trx_path_clks},
};

typedef int32_t u08_i32_callback (struct ad9361_rf_phy *, uint8_t, int32_t);
typedef int32_t u08_i32_callback_get (struct ad9361_rf_phy *, uint8_t, int32_t*);

Caller Two_Param_u08_i32 [2]=
{
    { 0x6415, &ad9361_set_rx_rf_gain},
    { 0x6416, &ad9361_get_rx_rf_gain},
};


/*
========================================================
    FUNCTIONS
========================================================
*/


void* callback_id(Caller* var,char size,uint32_t opcode)
{
    for (char i = 0; i < size; i++,var++)
    {
        if(var->ID == opcode)
        {
            return var->foo;
        }
    }
    return NULL;
}

void push_param(uint32_t var,unsigned char flip_n)
{
    if(flip_n < 2)
    {
        FLIP_VALUES[flip_n]=var;
    }
}

/*
========================================================
    SPECIALS
========================================================
*/

void assign_memory_ch_u32_u08(uint8_t* Destination, uint32_t* Source, int begin, int end )
{
    for(int i=begin; i <= end;i++)
    {
        Destination[i] = Source[i];
    }
}
void assign_memory_ch_u08_u32(uint32_t* Destination, uint8_t* Source, int begin, int end )
{
    for(int i=begin; i <= end;i++)
    {
        Destination[i] = Source[i];
    }
}


void assign_memory_to_FIR_RX(uint32_t* Source, AD9361_RXFIRConfig* Destinaion)
{
    static FIR_STAGE State = GAIN_DEC;
    static unsigned char index = 0;
    unsigned char N   = 0;
    static unsigned char Last_index = 0;
    uint32_t* begin    = Source;
    uint32_t  Free     = MAX_READ_SIZE-1;

    if(GAIN_DEC == State)
    {   
        Source++;// avoid opcode
        Destinaion->rx      = *Source;
        Source++;
        Destinaion->rx_gain = *Source;
        Source++;
        Destinaion->rx_dec  = *Source;
        State = COEFCIENTS;
        index = 0;
        N = 3; // there are almost 3 elements read
    }
    
    if(COEFCIENTS == State)
    {
        // index is saved by a static variable, it will increment until
        // reach 128 bytes, or if there is a MAX_INT in memory, wich mean 
        // END OF FILE
        if(index <= 128)
        {
            for(; N < MAX_READ_SIZE; N++,Source++,index++)
            {
                if(UINT32_MAX != *Source)
                {
                    Destinaion->rx_coef[index] = (int16_t)(*Source);
                }
                else{ goto endstate; }
            }
        }
        else
        {
            endstate:
            State = LAST;
            Source++;
        }
    }
    if (LAST == State)
    {
        Free -= (Source-begin);
        for(int j=0;j<Free;j++,Last_index++, Source++)
        {
            if(Last_index == 0)
            {
                Destinaion->rx_coef_size = (uint8_t)(*Source);
            }
            else if(Last_index >=1 && Last_index <=6)
            {
                Destinaion->rx_path_clks[Last_index-1] = *Source; 
            }
            else if(Last_index == 7)
            {
                Destinaion->rx_bandwidth = *Source;
                Current_state = END_PUSH;
                Last_index = 0;
                State = GAIN_DEC;
                break;
            }
        }
    }
}
void assign_memory_to_FIR_TX(uint32_t* Source, AD9361_TXFIRConfig* Destinaion)
{
    static FIR_STAGE State = GAIN_DEC;
    static unsigned char index = 0;
    static unsigned char Last_index = 0;
    unsigned char N   = 0;
    uint32_t* begin    = Source;
    uint32_t  Free     = MAX_READ_SIZE-1;

    if(GAIN_DEC == State)
    {   
        Source++; // avoid opcode
        Destinaion->tx      = *Source;
        Source++;
        Destinaion->tx_gain = *Source;
        Source++;
        Destinaion->tx_int  = *Source;
        State = COEFCIENTS;
        index = 0;
        N = 3; // there are almost 3 elements read
    }
    
    if(COEFCIENTS == State)
    {
        // index is saved by a static variable, it will increment until
        // reach 128 bytes, or if there is a MAX_INT in memory, wich mean 
        // END OF FILE
        if(index <= 128)
        {
            for(; N < MAX_READ_SIZE; N++,Source++,index++)
            {
                if(UINT32_MAX != *Source)
                {
                    Destinaion->tx_coef[index] = (int16_t)(*Source);
                }
                else{ goto endstate; }
            }
        }
        else
        {
            endstate:
            State = LAST;
            Source++;
        }
    }
    if (LAST == State)
    {
        Free -= (Source-begin);
        for(int j=0;j<Free;j++,Last_index++, Source++)
        {
            if(Last_index == 0)
            {
                Destinaion->tx_coef_size = (uint8_t)(*Source);
            }
            else if(Last_index >=1 && Last_index <=6)
            {
                Destinaion->tx_path_clks[Last_index-1] = *Source; 
            }
            else if(Last_index == 7)
            {
                Destinaion->tx_bandwidth = *Source;
                Current_state = END_PUSH;
                Last_index = 0;
                State = GAIN_DEC;
                break;
            }
        }
    }
}

void read_memory_to_FIR_RX(uint32_t* Source)
{
    static FIR_STAGE State = GAIN_DEC;
    static unsigned char index = 0;
    unsigned char N   = 0;
    static unsigned char Last_index = 0;
    uint32_t* begin    = Source;
    uint32_t  Free     = MAX_READ_SIZE-1;

    if(GAIN_DEC == State)
    {
        
        *Source = RX_FIR.rx;
        Source++;
        *Source = RX_FIR.rx_gain;
        Source++;
        *Source = RX_FIR.rx_dec;
        State = COEFCIENTS;
        index = 0;
        N = 3; // there are almost 3 elements read
    }
    if(COEFCIENTS == State)
    {
        // index is saved by a static variable, it will increment until
        // reach 128 bytes, or if there is a MAX_INT in memory, wich mean 
        // END OF FILE

        for(; N < MAX_READ_SIZE; N++,Source++,index++)
        {
            if(RX_FIR.rx_coef_size != (index-1))
            {
               (*Source) =  RX_FIR.rx_coef[index];
            }
            else{ break;}
        }
        if(RX_FIR.rx_coef_size == (index-1))
        {
            State = LAST;
            Source++;
        }
    }
    if (LAST == State)
    {
        Free -= (Source-begin);
        for(int j=0;j<Free;j++,Last_index++, Source++)
        {
            if(Last_index == 0)
            {
                *Source = RX_FIR.rx_coef_size ;
            }
            else if(Last_index >=1 && Last_index <=6)
            {
                *Source = RX_FIR.rx_path_clks[Last_index-1]; 
            }
            else if(Last_index == 7)
            {
                *Source = RX_FIR.rx_bandwidth;
                Current_state = END_PULL;
                Last_index = 0;
                State = GAIN_DEC;
                break;
            }
        }
    }

}
void read_memory_to_FIR_TX(uint32_t* Source)
{
    static FIR_STAGE State = GAIN_DEC;
    static unsigned char index = 0;
    unsigned char N   = 0;
    static unsigned char Last_index = 0;
    uint32_t* begin    = Source;
    uint32_t  Free     = MAX_READ_SIZE-1;

    if(GAIN_DEC == State)
    {
        
        *Source = TX_FIR.tx;
        Source++;
        *Source = TX_FIR.tx_gain;
        Source++;
        *Source = TX_FIR.tx_int;
        State = COEFCIENTS;
        index = 0;
        N = 3; // there are almost 3 elements read
    }
    if(COEFCIENTS == State)
    {
        // index is saved by a static variable, it will increment until
        // reach 128 bytes, or if there is a MAX_INT in memory, wich mean 
        // END OF FILE

        for(; N < MAX_READ_SIZE; N++,Source++,index++)
        {
            if(TX_FIR.tx_coef_size != (index-1))
            {
               (*Source) =  TX_FIR.tx_coef[index];
            }
            else{ break;}
        }
        if(TX_FIR.tx_coef_size == (index-1))
        {
            State = LAST;
            Source++;
        }
    }
    if (LAST == State)
    {
        Free -= (Source-begin);
        for(int j=0;j<Free;j++,Last_index++, Source++)
        {
            if(Last_index == 0)
            {
                *Source = TX_FIR.tx_coef_size;
            }
            else if(Last_index >=1 && Last_index <=6)
            {
                *Source = TX_FIR.tx_path_clks[Last_index-1]; 
            }
            else if(Last_index == 7)
            {
                *Source = TX_FIR.tx_bandwidth;
                Current_state = END_PULL;
                Last_index = 0;
                State = GAIN_DEC;
                break;
            }
        }
    }
}

void push_special (uint32_t* mem)
{
    uint32_t set_get = foo_params.opcode & 3;
    static uint32_t step = 0;
    
    switch (foo_params.opcode )
    {
        /*LOAD*/
    case RX_FASTLOCK_LOAD_ID: // ad9361_rx_fastlock_load
    case TX_FASTLOCK_LOAD_ID: // ad9361_tx_fastlock_load
        memset(fastLock,0,sizeof(fastLock));
        Current_state = END_PUSH;
        break;
        
        /*SAVE*/
    case RX_FASTLOCK_SAVE_ID:// ad9361_rx_fastlock_save
    case TX_FASTLOCK_SAVE_ID:// ad9361_tx_fastlock_save
        
        mem++; // avoid ocpode
        assign_memory_ch_u32_u08(fastLock,mem,0,15);
        Current_state = END_PUSH;
        send_ACK();
        break;

    case SET_TRX_PATH_CLKS_ID:
        if(set_get == SET)
        {
            mem++;
            memcpy(rx_path_clk,mem,6*sizeof(uint32_t));
            memcpy(tx_path_clk,mem+6,6*sizeof(uint32_t));
        }
        else
        {
            memset(rx_path_clk,0,sizeof(rx_path_clk));
            memset(tx_path_clk,0,sizeof(tx_path_clk));
        }
        Current_state = END_PUSH;
        break;
    case GET_RX_RSSI_ID:
        memset(tx_path_clk,0,sizeof(rssi));
        Current_state = END_PUSH;
        break;

    case GET_RX_FIR_CONFIG_ID:
        //memset(&RX_FIR,0,sizeof(AD9361_RXFIRConfig));
        Current_state = END_PUSH;
        break;

    case GET_TX_FIR_CONFIG_ID:
        memset(&TX_FIR,0,sizeof(AD9361_RXFIRConfig));
        Current_state = END_PUSH;
        break;

    case SET_TX_FIR_CONFIG_ID:
        assign_memory_to_FIR_TX(mem,&TX_FIR);
        send_ACK();
        break;
    case SET_RX_FIR_CONFIG_ID:
        assign_memory_to_FIR_RX(mem,&RX_FIR);
        send_ACK();
        break;
    case TRX_LOAD_ENABLE_FIR_ID:
        
        break;

    default:
        break;
    }
}
void pull_special(uint32_t* mem)
{

    switch (foo_params.opcode )
    {
        /*LOAD*/
    case RX_FASTLOCK_LOAD_ID: // ad9361_rx_fastlock_load
    case TX_FASTLOCK_LOAD_ID: // ad9361_tx_fastlock_load
        assign_memory_ch_u08_u32(mem,fastLock,0,15);
        Current_state = END_PULL;
        break;
    case SET_TRX_PATH_CLKS_ID:
        memcpy(mem,tx_path_clk,sizeof(tx_path_clk));
        memcpy(mem+6,rx_path_clk,sizeof(rx_path_clk));
        Current_state = END_PULL;
        break;
    case GET_RX_RSSI_ID:
        memcpy(mem,tx_path_clk,sizeof(rssi));
        Current_state = END_PULL;
        break;

    case GET_RX_FIR_CONFIG_ID:
        read_memory_to_FIR_RX(mem);
        break;

    case GET_TX_FIR_CONFIG_ID:
        read_memory_to_FIR_RX(mem);
       
        break;
    }
}

/*
========================================================
    MEMEORY MANAGMENT
========================================================
*/

void set_opcode_to_ptypes(long opcode)

{
    foo_params.opcode = opcode; 
    foo_params.P1 = ((7 << 10) & opcode) >> 10;
    foo_params.P2 = ((7 << 13) & opcode) >> 13;
}

paramaters_pair* get_opcode_types()
{
    return &foo_params;
}
/*
========================================================
    CALLBACKS
========================================================
*/
void opcode_callback(struct ad9361_rf_phy *phy)
{
    Caller* lens = NULL;
    char    size = 0;
    uint32_t set_get = foo_params.opcode & 3;
    uint32_t op_saver = foo_params.opcode;
    /*70% of functions has one parameter*/
    if(foo_params.P2 == EMPTY_PARAM)
    {
        switch (foo_params.P1)
        {
            case NOT_SIGNED_8_BIT:
                lens = One_Param_u08;
                size = 16;
                if(set_get == SET)
                {
                    ((u08_t_callback*)callback_id(lens,size,foo_params.opcode))(phy,(uint8_t)FLIP_VALUES[0]);
                }
                else if(set_get == GET)
                {
                    uint8_t get_var = 0;
                    ((u08_t_callback_get*)callback_id(lens,size,foo_params.opcode))(phy,&get_var);
                    FLIP_VALUES[0] = get_var;
                }
                break;
            case NOT_SIGNED_32_BIT:
                lens = One_Param_u32;
                size = 22;
                if(set_get == SET || set_get == NA || set_get == DO)
                {
                    ((u32_t_callback*) callback_id(lens,size,foo_params.opcode))(phy,(uint32_t)FLIP_VALUES[0]);
                }
                else
                {
                    ((u32_t_callback_get*) callback_id(lens,size,foo_params.opcode))(phy,(uint32_t*)(&FLIP_VALUES[0]));
                } 
                break;
            case SIGNED_64_BIT:
                lens = One_Param_u64;
                size = 4;
                if(set_get == SET )
                {   
                    uint64_t var  = ((uint64_t)FLIP_VALUES[1]) << 32;
                    var |= FLIP_VALUES[0];
                    ((u64_t_callback*) callback_id(lens,size,foo_params.opcode))(phy,var);  
                }
                else
                {
                    uint64_t var;
                    ((u64_t_callback_get*) callback_id(lens,size,foo_params.opcode))(phy,&var); 
                    FLIP_VALUES[0] = var>>32;
                    FLIP_VALUES[1] = var & (UINT_MAX);
                }

                break;
            case RXFIR_TYPE://! SPECIAL ONE
                ad9361_set_rx_fir_config(phy,RX_FIR);
                break;
            case TXFIR_TYPE://! SPECIAL ONE
                ad9361_set_tx_fir_config (phy,TX_FIR);
                break;
            default:
                break;
        }
    }/*30% of functions has two parameters*/
    else
    {
        switch (foo_params.P2)
        {
            case NOT_SIGNED_8_BIT:
                if(foo_params.P1 == NOT_SIGNED_8_BIT)
                {
                    lens = Two_Param_u08_u08;
                    size = 2;
                    if(set_get == SET)
                    {
                        ((u08_u08_callback*) callback_id(lens,size,foo_params.opcode))(phy,(uint8_t)FLIP_VALUES[0],(uint8_t)FLIP_VALUES[1]);
                    }
                    else
                    {
                        ((u08_u08_callback_get*) callback_id(lens,size,foo_params.opcode))(phy,(uint8_t)FLIP_VALUES[0],(uint8_t*)(&FLIP_VALUES[1]));
                    }
                }
                else //! SPECIAL ONE
                {
                    lens = Two_Param_u32_u08;
                    size = 4;
                    ((u32_u08_callback*) callback_id(lens,size,foo_params.opcode))(phy,(uint32_t)FLIP_VALUES[0],&fastLock[0]);
                }
                break;
            case NOT_SIGNED_32_BIT:
                if(foo_params.P1 == NOT_SIGNED_8_BIT)
                {
                    lens = Two_Param_u08_u32;
                    size = 3;
                    if(set_get == SET)
                    {
                        ((u08_u32_callback*) callback_id(lens,size,foo_params.opcode))(phy,(uint8_t)FLIP_VALUES[0],(uint32_t)FLIP_VALUES[1]);
                    }
                    else
                    {
                        ((u08_u32_callback_get*) callback_id(lens,size,foo_params.opcode))(phy,(uint8_t)FLIP_VALUES[0],(uint32_t*)(&FLIP_VALUES[1]));
                    }
                }
                else //! SPECIAL ONE
                {
                    lens = Two_Param_u32_u32;
                    size = 2;
                    ((u32_u32_callback*) callback_id(lens,size,foo_params.opcode))(phy,rx_path_clk,tx_path_clk);
                }
                break;

            case SIGNED_32_BIT:
                if(foo_params.P1 == NOT_SIGNED_8_BIT)
                {
                    uint8_t p1 = (uint8_t)FLIP_VALUES[0];
                    int32_t p2 = 0;

                    lens = Two_Param_u08_i32;
                    size = 2;
                    
                    if (set_get == SET)
                    {
                        p2 = (int32_t)(FLIP_VALUES[1]);
                        ad9361_set_rx_rf_gain(phy,p1,p2);
                    }
                    else
                    {
                        ad9361_get_rx_rf_gain(phy,p1,&p2);
                    }
                    p2 = FLIP_VALUES[2];
                }
                else
                {
                    ad9361_do_calib(phy,(uint32_t)FLIP_VALUES[0],(int32_t)FLIP_VALUES[1]);
                }
                break;
            case STRUCT_TYPE:
                    ad9361_get_rx_rssi(phy,(uint8_t)FLIP_VALUES[0],&rssi);
                break;
            case RXFIR_TYPE:
            {
                    //
                    uint32_t temp = foo_params.opcode;
                    uint8_t p1 = FLIP_VALUES[0];
                    //ad9361_get_rx_fir_config(phy,p1,&RX_FIR);
                    foo_params.opcode  = temp;
            }
                break;
            case TXFIR_TYPE:
                if(foo_params.P1 == NOT_SIGNED_8_BIT)
                {
                    ad9361_get_tx_fir_config(phy,(uint8_t)FLIP_VALUES[0],&TX_FIR);
                }
                else
                {
                    ad9361_trx_load_enable_fir(phy,RX_FIR,TX_FIR);
                }
                break;
            default:
                break;
        }
    }
    foo_params.opcode = op_saver;
}

