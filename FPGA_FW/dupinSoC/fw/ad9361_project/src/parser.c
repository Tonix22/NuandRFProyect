#include "stdio.h"
#include "parser.h"
#include <stdint.h>
#include "ad9361_api.h"

typedef struct Action
{
    uint32_t ID;
    void* foo;
}Caller;

typedef int32_t u08_t_callback (struct ad9361_rf_phy* , uint32_t);
Caller One_Param_u08[16] = 
{   
    {0x455, &ad9361_set_rx_lo_int_ext        },
    {0x4A5, &ad9361_set_rx_fir_en_dis        },
    {0x4A6, &ad9361_get_rx_fir_en_dis        },
    {0x4B5, &ad9361_set_rx_rfdc_track_en_dis },
    {0x4B6, &ad9361_get_rx_rfdc_track_en_dis },
    {0x4C5, &ad9361_set_rx_bbdc_track_en_dis },
    {0x4C6, &ad9361_get_rx_bbdc_track_en_dis },
    {0x4D5, &ad9361_set_rx_quad_track_en_dis },
    {0x4D6, &ad9361_get_rx_quad_track_en_dis },
    {0x459, &ad9361_set_tx_lo_int_ext        },
    {0x4A9, &ad9361_set_tx_fir_en_dis        },
    {0x4AA, &ad9361_get_tx_fir_en_dis        },
    {0x559, &ad9361_set_tx_auto_cal_en_dis   },
    {0x55A, &ad9361_get_tx_auto_cal_en_dis   },
    {0x571, &ad9361_set_no_ch_mode           },
    {0x4AD, &ad9361_set_trx_fir_en_dis       },

};

typedef int32_t u32_t_callback (struct ad9361_rf_phy* , uint32_t);

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
    {0x99D, &ad9361_set_trx_rate_gov          },
    {0x99E, &ad9361_get_trx_rate_gov          },
    {0x9C3, &ad9361_do_dcxo_tune_coarse       },
    {0x9D3, &ad9361_do_dcxo_tune_fine         },
};

typedef int32_t u64_t_callback (struct ad9361_rf_phy *, uint64_t);

Caller One_Param_u64 [4] = 
{
    {0x1045, &ad9361_set_rx_lo_freq},
    {0x1046, &ad9361_get_rx_lo_freq},
    {0x1049, &ad9361_set_tx_lo_freq},
    {0x104A, &ad9361_get_tx_lo_freq},
};

/***********************************
********* TWO PARAMETER ************
*************************************/

typedef int32_t u08_u08_callback (struct ad9361_rf_phy *, uint8_t, uint8_t);

Caller Two_Param_u08_u08 [2] = 
{
    {0x2475,&ad9361_set_rx_gain_control_mode},
    {0x2476,&ad9361_get_rx_gain_control_mode},
};

typedef int32_t u08_u32_callback (struct ad9361_rf_phy *, uint8_t, uint32_t);

Caller Two_Param_u08_u32 [4]=
{
    {0x2914, &ad9361_rx_fastlock_load},
    {0x2924, &ad9361_rx_fastlock_save},
    {0x2918, &ad9361_tx_fastlock_load},
    {0x2928, &ad9361_tx_fastlock_save},
};

typedef int32_t u32_u08_callback (struct ad9361_rf_phy *, uint32_t, uint8_t);

Caller Two_Param_u32_u08 [3]=
{
    {0x4539,&ad9361_set_tx_attenuation },
    {0x453A,&ad9361_get_tx_attenuation },
    {0x446A,&ad9361_get_tx_rssi },
};

typedef int32_t u32_u32_callback (struct ad9361_rf_phy *, uint32_t, uint32_t);

Caller Two_Param_u32_u32 [2]=
{
    {0x496D,&ad9361_set_trx_path_clks},
    {0x496E,&ad9361_get_trx_path_clks},
};

