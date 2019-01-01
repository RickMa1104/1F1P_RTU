#ifndef  _pulse_h
#define  _pulse_h
#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal_tim.h"
uint16_t pulse(void); 

void TIM2_CH2_CAP_Init(uint32_t arr,uint16_t psc);
#endif
