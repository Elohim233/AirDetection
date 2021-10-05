#include "IIC.h"

void IIC_GPIO_Init( void )
{
		MX_GPIO_Init();
    //初始化ICC的模式
    SET_SDA;
    SET_SCL;  
}

/**
  * @brief  用于模拟IIC时的简单延时
  * @param  None
  * @retval None
  */
void IIC_Delay(void)
{
    u16 i;
	/*　
	 	下面的时间是通过逻辑分析仪测试得到的。
    工作条件：CPU主频72MHz ，MDK编译环境，1级优化
  
		循环次数为10时，SCL频率 = 205KHz 
		循环次数为7时，SCL频率 = 347KHz， SCL高电平时间1.5us，SCL低电平时间2.87us 
	 	循环次数为5时，SCL频率 = 421KHz， SCL高电平时间1.25us，SCL低电平时间2.375us 
	*/
//	for (i = 0; i < 400; i++);
	HAL_Delay_US(2);
//	HAL_Delay(1);
}


/**
  * @brief  IIC启动
  * @param  None
  * @retval None
  * @note   当SCL处于高电平状态时，SDA出现一个下降沿
            即产生IIC启动信号
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
  * @brief  IIC停止
  * @param  None
  * @retval None
  * @note   当SCL处于高电平状态时，SDA出现一个上升沿
            即产生IIC停止信号
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
  * @brief  IIC等待应答信号
  * @param  None
  * @retval ack_status： 应答状态，0表示应答，1表示设备无响应
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
  * @brief  主机（主控制器）产生应答信号
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
  * @brief  主机（主控制器）产生不应答信号
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
  * @brief  IIC发送1byte数据
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
        //数据建立
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
        IIC_DELAY;    //数据建立保持一定延时
        SET_SCL;      //产生一个上升沿[正脉冲] 
        IIC_DELAY;
        RESET_SCL;
        IIC_DELAY;    //延时,防止SCL还没变成低时改变SDA,从而产生START/STOP信号      }
			}   
}



/**
  * @brief  IIC读取1byte数据
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
      
        SET_SCL;           //产生时钟上升沿[正脉冲],让从机准备好数据 
        IIC_DELAY; 
        Dat<<=1;    
        if(IIC_SDA_STATE)  //读引脚状态
        {
            Dat|=0x01; 
        }   
        RESET_SCL;         //准备好再次接收数据  
        IIC_DELAY;         //等待数据准备好         
     }
     return Dat;
}

/* 单字节写入 -------------------------------------------------------- */
void Single_Write_IIC(u8 SlaveAddress,u8 REG_Address,u8 REG_data)
{
    IIC_Start();                  //起始信号
    IIC_SendByte(SlaveAddress);   //发送设备地址+写信号
    IIC_SendByte(REG_Address);    //内部寄存器地址， 
    IIC_SendByte(REG_data);       //内部寄存器数据， 
    IIC_Stop();                   //发送停止信号
}

/* 单字节读取 --------------------------------------------------------- */
u8 Single_Read_IIC(u8 SlaveAddress, u8 REG_Address)
{  
    u8 REG_data;
    IIC_Start();                          //起始信号
    IIC_SendByte(SlaveAddress);           //发送设备地址+写信号
    IIC_SendByte(REG_Address);            //发送存储单元地址，//从0开始 
    IIC_Start();                          //起始信号
    IIC_SendByte(SlaveAddress+1);         //发送设备地址+读信号
    REG_data = IIC_RecvByte();            //读出寄存器数据
    IIC_SendACK();   
    IIC_Stop();                           //停止信号
    return REG_data; 
}



///*******************************************************************************
//* 函 数 名         : IIC_Read_Byte
//* 函数功能		   : IIC读一个字节 
//* 输    入         : ack=1时，发送ACK，ack=0，发送nACK 
//* 输    出         : 应答或非应答
//*******************************************************************************/  
u8 IIC_Recv_Byte(u8 ack)
{
      u8 i,Dat = 0;
     SET_SDA;
     RESET_SCL; 
     Dat=0;
     for(i=0;i<8;i++)
     {
      
        SET_SCL;           //产生时钟上升沿[正脉冲],让从机准备好数据 
        IIC_DELAY; 
        Dat<<=1;    
        if(IIC_SDA_STATE)  //读引脚状态
        {
            Dat|=0x01; 
        }   
        RESET_SCL;         //准备好再次接收数据  
        IIC_DELAY;         //等待数据准备好         
     }
		     if (!ack)
        IIC_SendNACK();//发送nACK
    else
        IIC_SendACK(); //发送ACK   
     return Dat;
}



