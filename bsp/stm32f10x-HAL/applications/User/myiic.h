#ifndef __MYIIC_H
#define __MYIIC_H
#include "rtthread.h" 
#include <stm32f1xx.h>
#include <drivers/pin.h>
#include "sys.h"

#ifndef u8
#define  u8 uint8_t
#endif
#ifndef u32
#define  u32 uint32_t
#endif

#define IIC_SCL_PIN	21	
#define IIC_SDA_PIN 22  

//IO��������
#define SDA_IN()  {rt_pin_mode(IIC_SDA_PIN, PIN_MODE_INPUT);}	//PB9����ģʽ
#define SDA_OUT() {rt_pin_mode(IIC_SDA_PIN, PIN_MODE_OUTPUT);}//PB9���ģʽ
//IO��������	 
#define IIC_SCL    PBout(10) //SCL
#define IIC_SDA    PBout(11) //SDA	 
#define READ_SDA   PBin(11)  //����SDA 





//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















