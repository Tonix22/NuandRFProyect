#ifndef PARSER_H
#define PARSER_H
#include "ad9361.h"
#include "ad9361_api.h"

typedef enum
{
    GET_RX_RSSI_ID         = 0xA466,
    SET_RX_FIR_CONFIG_ID   = 0x1885,
    GET_RX_FIR_CONFIG_ID   = 0xC496,
    RX_FASTLOCK_LOAD_ID    = 0x2914,
    SET_TX_FIR_CONFIG_ID   = 0x1C89,
    GET_TX_FIR_CONFIG_ID   = 0xE49A,
    TX_FASTLOCK_LOAD_ID    = 0x2918,
    SET_TRX_PATH_CLKS_ID   = 0x496D,
    TRX_LOAD_ENABLE_FIR_ID = 0xF9BC,
    SPECIAL_SIZE = 9
}Special_ids_t;

typedef enum{
    NA,
    SET,
    GET,
    DO,
}Encapsulators;

typedef enum
{
    EMPTY_PARAM,
    NOT_SIGNED_8_BIT,
    NOT_SIGNED_32_BIT,
    SIGNED_32_BIT,
    SIGNED_64_BIT,
    STRUCT_TYPE ,
    RXFIR_TYPE  ,
    TXFIR_TYPE,
}Param_types;

typedef struct p_list
{
    Param_types P1;
    Param_types P2;
    uint32_t opcode;
}paramaters_pair;

typedef struct Action
{
    uint32_t ID;
    void* foo;
}Caller;

void opcode_callback(struct ad9361_rf_phy *phy);
void push_param(uint32_t var,unsigned char idx);
void set_opcode_to_ptypes(long opcode);
paramaters_pair* get_opcode_types();


#endif