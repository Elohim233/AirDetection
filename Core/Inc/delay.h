#ifndef __DELAY__H
#define __DELAY__H

#include "main.h"
#include "tim.h"

#define MAX_Delay_CNT 1000
void HAL_Delay_us_Init();
void HAL_Delay_US(__IO uint32_t Delay);
void delay_ms(uint16_t time);
//#define CPU_FREQUENCY_MHZ    2		// STM32Ê±ÖÓÖ÷Æµ
//void HAL_Delay_US(__IO uint32_t delay);

#endif


