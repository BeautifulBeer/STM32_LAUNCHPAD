/*
 * config_interrupt.c
 *
 *  Created on: 2017. 11. 24.
 *      Author: hw_3
 */

#include "config_nvic.h"

void m_Init_USART2_NVIC(void){
	NVIC_InitTypeDef nvic_init_;
	nvic_init_.NVIC_IRQChannel = USART2_IRQn;
	nvic_init_.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_init_.NVIC_IRQChannelSubPriority = 0;
	nvic_init_.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_init_);
}

void m_Init_USART1_NVIC(void){
	NVIC_InitTypeDef nvic_init_;
	nvic_init_.NVIC_IRQChannel = USART1_IRQn;
	nvic_init_.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_init_.NVIC_IRQChannelSubPriority = 0;
	nvic_init_.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_init_);
}

void m_Init_MPR121_NVIC(void) {
  NVIC_InitTypeDef nvic_init_;
  nvic_init_.NVIC_IRQChannel = I2C1_ER_IRQn;
  nvic_init_.NVIC_IRQChannelPreemptionPriority = 0;
  nvic_init_.NVIC_IRQChannelSubPriority = 1;
  nvic_init_.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&nvic_init_);
}
