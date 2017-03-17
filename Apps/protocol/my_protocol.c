#include "my_protocol.h"
#include "usart_driver.h"
#include "nrf24l01_driver.h"

static u8 data_to_send[50];  // �������ݻ���
static u8 data_to_rec[100];  // �������ݻ���

static u8 data_to_send_pc[33];
static u8 data_to_rec_pc[33]; // �ӵ��Խ��յ����ݻ���

static u8 flag_to_master = 0; // ���͵�master�����к�
static u8 flag_to_pc = 0;  // ���͵����Ե����к�

static u8 flag_from_master = 0;  // ��master ���յ������к�
static u8 flag_from_pc = 0; // ��pc���յ������к�



static u16 safe_count = 0; // ��ȫ�������������ʱ��û�д�pc���յ���Ч��Ϣ���򴥷�����
u8 warning = 0; // ֵΪ1 ��������

u8 send_to_master(data_to_master_t data) //��master������
{
	u8 i = 0 ;
	data_to_send[i++] = 0xAA; 
	data_to_send[i++] = 0xAA;
	
	flag_to_master++;
	if(flag_to_master>250)  // �������к�
		flag_to_master = 0;
	
	data_to_send[i++] = data.GPS_data[0];
	data_to_send[i++] = data.GPS_data[1];
  data_to_send[i++] = data.GPS_data[2];
	data_to_send[i++] = data.GPS_data[3];
	
	data_to_send[i++] = data.Height[0];
	data_to_send[i++] = data.Height[1];
	
	data_to_send[i++] = data.order[0];
	data_to_send[i++] = data.order[1];
	data_to_send[i++] = data.order[2];
	data_to_send[i++] = data.order[3];
	data_to_send[i++] = data.order[4];
	data_to_send[i++] = data.order[5]; 
	data_to_send[i++] = data.order[6];
	data_to_send[i++] = data.order[7];
	data_to_send[i++] = data.order[8]; 

	u8 sum = 0;
	for(u8 j = 0;j<i;j++)
		sum += data_to_send[j];
	data_to_send[i++] = sum;
	
	USART1_sendData(data_to_send,i);
	
	return 1;
	
}

u8 rec_from_master(data_from_master_t *data) // ��master ��������
{
	USART1_recData(data_to_rec);
	u8 i = 0;
	for(;i<99;i++)  // ���֡ͷ
	{
		if(data_to_rec[i] == 0xAA && data_to_rec[i+1] == 0xAA)
			break;
	}
	
	u8 j = i;
	u8 sum = 0;
	
	if(i<80)
	{
		i++;i++;
		if(data_to_rec[i] == flag_from_master) //����Ƿ�Ϊ������
			return 0;
		flag_from_master = data_to_rec[i++]; // ���±�־
		
		data->yaw_pit_rol[0] = data_to_rec[i++];
		data->yaw_pit_rol[1] = data_to_rec[i++];
		data->yaw_pit_rol[2] = data_to_rec[i++];
		
		data->pwm1234[0] = data_to_rec[i++];
		data->pwm1234[1] = data_to_rec[i++];
		data->pwm1234[2] = data_to_rec[i++];
		data->pwm1234[3] = data_to_rec[i++];
		data->pwm1234[4] = data_to_rec[i++];
		data->pwm1234[5] = data_to_rec[i++];
		data->pwm1234[6] = data_to_rec[i++];
		data->pwm1234[7] = data_to_rec[i++];
		
		data->pid12[0] = data_to_rec[i++];
		data->pid12[1] = data_to_rec[i++];
		data->pid12[2] = data_to_rec[i++];
		data->pid12[3] = data_to_rec[i++];
		data->pid12[4] = data_to_rec[i++];
		data->pid12[5] = data_to_rec[i++];
		
		data->mag = data_to_rec[i++];
		data->bmp = data_to_rec[i++];
		
		data->err = data_to_rec[i++];
		
		for(;j<i;j++)
			sum += data_to_rec[j];
		
		if(sum != data_to_rec[i])
			return 0;
		
		return 1;
	}
	
	return 0;
//	i++;
//	if(i>99) i = 0;
//	i++;
//	if(i>99) i = 0;
//	
//	if(data_to_rec[i] == flag_from_master)
//		return 0;
//	flag_from_master = data_to_rec[i++];
//	
//	if(i>99) i = 0;
//	
//		data->yaw_pit_rol[0] = data_to_rec[i++];
//	if(i>99) i = 0;
//		data->yaw_pit_rol[1] = data_to_rec[i++];
//	if(i>99) i = 0;
//		data->yaw_pit_rol[2] = data_to_rec[i++];
//	if(i>99) i = 0;
//		
//		data->pwm1234[0] = data_to_rec[i++];
//	if(i>99) i = 0;
//		data->pwm1234[1] = data_to_rec[i++];
//	if(i>99) i = 0;
//		data->pwm1234[2] = data_to_rec[i++];
//	if(i>99) i = 0;
//		data->pwm1234[3] = data_to_rec[i++];
//	if(i>99) i = 0;
//	
//		data->pid12[0] = data_to_rec[i++];
//	if(i>99) i = 0;
//		data->pid12[1] = data_to_rec[i++];
//	if(i>99) i = 0;
//		data->pid12[2] = data_to_rec[i++];
//	if(i>99) i = 0;
//		data->pid12[3] = data_to_rec[i++];
//	if(i>99) i = 0;
//		data->pid12[4] = data_to_rec[i++];
//	if(i>99) i = 0;
//		data->pid12[5] = data_to_rec[i++];
//	if(i>99) i = 0;
//		data->mag = data_to_rec[i++];
//		
//	if(i>99) i = 0;
//		data->bmp = data_to_rec[i++];
//	if(i>99) i = 0;
//		data->err = data_to_rec[i];
//	
//	return 1;
	
}