typedef int32_t i32_u08_callback (struct ad9361_rf_phy *, int32_t, uint8_t);
Caller Two_Param_i32_u08 [2]=
{
    { 0x6415, &ad9361_set_rx_rf_gain},
    { 0x6416, &ad9361_get_rx_rf_gain},
};

uint64_t FLIP_VALUES[2];

void* opcode_callback(Caller* var,char size,uint32_t opcode)
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


void push_param(uint64_t var,char idx)
{
    if(idx < 2)
    {
        FLIP_VALUES[idx]=var;
    }
}


void opcode_preanalysis(struct ad9361_rf_phy *phy, long opcode)
{
    char flag_parm1 = ((7 << 10) & opcode) >> 10;
    char flag_parm2 = ((7 << 13) & opcode) >> 13;
    Caller* lens = NULL;
    char    size = 0;

    if(flag_parm2 == EMPTY_PARAM)
    {
        switch (flag_parm1)
        {
            case NOT_SIGNED_8_BIT:
                lens = One_Param_u08;
                size = 16;
                ((u08_t_callback*)opcode_callback(lens,size,opcode))(phy,(uint8_t)FLIP_VALUES[0]);
                break;
            case NOT_SIGNED_32_BIT:
                lens = One_Param_u32;
                size = 22;
                ((u32_t_callback*) opcode_callback(lens,size,opcode))(phy,(uint32_t)FLIP_VALUES[0]);
                break;
            case SIGNED_64_BIT:
                lens = One_Param_u64;
                size = 4;
                ((u64_t_callback*) opcode_callback(lens,size,opcode))(phy,FLIP_VALUES[0]);
                break;
            case RXFIR_TYPE:
                break;
            default:
                break;
        }
    }
    else
    {
        switch (flag_parm2)
        {
            case NOT_SIGNED_8_BIT:
                if(flag_parm1 == NOT_SIGNED_8_BIT)
                {
                    lens = Two_Param_u08_u08;
                    size = 2;
                    ((u08_u08_callback*) opcode_callback(lens,size,opcode))(phy,(uint8_t)FLIP_VALUES[0],(uint8_t)FLIP_VALUES[1]);
                }
                else
                {
                    lens = Two_Param_u08_u32;
                    size = 4;
                    ((u08_u32_callback*) opcode_callback(lens,size,opcode))(phy,(uint8_t)FLIP_VALUES[0],(uint32_t)FLIP_VALUES[1]);
                }
                break;
            case NOT_SIGNED_32_BIT:
                if(flag_parm1 == NOT_SIGNED_8_BIT)
                {
                    lens = Two_Param_u32_u08;
                    size = 3;
                    ((u32_u08_callback*) opcode_callback(lens,size,opcode))(phy,(uint32_t)FLIP_VALUES[0],(uint8_t)FLIP_VALUES[1]);
                }else
                {
                    lens = Two_Param_u32_u32;
                    size = 2;
                    ((u32_u32_callback*) opcode_callback(lens,size,opcode))(phy,(uint32_t)FLIP_VALUES[0],(uint32_t)FLIP_VALUES[1]);
                }
                break;
            case SIGNED_32_BIT:
                if(flag_parm1 == NOT_SIGNED_8_BIT)
                {
                    lens = Two_Param_i32_u08;
                    size = 2;
                    ((i32_u08_callback*) opcode_callback(lens,size,opcode))(phy,0,0);
                }
                else
                {
                    ad9361_do_calib(phy,0,0);
                }
                break;
            case STRUCT_TYPE:
                    ad9361_get_rx_rssi(phy,0,NULL);
                break;
            case RXFIR_TYPE:
                    ad9361_get_rx_fir_config(phy,0,NULL);
                break;
            case TXFIR_TYPE:
                if(flag_parm1 == NOT_SIGNED_8_BIT)
                {
                    ad9361_get_tx_fir_config(phy,0,NULL);
                }
                else
                {
                    //ad9361_trx_load_enable_fir(phy,NULL,NULL);
                }
                break;
            default:
                break;
        }
    }
}

