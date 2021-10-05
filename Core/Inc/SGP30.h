#ifndef _SGP30_h_
#define _SGP30_h_

#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "delay.h"
#include "IIC.h"


//#define SGP30_ADDR          0x58
//#define	SGP30_ADDR_WRITE	SGP30_ADDR<<1       //0xb0
//#define	SGP30_ADDR_READ		(SGP30_ADDR<<1)+1   //0xb1


#define SGP30_ADDR      								0x58
#define SGP30_Feature_Set   						0x0020
#define SGP30_Init_air_quality 					0x2003
#define SGP30_Measure_air_quality   		0x2008
#define SGP30_Get_baseline 							0x2015
#define SGP30_Set_baseline 							0x201e
#define SGP30_Set_humidity							0x2061
#define SGP30_Measure_test 							0x2032
#define SGP30_Get_feature_set_version		0x202f
#define SGP30_Measure_raw_signals				0x2050

#define I2C_WR	0		/* 写控制bit */
#define I2C_RD	1		/* 读控制bit */
#define SGP30_read  0xb1  //SGP30的读地址
#define SGP30_write 0xb0  //SGP30的写地址

uint8_t SGP30_I2C_CheckDevice(uint8_t _Address);
uint32_t SGP30_I2C_Read_CO2_TVOC(uint8_t _Address);
static u8 CRC_Check(u8 *check_data,u8 num,u8 check_crc);
void  SGP30_Init(void);
void SGP30_Write(u8 a, u8 b);
u32 SGP30_Read(void);
#endif
