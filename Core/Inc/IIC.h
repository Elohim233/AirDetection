#ifndef _IIC_h_
#define _IIC_h_


#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "delay.h"

//#define IIC_GPIO (GPIOC)
//#define IIC_GOIO_SDA (GPIOC)
//#define IIC_GPIO_SCL (GPIOC)
//#define IIC_SDA (GPIO_PIN_2)
//#define IIC_SCL (GPIO_PIN_1)

//ʹ�����ģ��I2C
//#define SET_SDA          { HAL_GPIO_WritePin(PCF8563_SDA_GPIO_Port, PCF8563_SDA_Pin, GPIO_PIN_SET); 	} 
//#define RESET_SDA        { HAL_GPIO_WritePin(PCF8563_SDA_GPIO_Port, PCF8563_SDA_Pin, GPIO_PIN_RESET); } 

//#define SET_SCL          { HAL_GPIO_WritePin(PCF8563_SCLK_GPIO_Port, PCF8563_SCLK_Pin, GPIO_PIN_SET);   } 
//#define RESET_SCL        { HAL_GPIO_WritePin(PCF8563_SCLK_GPIO_Port, PCF8563_SCLK_Pin, GPIO_PIN_RESET); } 

#define IIC_SDA_STATE    ( HAL_GPIO_ReadPin(IIC_SDA_GPIO_Port ,IIC_SDA_Pin) )        //��ȡSDA����״̬


#define GPIO_PORT_I2C	GPIOC			     // GPIO�˿� 
#define I2C_SCL_PIN		IIC_SCLK_Pin			 // ���ӵ�SCLʱ���ߵ�GPIO 
#define I2C_SDA_PIN		IIC_SDA_Pin			 	// ���ӵ�SDA�����ߵ�GPIO 
 
 
/* �����дSCL��SDA�ĺ� */
#define SET_SCL  GPIO_PORT_I2C->BSRR = I2C_SCL_PIN											// SCL = 1 
#define RESET_SCL  GPIO_PORT_I2C->BSRR = (uint32_t)I2C_SCL_PIN << 16U  		// SCL = 0 
 
#define SET_SDA  GPIO_PORT_I2C->BSRR = I2C_SDA_PIN   										// SDA = 1 
#define RESET_SDA  GPIO_PORT_I2C->BSRR = (uint32_t)I2C_SDA_PIN << 16U  		// SDA = 0 




#define IIC_DELAY         IIC_Delay(); 

//enum IIC_REPLAY_ENUM
//{
//    IIC_NACK = 0,
//    IIC_ACK = 1
//};

//enum IIC_BUS_STATE_ENUM
//{
//    IIC_BUS_READY = 0,
//    IIC_BUS_BUSY=1,
//    IIC_BUS_ERROR=2
//};


//IIC ��ʼ��
void IIC_GPIO_Init(void);
//IIC ��ʱ
void IIC_Delay(void);

//IIC ��������
void IIC_Start(void);

//IIC ֹͣ����
void IIC_Stop(void);

//IIC ���Ͷ���
void IIC_SendACK(void);

//IIC ֹͣ����
void IIC_SendNACK(void);

//IIC ���͵��ֽ�
void IIC_SendByte(u8 Data);

//IIC ���յ��ֽ�
u8 IIC_RecvByte(void);

//IIC д�뵥�ֽ�
void Single_Write_IIC(u8 SlaveAddress,u8 REG_Address,u8 REG_data);

//IIC ��ȡ���ֽ�
u8 Single_Read_IIC(u8 SlaveAddress, u8 REG_Address);


u8 IIC_Wait_Ask(void);
u8 IIC_Recv_Byte(u8 ack);


#endif
