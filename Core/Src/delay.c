#include "delay.h"

uint32_t CFG_VAL = 0;
void HAL_Delay_US(uint32_t Delay_us)
{
		__HAL_TIM_SetCounter(&htim2, 0);

		__HAL_TIM_ENABLE(&htim2);

		while(__HAL_TIM_GetCounter(&htim2) < Delay_us);
		/* Disable the Peripheral */
		__HAL_TIM_DISABLE(&htim2);
}
///*****************************************************************
//* ΢����ʱ��ʼ����ʱ����
//*
//* @ע�⣺��ʼ���������SystemClock_Config();֮�󣡣���
//*
//******************************************************************/
//void HAL_Delay_us_Init(void)
//{
//	CFG_VAL = (uint32_t)HAL_RCC_GetHCLKFreq()/1000/1000;
//}

//void delay_ms(uint16_t time)
//{    
//   uint16_t i=0;  
//   while(time--)
//   {
//      i=12000;  //�Լ�����
//      while(i--) ;    
//   }
//}
