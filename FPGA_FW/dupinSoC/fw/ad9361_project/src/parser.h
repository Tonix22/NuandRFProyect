#ifndef PARSER_H
#define PARSER_H
#include "ad9361.h"

void opcode_preanalysis(struct ad9361_rf_phy *phy, long opcode);

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

#endif