#include "pulse.h"
#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal_tim.h"
TIM_HandleTypeDef TIM2_Handler;
//uint8_t b=1,c=1;
	long long  temp=0;
	uint16_t pulsecount;
void SystemClock_Config(void);
/***************TIM2_CH2_CAPTURE_INIT******************/
void TIM2_CH2_CAP_Init(uint32_t arr,uint16_t psc)
{
	TIM_IC_InitTypeDef TIM2_CH2Config ; 
	TIM2_Handler.Instance = TIM2;
	TIM2_Handler.Init.Prescaler = psc; 
	TIM2_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;
	TIM2_Handler.Init.Period = arr;
	TIM2_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; 
	HAL_TIM_IC_Init(&TIM2_Handler); 

	TIM2_CH2Config.ICPolarity=TIM_ICPOLARITY_RISING;
	TIM2_CH2Config.ICSelection=TIM_ICSELECTION_DIRECTTI; 
	TIM2_CH2Config.ICPrescaler=TIM_ICPSC_DIV1;
	TIM2_CH2Config.ICFilter=0;
	HAL_TIM_IC_ConfigChannel(&TIM2_Handler,&TIM2_CH2Config,TIM_CHANNEL_3);

}

 uint8_t TIM2CH2_CAPTURE_STA = 0;
 uint32_t TIM2CH2_CAPTURE_VAL;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
//	b++;
	if((TIM2CH2_CAPTURE_STA & 0X80)==0)
	{
		if(TIM2CH2_CAPTURE_STA & 0X40 )
		{
			if((TIM2CH2_CAPTURE_STA & 0X3F)==0X3F)
			{
				TIM2CH2_CAPTURE_STA |=0X80;
				TIM2CH2_CAPTURE_VAL =0XFFFFFFFF;
			} else TIM2CH2_CAPTURE_STA++ ;
		}
	}
}
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
//	c++;
	if((TIM2CH2_CAPTURE_STA & 0X80)==0)
	{
		if(TIM2CH2_CAPTURE_STA & 0X40 )
		{
			TIM2CH2_CAPTURE_STA |= 0X80;
			TIM2CH2_CAPTURE_VAL = HAL_TIM_ReadCapturedValue(&TIM2_Handler,TIM_CHANNEL_3);
			
		}else
		{
			TIM2CH2_CAPTURE_STA = 0;
			TIM2CH2_CAPTURE_VAL = 0;
			TIM2CH2_CAPTURE_STA |= 0X40;
			__HAL_TIM_DISABLE(&TIM2_Handler);
			__HAL_TIM_SET_COUNTER(&TIM2_Handler,0);
		  __HAL_TIM_ENABLE(&TIM2_Handler);
		}
	}
}
/***********************************************/

uint16_t pulse(void)
{



	  HAL_TIM_IC_Start_IT(&TIM2_Handler, TIM_CHANNEL_3);
    __HAL_TIM_ENABLE_IT(&TIM2_Handler,TIM_IT_UPDATE);


		TIM2CH2_CAPTURE_STA=0;

	  HAL_Delay(100);	
		if(TIM2CH2_CAPTURE_STA & 0X80)
		{
	    temp=TIM2CH2_CAPTURE_STA & 0X3F;
	    temp *=0xffffffff;
			temp +=TIM2CH2_CAPTURE_VAL;
			pulsecount = 100000/temp;
		}
		else
		{
			pulsecount = 0;
		}
		__HAL_TIM_DISABLE(&TIM2_Handler);
		return pulsecount;

//	 HAL_Delay(100);	
//		if(TIM2CH2_CAPTURE_STA & 0X80)
//		{
//	    temp=TIM2CH2_CAPTURE_STA & 0X3F;
//	    temp *=0xffffffff;
//			temp +=TIM2CH2_CAPTURE_VAL;
//			pulsecount = 100000/temp;
//			HAL_Delay(100);
//	//		printf("HIGNTIME:%lld us\r\n",temp);
//			TIM2CH2_CAPTURE_STA=0;
//			
//		}
//		else
//		{
//			pulsecount = 0;
//		}
//		__HAL_TIM_DISABLE(&TIM2_Handler);
//		return pulsecount;
}
/*****************************************/

