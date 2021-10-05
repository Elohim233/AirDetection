#include "SGP30.h"


/*
*****************************************************************************************************************
*		函数名：SGP30_I2C_CheckDevice
*		功能说明：检测I2C总线设备，CPU向发送设备地址，然后读取设备应答来判断设备是否存在
*		形参：_Address:设备的I2C总线地址
*		返回值：返回值0表示正确，返回1表示未探测到
*******************************************************************************************************************
*/
uint8_t SGP30_I2C_CheckDevice(uint8_t _Address)
{
		uint8_t ucAck;
		IIC_Start();							//发送启动信号
	
		/* 发送设备地址+读写控制bit(0 = w, 1 = r)bit7 先传*/
		IIC_SendByte(_Address|I2C_WR);
		ucAck = IIC_Wait_Ask();		//检测设备的ACK应答
		IIC_Stop();								//发送停止信号
		return ucAck;
}

/*
*****************************************************************************************************************
*		函数名：SGP30_I2C_Read_CO2_TVOC
*		功能说明：读取数据
*		形参：_Address:设备的I2C总线地址
*		返回值：返回值0表示正确，返回1表示未探测到
*******************************************************************************************************************
*/

uint32_t SGP30_I2C_Read_CO2_TVOC(uint8_t _Address)
{
		u32 Read_CO2_TVOC=0;
		u8  CRC_Check;
		IIC_Start();							//发送启动信号	
		/* 发送设备地址+读写控制bit(0 = w, 1 = r)bit7 先传*/
		IIC_SendByte(_Address<<1|I2C_WR);
		IIC_Wait_Ask();		//检测设备的ACK应答
		IIC_SendByte(0x20);
		IIC_Wait_Ask();		//检测设备的ACK应答
		IIC_SendByte(0x08);
		IIC_Wait_Ask();		//检测设备的ACK应答
		IIC_Stop();								//发送停止信号	
		HAL_Delay(1000);
		IIC_Start();							//发送启动信号
		IIC_SendByte(_Address<<1|I2C_RD);   //读取设备的特征集	
		IIC_Wait_Ask();		//检测设备的ACK应答
		Read_CO2_TVOC |= (u16)(IIC_Recv_Byte(1)<<8);
		Read_CO2_TVOC |= (u16)(IIC_Recv_Byte(1));
		CRC_Check = IIC_Recv_Byte(1);
		Read_CO2_TVOC |= (u32)(IIC_Recv_Byte(1)<<24);
		Read_CO2_TVOC |= (u32)(IIC_Recv_Byte(1)<<16);
		CRC_Check = IIC_Recv_Byte(0);
		IIC_Stop();								//发送停止信号
		return Read_CO2_TVOC;
}

/*
----------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------
*/
//CRC校验-8位
static u8 CRC_Check(u8 *check_data,u8 num,u8 check_crc)
{
		uint8_t bit;										//bit mask
		uint8_t crc = 0xFF;							//caculated checksum
		uint8_t byteCtr;								//byte counter
	
	
		//calculates 8Bit checksum with given polynomial x8+x5+x4+1
		for(byteCtr = 0; byteCtr < num; byteCtr++)
		{
				crc ^= (*(check_data+byteCtr));
				//CRC校验，最高为是1就^0x31
				for(bit = 8; bit > 0;--bit)
				{
						if(crc & 0x80)
							crc = (crc << 1)^0x31;
						else
							crc = (crc << 1);
				
				}
		}
		
		if(crc == check_crc)
			return 1;
		else
			return 0;
	
}


/*
			SGP30   初始化

*/
void  SGP30_Init(void)
{
		IIC_GPIO_Init();
		IIC_Start();							//发送启动信号
		/* 发送设备地址+读写控制bit(0 = w, 1 = r)bit7 先传*/
		IIC_SendByte(SGP30_ADDR<<1);
		IIC_Wait_Ask();		//检测设备的ACK应答
		IIC_SendByte(0x20);
		IIC_Wait_Ask();		//检测设备的ACK应答
		IIC_SendByte(0x03);
		IIC_Wait_Ask();		//检测设备的ACK应答	
		IIC_Stop();								//发送停止信号		
		HAL_Delay(1000);
	
}






