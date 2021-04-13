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
    else if(Current_state == SPECIAL_SET || Current_state == SPECIAL_GET)
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
            if( ptypes_ref->opcode & 1 ||
                ptypes_ref->opcode == RX_FASTLOCK_SAVE_ID ||
                ptypes_ref->opcode == TX_FASTLOCK_SAVE_ID )
            {
                Current_state = SPECIAL_SET;
            }
            else 
            {
                Current_state = SPECIAL_GET;
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
        if(Current_state == SPECIAL_SET)
        {
            clear_OUT_BUFF();
            push_param(data[P1_IDX] ,P1_NUM);
            send_ACK();
            ISR_FLAG = IDLE; // hold until
            while(Current_state == SPECIAL_SET)
            {
                if(ISR_FLAG == READ)
                {
                    ISR_FLAG = IDLE;
                    read_memory();//mdata in read
                    clear_OUT_BUFF();//mdaout clear
                    push_special(data);//update state internally
                }
            }
            Current_state = NORMAL;
        }
        else
        {
            read_memory();
            push_special(NULL);//clear data
            Current_state = SPECIAL_GET;
        }
        clear_OUT_BUFF();
    }
    
}

void send_ACK()
{
    uint32_t code[4] = {0};
    code[0]='A';
    code[1]='C';
    code[2]='K';
    aip_write(0x2, &code[0], 4, 0);
}
void send_EOF()
{
    uint32_t code[4] = {0};
    code[0]='E';
    code[1]='O';
    code[2]='F';
    aip_write(0x2, &code[0], 4, 0);
}
void clear_OUT_BUFF()
{
    uint32_t code[4] = {0};
    aip_write(0x2, &code[0], 4, 0);
}

void send_response()
{
    uint32_t set_get;
    uint32_t cnt = 0;

    ptypes_ref    = get_opcode_types();
    set_get = ptypes_ref->opcode & 3;
    if(Current_state == SPECIAL_GET)
    {
        clear_OUT_BUFF();
        while(Current_state == SPECIAL_GET)
        {
            if(ISR_FLAG == READ) // wait a start as ACK
            {
                ISR_FLAG = IDLE;
                read_memory();
                clear_OUT_BUFF();
                pull_special(data);//update state internally
                aip_write(0x2, &data[0], MAX_READ_SIZE, 0);
            }
        }
        while(ISR_FLAG == IDLE);
        ISR_FLAG = IDLE;
        send_EOF();
    }
    else
    {
        if(set_get == GET && ptypes_ref->P2 == EMPTY_PARAM)
        {
            aip_write(0x2, &FLIP_VALUES[0], 1, 0);
            while(ISR_FLAG != READ && cnt++ < 60000000);// wait respose from GUI
        }
        else if(set_get == GET)
        {
            // two parameter functions work with one parameter as input
            // the other one as ouput. That's the reason for FLIP_VALUES[1]
            aip_write(0x2, &FLIP_VALUES[1], 1, 0);
            while(ISR_FLAG != READ && cnt++ < 60000000);// wait respose from GUI
        }
    }
}
void Subscribe_broker(struct ad9361_rf_phy *ad9361_phy)
{
    int_isr();
    clear_OUT_BUFF();
	for(;;)
	{
		if(ISR_FLAG == READ) // when an start is sent
		{
            clear_OUT_BUFF(); // clear MDATA OUT
            read_memory();
            load_memory();
			opcode_callback(ad9361_phy);
            send_response();
            memset(FLIP_VALUES,0,2*sizeof(uint32_t));
            ISR_FLAG = IDLE;
		}
	}
}

