/*
 * config_pwm.h
 *
 *  Created on: 2017. 12. 5.
 *      Author: hw_3
 */

#ifndef CONFIG_PWM_H_
#define CONFIG_PWM_H_


#include <stm32f10x_tim.h>

/*
 * SK6812 PWM
 * Input Code 0 : T0H(0.3u) + T0L(0.9u)
 * Input Code 1 : T1H(0.6u) + T1L(0.6u)
 * Reset Code : Treset(80u)
 * ARR = 4
 * 0 - CRRx = 1 (Value)
 * 1 - CRRx = 2 (Value)
 */


//Initialize TIM_Timebase
void m_Init_TIM2();
//For PWM
void m_Init_PWM(TIM_TypeDef* TIMx);


#endif /* CONFIG_PWM_H_ */
