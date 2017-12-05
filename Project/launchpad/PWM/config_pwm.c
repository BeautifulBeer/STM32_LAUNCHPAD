/*
 * config_pwm.c
 *
 *  Created on: 2017. 12. 5.
 *      Author: hw_3
 */

#include "config_pwm.h"

void m_Init_PWM_TIM(TIM_TypeDef* TIMx){
	TIM_TimeBaseInitTypeDef time_;
	TIM_OCInitTypeDef time_oc_;
	TIM_DeInit(TIMx);

	time_.TIM_Period = PERIOD;
	time_.TIM_Prescaler = PRESCALAR;
	time_.TIM_ClockDivision = TIM_CKD_DIV1;
	time_.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIMx, &time_);
	TIM_ITConfig(TIM4, TIM_IT_CC3, ENABLE);

	TIM_CCPreloadControl(TIMx, ENABLE);

	//Channel3: Duty25
	time_oc_.TIM_OCMode = TIM_OCMode_PWM1;
	time_oc_.TIM_OutputState = TIM_OutputState_Enable;
	time_oc_.TIM_OCPolarity = TIM_OCPolarity_High;
	time_oc_.TIM_Pulse = 12;

	TIM_OC3Init(TIMx, &time_oc_);
	TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);
	TIM_CtrlPWMOutputs(TIMx, ENABLE);
	TIM_ARRPreloadConfig(TIMx, ENABLE);
	TIM_SelectOCxM(TIMx, TIM_Channel_3, TIM_OCMode_PWM1);
	TIM_CCxCmd(TIMx, TIM_Channel_3, ENABLE);
	TIM_Cmd(TIMx, ENABLE);

}

void m_Init_TIM4_CH3_GPIOB(void){
	GPIO_InitTypeDef gpio_init_;
	gpio_init_.GPIO_Pin = GPIO_Pin_8;
	gpio_init_.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_init_.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpio_init_);
}

void m_Init_TIM2(void){
	TIM_TimeBaseInitTypeDef time_;
	time_.TIM_Period = 2000;
	time_.TIM_Prescaler = 10000;
	time_.TIM_ClockDivision = TIM_CKD_DIV1;
	time_.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &time_);
	TIM_Cmd(TIM2, ENABLE);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
}

void m_Init_TIM4(void){
	TIM_TimeBaseInitTypeDef time_;
	time_.TIM_Period = 2000;
	time_.TIM_Prescaler = 10000;
	time_.TIM_ClockDivision = TIM_CKD_DIV1;
	time_.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &time_);
	TIM_Cmd(TIM4, ENABLE);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
}