//======================================================================================================//
u8 send_to_pc(data_to_pc_t data)
{
	
	u8 i = 0;
	data_to_send_pc[i++] = 0xAA;
	data_to_send_pc[i++] = 0xAA;
	data_to_send_pc[i++] = flag_to_pc;
	
	flag_to_pc++;
	if(flag_to_pc>250)
		flag_to_pc = 0;
	
	data_to_send_pc[i++] = data.master_data.yaw_pit_rol[0];
	data_to_send_pc[i++] = data.master_data.yaw_pit_rol[1];
	data_to_send_pc[i++] = data.master_data.yaw_pit_rol[2];
	
	data_to_send_pc[i++] = data.master_data.pwm1234[0];
	data_to_send_pc[i++] = data.master_data.pwm1234[1];
	data_to_send_pc[i++] = data.master_data.pwm1234[2];
	data_to_send_pc[i++] = data.master_data.pwm1234[3];
	data_to_send_pc[i++] = data.master_data.pwm1234[4];
	data_to_send_pc[i++] = data.master_data.pwm1234[5];
	data_to_send_pc[i++] = data.master_data.pwm1234[6];
	data_to_send_pc[i++] = data.master_data.pwm1234[7];
	
	data_to_send_pc[i++] = data.master_data.pid12[0];
	data_to_send_pc[i++] = data.master_data.pid12[1];
	data_to_send_pc[i++] = data.master_data.pid12[2];
	data_to_send_pc[i++] = data.master_data.pid12[3];
	data_to_send_pc[i++] = data.master_data.pid12[4];
	data_to_send_pc[i++] = data.master_data.pid12[5];
	
	
	data_to_send_pc[i++] = data.master_data.mag;
	data_to_send_pc[i++] = data.master_data.bmp;
	
	data_to_send_pc[i++] = data.master_data.err;
	
	data_to_send_pc[i++] = data.slave_data.GPS_data[0];
	data_to_send_pc[i++] = data.slave_data.GPS_data[1];
	data_to_send_pc[i++] = data.slave_data.GPS_data[2];
	data_to_send_pc[i++] = data.slave_data.GPS_data[3];
	
	data_to_send_pc[i++] = data.slave_data.Height[0];
	data_to_send_pc[i++] = data.slave_data.Height[1];
	
	u8 sum = 0;
	for(u8 j = 0;j<i;j++)
		sum += data_to_send_pc[j];
	data_to_send_pc[i++] = sum;
	
	USART2_sendData(data_to_send_pc,i);
	
	return 1;
}

u8 rec_from_pc(data_from_pc_t *data)
{

	
	if(NRF24L01_RxPacket(data_to_rec_pc)) // �������ʧ�ܣ��򷵻�
		return 0;
	
	int i = 0;
	for(;i<31;i++)
	{
		if(data_to_rec_pc[i] == 0xAA && data_to_rec_pc[i+1] == 0xAA)
		{
			if(i<20)
			{
				u8 j = i;
				u8 k = j;
				u8 sum = 0;
				j++;j++;
				
				flag_from_pc = data_to_rec_pc[j++];
				if(flag_from_pc >240)
					flag_from_pc = 0;
		
				data->order[0] = data_to_rec_pc[j++];
				
				data->order[1] = data_to_rec_pc[j++];
				
				data->order[2] = data_to_rec_pc[j++];
				
				data->order[3] = data_to_rec_pc[j++];
				
				data->order[4] = data_to_rec_pc[j++];
				
				data->order[5] = data_to_rec_pc[j++];
					
				data->order[6] = data_to_rec_pc[j++];
				
				data->order[7] = data_to_rec_pc[j++];
				
				data->order[8] = data_to_rec_pc[j++];
				
				for(;k<j;k++)
					sum += data_to_rec_pc[k];
				if(sum == data_to_rec_pc[j])
				{
			

					return 1;
			
				}
				
				
			}
		}
	}
//	i++;
//	if(i>31)i=0;
//	i++;
//	if(i>31)i=0;
//	
//	if(data_to_rec_pc[i] == flag_from_pc) // ������кţ���ͬ��˵���Ǿ����ݣ�����
//		return 0;
//	flag_from_pc = data_to_rec_pc[i++];
//	if(i>31)i=0;
//	
//	data->order[0] = data_to_rec_pc[i++];
//	if(i>31)i=0;
//	data->order[1] = data_to_rec_pc[i++];
//	if(i>31)i=0;
//	data->order[2] = data_to_rec_pc[i++];
//	if(i>31)i=0;
//	data->order[3] = data_to_rec_pc[i++];
//	if(i>31)i=0;
//	data->order[4] = data_to_rec_pc[i++];
//	if(i>31)i=0;
//	data->order[5] = data_to_rec_pc[i++];
//	if(i>31)i=0;

//	
//	return 1;
	
	
}