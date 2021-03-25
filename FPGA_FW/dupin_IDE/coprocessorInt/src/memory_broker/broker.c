#include <stdio.h>
#include <string.h>
#include "broker.h"
#include "parser.h"
#include "isr_handler.h"
#include "aip.h"


extern volatile DataStat ISR_FLAG;

extern Special_ids_t     Special_Opcodes[SPECIAL_SIZE];
extern uint32_t          FLIP_VALUES[2];

/*read_memory globals*/
uint32_t data[MAX_READ_SIZE];

/*load_memory globals*/
paramaters_pair* ptypes_ref;
uint8_t data_size = 0;
InternatlStates Current_state = NORMAL;



void read_memory()
{

    Mem_stat status   =  Busy;
    aip_write(0x1e, &status, 1, 0);

    /*clear buffer*/
    memset(data,0,MAX_READ_SIZE*sizeof(uint32_t));

    if(Current_state == NORMAL)
    {
        aip_read(0x0, data, STANDAR_READ_SIZE, 0);
        //aip_write(0x2, data, 10, 0);
    }
    else if(Current_state == SPECIAL_SET)
    {
        aip_read(0x0, data, MAX_READ_SIZE, 0);
    }

    /* done */
	status = Done;
	aip_write(0x1e, &status, 1, 0);

}

void load_memory()
{
    set_opcode_to_ptypes(data[OPCODE_IDX]);
    ptypes_ref    = get_opcode_types();
    Current_state = NORMAL;

    /*Analyse if opcode need special cycles*/
    for(int i = 0;i < SPECIAL_SIZE;i++)
    {
        if(ptypes_ref->opcode == Special_Opcodes[i])
        {
            if((ptypes_ref->opcode >> 1) & 1)
            {
                Current_state = SPECIAL_GET;
            }
            else 
            {
                Current_state = SPECIAL_SET;
            } 
            break;
        }
    }
    /*Almost 87% of cases*/
    if(Current_state == NORMAL)
    {
        if(ptypes_ref->P2 == EMPTY_PARAM && ptypes_ref->opcode != 0x1045)
        {   
            push_param(data[P1_IDX] ,P1_NUM);
        }
        else
        {
            push_param(data[P1_IDX] ,P1_NUM);
            push_param(data[P2_IDX] ,P2_NUM);
        }
    }
    else /*The special 13*%*/
    {
        while(Current_state == SPECIAL_SET)
        {
            push_special(data);//update state internally
            read_memory();
        }
    }

}
void send_response()
{
    uint32_t set_get; 
    ptypes_ref    = get_opcode_types();
    set_get = ptypes_ref->opcode & 3;
    if(set_get == GET )
    {
        aip_write(0x2, &FLIP_VALUES[0], 1, 0);
    }
    
}
void Subscribe_broker(struct ad9361_rf_phy *ad9361_phy)
{
    int_isr();
	for(;;)
	{
		if(ISR_FLAG == READ) // when an start is sent
		{
            //dummy();
            read_memory();
            load_memory();
			opcode_callback(ad9361_phy);
            send_response();
            ISR_FLAG = IDLE;
		}
	}
}

