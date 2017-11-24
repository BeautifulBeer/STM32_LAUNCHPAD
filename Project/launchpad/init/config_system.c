/*
 * config_system.c
 *
 *  Created on: 2017. 11. 24.
 *      Author: hw_3
 */

#include "config_system.h"

void m_Init_GPIOA_Clock(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
}

void m_Init_GPIOC_Clock(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
}

void m_Init_USART2_Clock(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
}

void m_Init_USART3_Clock(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
}

