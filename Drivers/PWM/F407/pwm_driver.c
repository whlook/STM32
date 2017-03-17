#include "pwm_driver.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"



static void delay_ms(u16 nms) // ����ȷ��ʱ
{	
	
	uint16_t i,j;
	
	for(i=0;i<nms;i++)
		for(j=0;j<30000;j++);
	
} 

/*ʹ�õ���TIM3*/
void PWM_Init(void)
{
	/*��ؽṹ�嶨��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	/*ʹ�����ʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	   
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB,ENABLE); 	
	
	/*GPIO�˿ڸ���*/
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3); //����Ϊ��ʱ��3
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3); //����Ϊ��ʱ��3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3); //����Ϊ��ʱ��3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3); //����Ϊ��ʱ��3

	/*�˿ڳ�ʼ��*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;   //GPIOA
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //��ʼ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;  //GPIOB
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOB,&GPIO_InitStructure);              //��ʼ��
	
	/*��ʱ����ʼ��*/
	TIM_TimeBaseStructure.TIM_Prescaler=21-1;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=10000-1;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//��ʼ����ʱ��3
	
	//��ʼ��TIM3 Channel PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  
	TIM_OC3Init(TIM3, &TIM_OCInitStructure); 
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  

  //ʹ��Ԥװ��ֵ
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable); 
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable); 
 
  TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPEʹ�� 
	TIM_CtrlPWMOutputs(TIM3,ENABLE);
	
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3
	
}

void Set_ESC(void)
{
		TIM3->CCR1 = 8000; 
		TIM3->CCR2 = 8000;
		TIM3->CCR3 = 8000; 
		TIM3->CCR4 = 8000;
		delay_ms(4000);
	
		TIM3->CCR1 = 4000; 
		TIM3->CCR2 = 4000;
		TIM3->CCR3 = 4000; 
		TIM3->CCR4 = 4000;
		delay_ms(2000);
	
		TIM3->CCR1 = 4200; 
		TIM3->CCR2 = 4200;
		TIM3->CCR3 = 4200; 
		TIM3->CCR4 = 4200;
}

void Set_PWM1(u16 pwm_value)
{
	if(pwm_value<4000)
		pwm_value = 4000;
	if(pwm_value>8000)
		pwm_value = 8000;
	
	TIM3->CCR1 = pwm_value;
}
void Set_PWM2(u16 pwm_value)
{
	if(pwm_value<4000)
		pwm_value = 4000;
	if(pwm_value>8000)
		pwm_value = 8000;
	
	TIM3->CCR2 = pwm_value;
}
void Set_PWM3(u16 pwm_value)
{
	if(pwm_value<4000)
		pwm_value = 4000;
	if(pwm_value>8000)
		pwm_value = 8000;
	
	TIM3->CCR3 = pwm_value;
}
void Set_PWM4(u16 pwm_value)
{
	if(pwm_value<4000)
		pwm_value = 4000;
	if(pwm_value>8000)
		pwm_value = 8000;
	TIM3->CCR4 = pwm_value;
}