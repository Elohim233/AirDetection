#include "SGP30.h"


/*
*****************************************************************************************************************
*		��������SGP30_I2C_CheckDevice
*		����˵�������I2C�����豸��CPU�����豸��ַ��Ȼ���ȡ�豸Ӧ�����ж��豸�Ƿ����
*		�βΣ�_Address:�豸��I2C���ߵ�ַ
*		����ֵ������ֵ0��ʾ��ȷ������1��ʾδ̽�⵽
*******************************************************************************************************************
*/
uint8_t SGP30_I2C_CheckDevice(uint8_t _Address)
{
		uint8_t ucAck;
		IIC_Start();							//���������ź�
	
		/* �����豸��ַ+��д����bit(0 = w, 1 = r)bit7 �ȴ�*/
		IIC_SendByte(_Address|I2C_WR);
		ucAck = IIC_Wait_Ask();		//����豸��ACKӦ��
		IIC_Stop();								//����ֹͣ�ź�
		return ucAck;
}

/*
*****************************************************************************************************************
*		��������SGP30_I2C_Read_CO2_TVOC
*		����˵������ȡ����
*		�βΣ�_Address:�豸��I2C���ߵ�ַ
*		����ֵ������ֵ0��ʾ��ȷ������1��ʾδ̽�⵽
*******************************************************************************************************************
*/

uint32_t SGP30_I2C_Read_CO2_TVOC(uint8_t _Address)
{
		u32 Read_CO2_TVOC=0;
		u8  CRC_Check;
		IIC_Start();							//���������ź�	
		/* �����豸��ַ+��д����bit(0 = w, 1 = r)bit7 �ȴ�*/
		IIC_SendByte(_Address<<1|I2C_WR);
		IIC_Wait_Ask();		//����豸��ACKӦ��
		IIC_SendByte(0x20);
		IIC_Wait_Ask();		//����豸��ACKӦ��
		IIC_SendByte(0x08);
		IIC_Wait_Ask();		//����豸��ACKӦ��
		IIC_Stop();								//����ֹͣ�ź�	
		HAL_Delay(1000);
		IIC_Start();							//���������ź�
		IIC_SendByte(_Address<<1|I2C_RD);   //��ȡ�豸��������	
		IIC_Wait_Ask();		//����豸��ACKӦ��
		Read_CO2_TVOC |= (u16)(IIC_Recv_Byte(1)<<8);
		Read_CO2_TVOC |= (u16)(IIC_Recv_Byte(1));
		CRC_Check = IIC_Recv_Byte(1);
		Read_CO2_TVOC |= (u32)(IIC_Recv_Byte(1)<<24);
		Read_CO2_TVOC |= (u32)(IIC_Recv_Byte(1)<<16);
		CRC_Check = IIC_Recv_Byte(0);
		IIC_Stop();								//����ֹͣ�ź�
		return Read_CO2_TVOC;
}

/*
----------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------
*/
//CRCУ��-8λ
static u8 CRC_Check(u8 *check_data,u8 num,u8 check_crc)
{
		uint8_t bit;										//bit mask
		uint8_t crc = 0xFF;							//caculated checksum
		uint8_t byteCtr;								//byte counter
	
	
		//calculates 8Bit checksum with given polynomial x8+x5+x4+1
		for(byteCtr = 0; byteCtr < num; byteCtr++)
		{
				crc ^= (*(check_data+byteCtr));
				//CRCУ�飬���Ϊ��1��^0x31
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
			SGP30   ��ʼ��

*/
void  SGP30_Init(void)
{
		IIC_GPIO_Init();
		IIC_Start();							//���������ź�
		/* �����豸��ַ+��д����bit(0 = w, 1 = r)bit7 �ȴ�*/
		IIC_SendByte(SGP30_ADDR<<1);
		IIC_Wait_Ask();		//����豸��ACKӦ��
		IIC_SendByte(0x20);
		IIC_Wait_Ask();		//����豸��ACKӦ��
		IIC_SendByte(0x03);
		IIC_Wait_Ask();		//����豸��ACKӦ��	
		IIC_Stop();								//����ֹͣ�ź�		
		HAL_Delay(1000);
	
}






