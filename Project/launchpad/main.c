/*
 * main.c
 *
 *  Created on: 2017. 11. 24.
 *      Author: hw_3
 */
#include "bluetooth/config_bluetooth.h"
#include "init/config_system.h"
#include "init/config_nvic.h"
#include <lcd.h>
#include <touch.h>
#include "core_cm3.h"

void USART2_IRQHandler(void){
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
		uint16_t data = USART_ReceiveData(USART2);
		m_USART_byteSend(USART1, data);
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	}
}

void USART1_IRQHandler(void){
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
		uint16_t data = USART_ReceiveData(USART1);
		//m_USART_DataSend(USART1, data);
		m_USART_byteSend(USART2, data);
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}


void Configure_LED() {
   GPIO_InitTypeDef GPIO_init;

   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

   GPIO_init.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_init.GPIO_Pin = (GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_7);
   GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;

   GPIO_Init(GPIOD, &GPIO_init);
}


int main(){
	char buffer_[BT_STR_MAX_LENGTH];
	//System Configuration Initialization
	m_System_Clock();

	//GPIOx
	m_Init_GPIOA_Clock();

	//USARTx
	m_Init_USART2_Clock();
	m_Init_USART1_Clock();

	//Interrupt Configuration - EXTI
	m_Init_BT_USART2_EXIT();
	m_Init_BT_USART1_EXIT();

	//Initialize USART1/2 GPIOA
	m_Init_BT_USART1_GPIOA();
	m_Init_BT_USART2_GPIOA();

	//Initialize USART1/2
	m_Init_BT_USART1();
	m_Init_BT_USART2();

	//Interrupt Configuration - NVIC
	m_Init_USART2_NVIC();
	m_Init_USART1_NVIC();
	m_USART_DataSend(USART2, "AT+BTSCAN", buffer_);

	Configure_LED();


	GPIOD->BSRR = GPIO_BSRR_BS2;
	GPIOD->BSRR = GPIO_BSRR_BS3;
	GPIOD->BSRR = GPIO_BSRR_BS4;
	GPIOD->BSRR = GPIO_BSRR_BS7;


	//Main Loop
	while(1){

	}
}
