/***********************************************

	Fly2017  < 2017-1-13 >
	MPU9250 �������� �⺯���汾

************************************************/
#include "mpu9250_driver.h"
#include "i2c_driver.h"
#include "stm32f4xx_gpio.h"

/*=================================================*

	author: wuhui
	version: 2017.1.13
	input: 
	output: 
	description: 

 *=================================================*/
static short int GetData(unsigned char slave_address,unsigned char REG_Address)
{
	short int H,L;
	
	H=I2C1_ByteRead_Reg(slave_address,REG_Address);
	L=I2C1_ByteRead_Reg(slave_address,REG_Address+1);
	
	return ((H<<8)+L);
	
}

/*=================================================*

	author: wuhui
	version: 2017.1.13
	input: 
	output: 
	description: 

 *=================================================*/
static short int GetData_L(unsigned char slave_address,unsigned char REG_Address)
{
	short int H,L;
	
	L=I2C1_ByteRead_Reg(slave_address,REG_Address);
	H=I2C1_ByteRead_Reg(slave_address,REG_Address+1);
	
	return ((H<<8)+L);
}

// delay ms // 
static void delay_ms(u16 nms)
{	
	
	uint16_t i,j;
	
	for(i=0;i<nms;i++)
		for(j=0;j<8500;j++);
	
} 

/*=================================================*

	author: wuhui
	version: 2017.1.13
	input: 
	output: 
	description: 

 *=================================================*/
void MPU9250_init(void)
{

	I2C1_ByteWrite_Reg(0xd0,MPU6500_PWR_MGMT_1,0x00);  		 // wake up mpu6500
	delay_ms(10);
	
	I2C1_ByteWrite_Reg(0xd0,MPU6500_SMPLRT_DIV,0x07);      // 1000/(7+1) = 125Hz
	delay_ms(10);
	
	I2C1_ByteWrite_Reg(0xd0,MPU6500_CONFIG,0x06);          // gyro low pass 5Hz
	delay_ms(10);
	
	I2C1_ByteWrite_Reg(0xd0,MPU6500_GYRO_CONFIG,0x18);     // +-2000 dps
	delay_ms(10);
	
	I2C1_ByteWrite_Reg(0xd0,MPU6500_ACCEL_CONFIG,0x10);    // +-8g
	delay_ms(10);
	
	I2C1_ByteWrite_Reg(0xd0,MPU6500_ACCEL_CONFIG_2,0x06);  // acc low pass 5Hz
	delay_ms(10);
//+----------------------------------------------------+
	I2C1_ByteWrite_Reg(0xd0,MPU6500_USER_CTRL,0x00);       //  disable master , if open ,0x20
	delay_ms(10);
	
	I2C1_ByteWrite_Reg(0xd0,MPU6500_INT_PIN_CFG,0x02);     // open passby
	delay_ms(10);
//+----------------------+
	I2C1_ByteWrite_Reg(0x18,0x0a,0x06);                    // open ak's read
	delay_ms(10);
//+----------------------+
	I2C1_ByteWrite_Reg(0xd0,MPU6500_USER_CTRL,0x20);       //
	delay_ms(10);
	
	I2C1_ByteWrite_Reg(0xd0,MPU6500_INT_PIN_CFG,0x00);     //
	delay_ms(10);
	
}

/*=================================================*

	author: wuhui
	version: 2017.1.13
	input: 
	output: 
	description: 

 *=================================================*/

#define CONSTANTS_ONE_G			  9.7950f		/* m/s^2 */
#define PI                    3.141592654
#define SENSOR_MAX_G          8.0f        // g
#define SENSOR_MAX_W          2000.0f     // deg/s
#define ACC_SCALE             (SENSOR_MAX_G/32768.0f)  // turn to g
#define GYRO_SCALE            (SENSOR_MAX_W/32768.0f)  // turn to deg

MPU9250_read_data_t   MPU9250_get_data(void)
{
	MPU9250_read_data_t temp;
	
	/****  raw data  ****/
	temp.acc_x = GetData(0xd0,MPU6500_ACCEL_XOUT_H);
	temp.acc_y = GetData(0xd0,MPU6500_ACCEL_YOUT_H);
	temp.acc_z = GetData(0xd0,MPU6500_ACCEL_ZOUT_H);
	
	temp.gyro_x = GetData(0xd0,MPU6500_GYRO_XOUT_H);
	temp.gyro_y = GetData(0xd0,MPU6500_GYRO_YOUT_H);
	temp.gyro_z = GetData(0xd0,MPU6500_GYRO_ZOUT_H);
	
	temp.temperature = GetData(0xd0,MPU6500_TEMP_OUT_H);
	
	/****  turn to physical  ****/
	temp.acc_x = (float)temp.acc_x*ACC_SCALE*CONSTANTS_ONE_G;  //g  
	temp.acc_y = (float)temp.acc_y*ACC_SCALE*CONSTANTS_ONE_G;
	temp.acc_z = (float)temp.acc_z*ACC_SCALE*CONSTANTS_ONE_G;
	
	
	temp.gyro_x = (float)temp.gyro_x*GYRO_SCALE*180.f/PI;      // deg/s   
	temp.gyro_y = (float)temp.gyro_y*GYRO_SCALE*180.f/PI;
	temp.gyro_z = (float)temp.gyro_z*GYRO_SCALE*180.f/PI;
	
	temp.temperature = (float)temp.temperature/340 + 36.53;    // ��
	
	

//	I2C1_ByteWrite_Reg(0xd0,MPU6500_USER_CTRL,0x00); //  disable master , if open ,0x20
//	I2C1_ByteWrite_Reg(0xd0,MPU6500_INT_PIN_CFG,0x02); // open passby
//			
//	temp.mag_x = GetData_L(0x18,AK8963_HXL);
//	temp.mag_y = GetData_L(0x18,AK8963_HYL);
//  temp.mag_z = GetData_L(0x18,AK8963_HZL);			
//	
//	I2C1_ByteRead_Reg(0x18,0x09);  // read st2 to finish reading mag, only after this ,data can be reflush!!!!
//			
//	I2C1_ByteWrite_Reg(0xd0,MPU6500_USER_CTRL,0x20);
//	I2C1_ByteWrite_Reg(0xd0,MPU6500_INT_PIN_CFG,0x00);
	
	return temp;
	
		
}


