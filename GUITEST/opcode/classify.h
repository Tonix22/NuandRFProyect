#ifndef classify_H
#define classify_H

#include <string>

typedef enum
{
    none,
    b_8,
    b_32,
    b_64,
}bit_size;
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
    std::string name;
    set_get set;
    set_get get;
}word_and_parms;


#endif