#ifndef _MY_PROTOCOL_H_
#define _MY_PROTOCOL_H_
#include "stm32f10x.h"



#define CLEAR_SD 		0x00
#define OFFSET   		0x01
#define WRITE_PID 	0x02

#define GAS_CRTL  	0x03
#define LEFT      	0x04
#define RIGHT     	0x05
#define FRONT     	0x06
#define BACK      	0x07
#define HOLD_HEIGHT 0x08
#define AUTO_DOWN   0x09
#define FLY_START   0x0A

#define SAFE_STOP   0x11
#define CONNECT_TIP 0x22


//////////////////////////////////////

typedef struct data_to_master
{
	u8 GPS_data[4];
	u8 Height[2];
	u8 order[9]; // ���� ����ƫ�� ǰ��ƫ��
	
}data_to_master_t;

typedef struct data_from_master
{
	u8 yaw_pit_rol[3];
	u8 pwm1234[8];
	u8 pid12[6];
	u8 mag;
	u8 bmp;
	u8 err;
	
}data_from_master_t;

//-------------------------------------+
typedef struct data_to_pc
{
	data_from_master_t master_data;
	data_to_master_t   slave_data;
	
}data_to_pc_t;

typedef struct data_from_pc
{
	u8 order[9];

}data_from_pc_t;

typedef struct data_to_slave
{
	data_from_pc_t order;
}data_to_slave_t;

typedef struct data_from_slave
{
	data_to_pc_t slave_data;
}data_from_slave_t;
	

/////////////////////////////////////////////////////////////

u8 send_to_master(data_to_master_t data); 

u8 rec_from_master(data_from_master_t *data); 

u8 send_to_pc(data_to_pc_t data);

u8 rec_from_pc(data_from_pc_t *data);



#endif 