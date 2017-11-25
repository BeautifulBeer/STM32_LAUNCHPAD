/*
 * config_bluetooth.c
 *
 *  Created on: 2017. 11. 24.
 *      Author: hw_3
 */

#include "config_bluetooth.h"

void m_Init_BT_USART3(){
	m_Init_BT_USART(USART3);
	USART_Cmd(USART3, ENABLE);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
}

void m_Init_BT_USART2(){
	m_Init_BT_USART(USART2);
	USART_Cmd(USART2, ENABLE);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
}

void m_Init_BT_USART(USART_TypeDef* USARTx){
	USART_InitTypeDef usart_init_;
	//bps = baud rate * wordlength -- 9600bps under the configuration
	usart_init_.USART_BaudRate = 9600;
	usart_init_.USART_WordLength = USART_WordLength_8b;
	usart_init_.USART_StopBits = USART_StopBits_1;
	usart_init_.USART_Parity = USART_Parity_No;
	usart_init_.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart_init_.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USARTx, &usart_init_);
}

void m_Init_BT_USART3_GPIOC(){
	GPIO_InitTypeDef gpio_init_;
	//Tx configuration
	gpio_init_.GPIO_Pin = GPIO_Pin_10;
	gpio_init_.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_init_.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &gpio_init_);
	//Rx configuration
	gpio_init_.GPIO_Pin = GPIO_Pin_11;
	gpio_init_.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio_init_.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &gpio_init_);
}

void m_Init_BT_USART2_GPIOA(){
	GPIO_InitTypeDef gpio_init_;
	//Tx configuration
	gpio_init_.GPIO_Pin = GPIO_Pin_2;
	gpio_init_.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_init_.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_init_);
	//Rx configuration
	gpio_init_.GPIO_Pin = GPIO_Pin_3;
	gpio_init_.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio_init_.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_init_);
}


void m_Init_BT_USART2_EXIT(){
	EXTI_InitTypeDef exti_init_;
	//EXTI line configuration
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource3);
	//Rx Interrupt
	exti_init_.EXTI_Line = EXTI_Line3;
	exti_init_.EXTI_LineCmd = ENABLE;
	exti_init_.EXTI_Mode = EXTI_Mode_Interrupt;
	exti_init_.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_Init(&exti_init_);
}

void m_Init_BT_USART3_EXIT(){
	EXTI_InitTypeDef exti_init_;
	//EXTI line configuration
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource11);
	//Rx Interrupt
	exti_init_.EXTI_Line = EXTI_Line11;
	exti_init_.EXTI_LineCmd = ENABLE;
	exti_init_.EXTI_Mode = EXTI_Mode_Interrupt;
	exti_init_.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_Init(&exti_init_);
}

void USART2_IRQHandler(void){
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
		//Implementation
	}
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
}

void USART3_IRQHandler(void){
	if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) {
		//Implementation
	}
	USART_ClearITPendingBit(USART3, USART_IT_RXNE);
}