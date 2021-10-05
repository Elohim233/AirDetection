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

//使用软件模拟I2C
//#define SET_SDA          { HAL_GPIO_WritePin(PCF8563_SDA_GPIO_Port, PCF8563_SDA_Pin, GPIO_PIN_SET); 	} 
//#define RESET_SDA        { HAL_GPIO_WritePin(PCF8563_SDA_GPIO_Port, PCF8563_SDA_Pin, GPIO_PIN_RESET); } 

//#define SET_SCL          { HAL_GPIO_WritePin(PCF8563_SCLK_GPIO_Port, PCF8563_SCLK_Pin, GPIO_PIN_SET);   } 
//#define RESET_SCL        { HAL_GPIO_WritePin(PCF8563_SCLK_GPIO_Port, PCF8563_SCLK_Pin, GPIO_PIN_RESET); } 

#define IIC_SDA_STATE    ( HAL_GPIO_ReadPin(IIC_SDA_GPIO_Port ,IIC_SDA_Pin) )        //获取SDA引脚状态


#define GPIO_PORT_I2C	GPIOC			     // GPIO端口 
#define I2C_SCL_PIN		IIC_SCLK_Pin			 // 连接到SCL时钟线的GPIO 
#define I2C_SDA_PIN		IIC_SDA_Pin			 	// 连接到SDA数据线的GPIO 
 
 
/* 定义读写SCL和SDA的宏 */
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


//IIC 初始化
void IIC_GPIO_Init(void);
//IIC 延时
void IIC_Delay(void);

//IIC 启动函数
void IIC_Start(void);

//IIC 停止函数
void IIC_Stop(void);

//IIC 发送动作
void IIC_SendACK(void);

//IIC 停止动作
void IIC_SendNACK(void);

//IIC 发送单字节
void IIC_SendByte(u8 Data);

//IIC 接收单字节
u8 IIC_RecvByte(void);

//IIC 写入单字节
void Single_Write_IIC(u8 SlaveAddress,u8 REG_Address,u8 REG_data);

//IIC 读取单字节
u8 Single_Read_IIC(u8 SlaveAddress, u8 REG_Address);


u8 IIC_Wait_Ask(void);
u8 IIC_Recv_Byte(u8 ack);


#endif
