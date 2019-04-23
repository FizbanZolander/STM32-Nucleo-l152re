/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32l1xx.h"

void delay(int time)
{
	int i;
	for(i=0; i<time*4000 ;i++){}
}
void send_char(char c)
{
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	USART_SendData(USART2, c);
}

void wiadomosc(const char* s)
{
	 while(*s)
	 send_char(*s++);
}



int main(void)
{
	GPIO_InitTypeDef gpio; //obiekt do konfiguracji pinow do usartu
	GPIO_InitTypeDef dioda; // do konfiguracji diody wbudowanej
	USART_InitTypeDef usart; // konfiguracja usartu

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);


	gpio.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_Speed = GPIO_Speed_40MHz;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &gpio);

	dioda.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	dioda.GPIO_Mode = GPIO_Mode_OUT;
	dioda.GPIO_Speed = GPIO_Speed_40MHz;
	dioda.GPIO_OType = GPIO_OType_PP;
	dioda.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &dioda);

	dioda.GPIO_Pin = GPIO_Pin_0;
	dioda.GPIO_Mode = GPIO_Mode_OUT;
	dioda.GPIO_Speed = GPIO_Speed_40MHz;
	dioda.GPIO_OType = GPIO_OType_PP;
	dioda.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &dioda);

	dioda.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_10;
	dioda.GPIO_Mode = GPIO_Mode_IN;
	dioda.GPIO_Speed = GPIO_Speed_40MHz;
	dioda.GPIO_OType = GPIO_OType_PP;
	dioda.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &dioda);


	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

	usart.USART_BaudRate = 9600;
	usart.USART_WordLength = USART_WordLength_8b;
	usart.USART_StopBits = USART_StopBits_1;
	usart.USART_Parity = USART_Parity_No;
	usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &usart);

	USART_Cmd(USART2, ENABLE);

	GPIO_SetBits(GPIOA, GPIO_Pin_6);
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
	while(1)
	{
		if(USART_GetFlagStatus(USART2, USART_FLAG_RXNE))
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_6);

			/*char w = USART_ReceiveData(USART2);
			switch(w)
			{
			case '1':
				GPIO_ResetBits(GPIOA, GPIO_Pin_6);
				GPIO_ResetBits(GPIOA, GPIO_Pin_7);
				wiadomosc("czerwona zielona\r\n");
				break;
			case '2':
				GPIO_ResetBits(GPIOA, GPIO_Pin_6);
				GPIO_ResetBits(GPIOA, GPIO_Pin_7);
				GPIO_ResetBits(GPIOB, GPIO_Pin_0);
				wiadomosc("zielona niebieska\r\n");
				break;
			case '3':
				GPIO_ResetBits(GPIOA, GPIO_Pin_7);
				GPIO_SetBits(GPIOA, GPIO_Pin_6);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				wiadomosc("zielona\r\n");
				break;
			case '4':
				GPIO_ResetBits(GPIOA, GPIO_Pin_6);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				GPIO_SetBits(GPIOA, GPIO_Pin_7);
				wiadomosc("czerwona\r\n");
				break;
			case '5':
				GPIO_ResetBits(GPIOB, GPIO_Pin_0);
				GPIO_SetBits(GPIOA, GPIO_Pin_6);
				GPIO_SetBits(GPIOA, GPIO_Pin_7);
				wiadomosc("niebieska\r\n");
				break;
			case '6':
				GPIO_ResetBits(GPIOB, GPIO_Pin_0);
				GPIO_ResetBits(GPIOA, GPIO_Pin_6);
				GPIO_SetBits(GPIOA, GPIO_Pin_7);
				wiadomosc("czerwona niebieska \r\n");
			case '7':
				GPIO_ResetBits(GPIOB, GPIO_Pin_0);
				GPIO_ResetBits(GPIOA, GPIO_Pin_6);
				GPIO_ResetBits(GPIOA, GPIO_Pin_7);
				wiadomosc("wszystkie \r\n");
				break;
			default:
				GPIO_SetBits(GPIOA, GPIO_Pin_6);
				GPIO_SetBits(GPIOA, GPIO_Pin_7);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				wiadomosc("Zostal wyslany bledny znak\r\n");
				break; */


			}
		}
	}
}
