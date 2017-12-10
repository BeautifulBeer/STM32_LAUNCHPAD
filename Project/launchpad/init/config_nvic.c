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

void m_Init_I2C_NVIC(I2C_TypeDef* I2Cx, uint8_t flag){
  NVIC_InitTypeDef nvic_init_;
  if(I2Cx == I2C1){
	  if(flag){
		  nvic_init_.NVIC_IRQChannel = I2C1_EV_IRQn;
	  }else{
		  nvic_init_.NVIC_IRQChannel = I2C1_ER_IRQn;
	  }
  }else if(I2Cx == I2C2){
	  if(flag){
		  nvic_init_.NVIC_IRQChannel = I2C2_EV_IRQn;
	  }else{
		  nvic_init_.NVIC_IRQChannel = I2C2_ER_IRQn;
	  }
  }
  nvic_init_.NVIC_IRQChannelPreemptionPriority = 0;
  nvic_init_.NVIC_IRQChannelSubPriority = 1;
  nvic_init_.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&nvic_init_);
}

void m_Init_TIM_NVIC(TIM_TypeDef* TIMx, uint32_t Priority){
	NVIC_InitTypeDef nvic_init_;
	if(TIMx == TIM1){
		//Default Update Interrupt
		nvic_init_.NVIC_IRQChannel = TIM1_UP_IRQn;
	}else if(TIMx == TIM2){
		nvic_init_.NVIC_IRQChannel = TIM2_IRQn;
	}else if(TIMx == TIM3){
		nvic_init_.NVIC_IRQChannel = TIM3_IRQn;
	}else if(TIMx == TIM4){
		nvic_init_.NVIC_IRQChannel = TIM4_IRQn;
	}else if(TIMx == TIM5){
		nvic_init_.NVIC_IRQChannel = TIM5_IRQn;
	}
	nvic_init_.NVIC_IRQChannelPreemptionPriority = Priority;
	nvic_init_.NVIC_IRQChannelSubPriority = 0;
	nvic_init_.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_init_);
}
