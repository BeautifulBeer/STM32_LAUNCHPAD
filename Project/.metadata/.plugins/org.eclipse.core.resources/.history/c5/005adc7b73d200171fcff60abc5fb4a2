/*
 * config_interrupt.c
 *
 *  Created on: 2017. 11. 24.
 *      Author: hw_3
 */

#include "config_nvic.h"

void m_Init_USART2_NVIC(){
	NVIC_InitTypeDef nvic_init_;
	nvic_init_.NVIC_IRQChannel = USART2_IRQn;
	nvic_init_.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_init_.NVIC_IRQChannelSubPriority = 0;
	nvic_init_.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_init_);
}

void m_Init_USART3_NVIC(){
	NVIC_InitTypeDef nvic_init_;
	nvic_init_.NVIC_IRQChannel = USART3_IRQn;
	nvic_init_.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_init_.NVIC_IRQChannelSubPriority = 0;
	nvic_init_.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_init_);
}
