/*
 * config_pwm.c
 *
 *  Created on: 2017. 12. 5.
 *      Author: hw_3
 */

#include "config_pwm.h"

//100%, 75% 50% 25%
void m_Init_PWM_TIM(TIM_TypeDef* TIMx, uint8_t ch1_enable, uint8_t ch2_enable,
		uint8_t ch3_enable, uint8_t ch4_enable){
	TIM_OCInitTypeDef time_oc_;
	//CH1: Duty100
	if(ch1_enable){
		time_oc_.TIM_OCMode = TIM_OCMode_PWM1;
		time_oc_.TIM_OutputState = TIM_OutputState_Enable;
		time_oc_.TIM_OCPolarity = TIM_OCPolarity_High;
		time_oc_.TIM_Pulse = 47;
		TIM_OC1Init(TIMx, &time_oc_);
		TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
	}
	//CH2: Duty75
	if(ch2_enable){
		time_oc_.TIM_OutputState = TIM_OutputState_Enable;
		time_oc_.TIM_Pulse = 23;
		TIM_OC2Init(TIMx, &time_oc_);
		TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);
	}
	//CH3: Duty50
	if(ch3_enable){
		time_oc_.TIM_OutputState = TIM_OutputState_Enable;
		time_oc_.TIM_Pulse = 23;
		TIM_OC3Init(TIMx, &time_oc_);
		TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);
	}
	//CH4: Duty25
	if(ch3_enable){
		time_oc_.TIM_OutputState = TIM_OutputState_Enable;
		time_oc_.TIM_Pulse = 11;
		TIM_OC4Init(TIMx, &time_oc_);
		TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);
	}
}

void m_Init_PWM_GPIO(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pinx, uint8_t flag){
	GPIO_InitTypeDef gpio_init_;
	gpio_init_.GPIO_Pin = GPIO_Pinx;
	if(flag){
		gpio_init_.GPIO_Mode = GPIO_Mode_AF_PP;
	}else{
		gpio_init_.GPIO_Mode = GPIO_Mode_Out_PP;
	}
	gpio_init_.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx, &gpio_init_);
}

void m_Init_TIM(TIM_TypeDef* TIMx, int Period, int Prescalar){
	TIM_TimeBaseInitTypeDef time_;
	//time_.TIM_Period = Period;
	time_.TIM_Period = 47;
	//time_.TIM_Prescaler = Prescalar;
	time_.TIM_Prescaler = 0;
	time_.TIM_ClockDivision = TIM_CKD_DIV1;
	time_.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIMx, &time_);
	TIM_ARRPreloadConfig(TIMx, ENABLE);
	TIM_ITConfig(TIMx, TIM_IT_CC2, ENABLE);
	TIM_Cmd(TIMx, ENABLE);
}

void m_send_BIT(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint8_t bit){
	uint16_t cc;
	if(bit == 1){
		cc = BIT_1;
	}else if(bit == 0){
		cc = BIT_0;
	}else if(bit == 2){
		cc = RESET;
	}
	if(TIM_Channel == TIM_Channel_1){
		TIM_SetCompare1(TIMx, cc);
	}else if(TIM_Channel == TIM_Channel_2){
		TIM_SetCompare2(TIMx, cc);
	}else if(TIM_Channel == TIM_Channel_3){
		TIM_SetCompare3(TIMx, cc);
	}else if(TIM_Channel == TIM_Channel_4){
		TIM_SetCompare4(TIMx, cc);
	}
}
