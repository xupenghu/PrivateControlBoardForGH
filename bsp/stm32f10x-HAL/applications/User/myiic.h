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

//IO方向设置
#define SDA_IN()  {rt_pin_mode(IIC_SDA_PIN, PIN_MODE_INPUT);}	//PB9输入模式
#define SDA_OUT() {rt_pin_mode(IIC_SDA_PIN, PIN_MODE_OUTPUT);}//PB9输出模式
//IO操作函数	 
#define IIC_SCL    PBout(10) //SCL
#define IIC_SDA    PBout(11) //SDA	 
#define READ_SDA   PBin(11)  //输入SDA 





//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















