#include "IIC.h"

void IIC_GPIO_Init( void )
{
		MX_GPIO_Init();
    //��ʼ��ICC��ģʽ
    SET_SDA;
    SET_SCL;  
}

/**
  * @brief  ����ģ��IICʱ�ļ���ʱ
  * @param  None
  * @retval None
  */
void IIC_Delay(void)
{
    u16 i;
	/*��
	 	�����ʱ����ͨ���߼������ǲ��Եõ��ġ�
    ����������CPU��Ƶ72MHz ��MDK���뻷����1���Ż�
  
		ѭ������Ϊ10ʱ��SCLƵ�� = 205KHz 
		ѭ������Ϊ7ʱ��SCLƵ�� = 347KHz�� SCL�ߵ�ƽʱ��1.5us��SCL�͵�ƽʱ��2.87us 
	 	ѭ������Ϊ5ʱ��SCLƵ�� = 421KHz�� SCL�ߵ�ƽʱ��1.25us��SCL�͵�ƽʱ��2.375us 
	*/
//	for (i = 0; i < 400; i++);
	HAL_Delay_US(2);
//	HAL_Delay(1);
}


/**
  * @brief  IIC����
  * @param  None
  * @retval None
  * @note   ��SCL���ڸߵ�ƽ״̬ʱ��SDA����һ���½���
            ������IIC�����ź�
  */
void IIC_Start(void)
{
    SET_SDA;
    IIC_DELAY;
    SET_SCL;
    IIC_DELAY;
    RESET_SDA;
    IIC_DELAY;
    RESET_SCL;
    IIC_DELAY;
}
/**
  * @brief  IICֹͣ
  * @param  None
  * @retval None
  * @note   ��SCL���ڸߵ�ƽ״̬ʱ��SDA����һ��������
            ������IICֹͣ�ź�
  */
void IIC_Stop(void)
{
    RESET_SDA;
    IIC_DELAY;

    SET_SCL;
    IIC_DELAY;

    SET_SDA;
    IIC_DELAY;
}


/**
  * @brief  IIC�ȴ�Ӧ���ź�
  * @param  None
  * @retval ack_status�� Ӧ��״̬��0��ʾӦ��1��ʾ�豸����Ӧ
  */
u8 IIC_Wait_Ask(void)
{
    int count=0;
    SET_SCL;
    IIC_DELAY;
    while(IIC_SDA_STATE)
    {
        count++;
        if(count>250)
        {
            IIC_Stop();
            return 1;
        }   
    }
    RESET_SCL;
    IIC_DELAY;
    return 0;
}



/**
  * @brief  ��������������������Ӧ���ź�
  * @param  None
  * @retval None
  */
void IIC_SendACK(void)
{
    RESET_SDA;
    IIC_DELAY;
    SET_SCL;
    IIC_DELAY;
    RESET_SCL; 
    IIC_DELAY; 
    SET_SDA;
    IIC_DELAY; 



}


/**
  * @brief  ����������������������Ӧ���ź�
  * @param  None
  * @retval None
  */
void IIC_SendNACK(void)  
{
    SET_SDA;
    IIC_DELAY;
    SET_SCL;
    IIC_DELAY;
    RESET_SCL; 
    IIC_DELAY;
}


/**
  * @brief  IIC����1byte����
  * @param  None
  * @retval None
  * @note   
  */
void IIC_SendByte(u8 Data)
{
    u8 i;
     RESET_SCL;
     for(i=0;i<8;i++)
     {  
        //���ݽ���
        if(Data&0x80)
        {
            SET_SDA;
        }
        else
        {
            RESET_SDA;
        } 
        IIC_DELAY;
        Data<<=1;
        IIC_DELAY;    //���ݽ�������һ����ʱ
        SET_SCL;      //����һ��������[������] 
        IIC_DELAY;
        RESET_SCL;
        IIC_DELAY;    //��ʱ,��ֹSCL��û��ɵ�ʱ�ı�SDA,�Ӷ�����START/STOP�ź�      }
			}   
}



/**
  * @brief  IIC��ȡ1byte����
  * @param  None
  * @retval None
  * @note             
  */
u8 IIC_RecvByte(void)
{
      u8 i,Dat = 0;
     SET_SDA;
     RESET_SCL; 
     Dat=0;
     for(i=0;i<8;i++)
     {
      
        SET_SCL;           //����ʱ��������[������],�ôӻ�׼�������� 
        IIC_DELAY; 
        Dat<<=1;    
        if(IIC_SDA_STATE)  //������״̬
        {
            Dat|=0x01; 
        }   
        RESET_SCL;         //׼�����ٴν�������  
        IIC_DELAY;         //�ȴ�����׼����         
     }
     return Dat;
}

/* ���ֽ�д�� -------------------------------------------------------- */
void Single_Write_IIC(u8 SlaveAddress,u8 REG_Address,u8 REG_data)
{
    IIC_Start();                  //��ʼ�ź�
    IIC_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�
    IIC_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ�� 
    IIC_SendByte(REG_data);       //�ڲ��Ĵ������ݣ� 
    IIC_Stop();                   //����ֹͣ�ź�
}

/* ���ֽڶ�ȡ --------------------------------------------------------- */
u8 Single_Read_IIC(u8 SlaveAddress, u8 REG_Address)
{  
    u8 REG_data;
    IIC_Start();                          //��ʼ�ź�
    IIC_SendByte(SlaveAddress);           //�����豸��ַ+д�ź�
    IIC_SendByte(REG_Address);            //���ʹ洢��Ԫ��ַ��//��0��ʼ 
    IIC_Start();                          //��ʼ�ź�
    IIC_SendByte(SlaveAddress+1);         //�����豸��ַ+���ź�
    REG_data = IIC_RecvByte();            //�����Ĵ�������
    IIC_SendACK();   
    IIC_Stop();                           //ֹͣ�ź�
    return REG_data; 
}



///*******************************************************************************
//* �� �� ��         : IIC_Read_Byte
//* ��������		   : IIC��һ���ֽ� 
//* ��    ��         : ack=1ʱ������ACK��ack=0������nACK 
//* ��    ��         : Ӧ����Ӧ��
//*******************************************************************************/  
u8 IIC_Recv_Byte(u8 ack)
{
      u8 i,Dat = 0;
     SET_SDA;
     RESET_SCL; 
     Dat=0;
     for(i=0;i<8;i++)
     {
      
        SET_SCL;           //����ʱ��������[������],�ôӻ�׼�������� 
        IIC_DELAY; 
        Dat<<=1;    
        if(IIC_SDA_STATE)  //������״̬
        {
            Dat|=0x01; 
        }   
        RESET_SCL;         //׼�����ٴν�������  
        IIC_DELAY;         //�ȴ�����׼����         
     }
		     if (!ack)
        IIC_SendNACK();//����nACK
    else
        IIC_SendACK(); //����ACK   
     return Dat;
}

