/*
 * config_pwm.c
 *
 *  Created on: 2017. 12. 5.
 *      Author: hw_3
 */

#include "config_pwm.h"

void m_Init_TIM(TIM_TypeDef* TIMx){
	TIM_TimeBaseInitTypeDef time_;
	time_.TIM_Period = 0;
	time_.TIM_Prescaler = 19;
	time_.TIM_ClockDivision = TIM_CKD_DIV1;
	time_.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIMx, &time_);
}

void m_Init_PWM(TIM_TypeDef* TIMx){
	TIM_OCInitTypeDef tim_oc_;

}
