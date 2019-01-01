#include"apc240.h"
typedef uint8_t u8;
extern UART_HandleTypeDef hlpuart1;
char tab[]={0x7f,0x3f,0x1f,0xf,0x7,0x3,0x1,0x0};
RTU rtu;
void Apc240ModeSet(Apc240Mode Mode)
{
    switch (Mode)
            {
									case Apc240Mode1 :HAL_GPIO_WritePin(SETA_GPIO_Port, SETA_Pin, GPIO_PIN_RESET);
																		HAL_GPIO_WritePin(SETB_GPIO_Port, SETB_Pin, GPIO_PIN_RESET);
																		break;
									case Apc240Mode2 :HAL_GPIO_WritePin(SETA_GPIO_Port, SETA_Pin, GPIO_PIN_RESET);
																		HAL_GPIO_WritePin(SETB_GPIO_Port, SETB_Pin, GPIO_PIN_SET);
																		break;
									case Apc240Mode3 :HAL_GPIO_WritePin(SETA_GPIO_Port, SETA_Pin, GPIO_PIN_SET);
																		HAL_GPIO_WritePin(SETB_GPIO_Port, SETB_Pin, GPIO_PIN_RESET);
																		break;
									case Apc240Mode4 :HAL_GPIO_WritePin(SETA_GPIO_Port, SETA_Pin, GPIO_PIN_SET);
																		HAL_GPIO_WritePin(SETB_GPIO_Port, SETB_Pin, GPIO_PIN_SET);
																		break;
            }
}

void Apc240Send(u8 *data,int lenght)
{ 
   HAL_UART_Transmit(&hlpuart1, data ,lenght, 0x01 );
}

void Apc240SendComplete()
{
//		while(HAL_GPIO_ReadPin(AUX_GPIO_Port, AUX_Pin) == GPIO_PIN_RESET)
//		{
//		
//		}
}

void Apc240SendWait(uint8_t * sendData, uint8_t sendLength)
{
		Apc240ModeSet(Apc240Mode1);
		HAL_Delay(5);
		Apc240Send(sendData, sendLength);
		Apc240SendComplete();
}
void UartInit(int baudrate)
{
	hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = baudrate;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONEBIT_SAMPLING_DISABLED;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  HAL_UART_Init(&hlpuart1);
}




