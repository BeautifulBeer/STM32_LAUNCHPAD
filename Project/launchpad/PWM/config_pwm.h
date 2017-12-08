/*
 * config_pwm.h
 *
 *  Created on: 2017. 12. 5.
 *      Author: hw_3
 */

#ifndef CONFIG_PWM_H_
#define CONFIG_PWM_H_


#include <stm32f10x_tim.h>
#include <stm32f10x_gpio.h>

#define SYS_CLK					 	40000000
//#define TIMER_FREQ 					10000000 //0.1us
#define TIMER_FREQ 					40000000
#define PWM_FREQ 					833333  //1.2us
//#define PRESCALAR 					(SYS_CLK / TIMER_FREQ - 1)
#define PRESCALAR 					0
//#define PRESCALAR 					47
//#define PERIOD						(TIMER_FREQ / PWM_FREQ - 1)
#define PERIOD						47
//#define PERIOD						11
//#define _DUTY_CYCLE(cycle)			(((PERIOD + 1) * cycle) / 100 -1)
//#define PUL_DUTY0					_DUTY_CYCLE(0)
#define PUL_DUTY0
//#define PUL_DUTY25					_DUTY_CYCLE(25) // NeoPixel LED 0
#define PUL_DUTY25					11
//#define PUL_DUTY50					_DUTY_CYCLE(50) // NeoPixel LED 1
#define PUL_DUTY50					23


//Initialize TIM_Timebase
void m_Init_PWM_TIM(TIM_TypeDef* TIMx);
//Initialize GPIOE configuration for USART2
void m_Init_TIM4_CH3_GPIOB(void);
void m_Init_TIM2(void);
void m_Init_TIM4(void);


#endif /* CONFIG_PWM_H_ */
