/*
 * config_pwm.h
 *
 *  Created on: 2017. 12. 5.
 *      Author: hw_3
 */

#ifndef CONFIG_PWM_H_
#define CONFIG_PWM_H_

#include <stdint.h>
#include "../MPR121/Adafruit_MPR121.h"
#include <stm32f10x_tim.h>
#include <stm32f10x_gpio.h>

#define SYS_CLK					 	(volatile)40000000
#define TIMER_CLK					(volatile)(SYS_CLK / 1)
#define PWM_FREQ 					(volatile)833333  //1.2us
//#define PRESCALAR 					(SYS_CLK / TIMER_FREQ - 1)
#define PRESCALAR 					(volatile)0
#define PERIOD						(volatile)47//((TIMER_CLK / PWM_FREQ - 1))

#define DUTY_0						(volatile)0//(PERIOD * (25 / 100))
#define DUTY_25						(volatile)11//(PERIOD * (25 / 100))
#define DUTY_50						(volatile)23//(PERIOD * (50 / 100))
#define DUTY_75						(volatile)35//(PERIOD * (75 / 100))
#define DUTY_100					(volatile)47//PERIOD
#define BIT_1						DUTY_50
#define BIT_0						DUTY_25
#define RESET						DUTY_0

#define CONST_PATTERN_NUM 			8
#define CONST_PIXEL_NUM 			8
#define CONST_RGB_NUM				3
#define CONST_RESET_PERIOD			67 // 80us / 1.2us
#define LED_TIM_PERIOD				500
#define LED_TIM_PESCALAR			20000



void m_Init_PWM_TIM(TIM_TypeDef* TIMx, uint8_t ch1_enable, uint8_t ch2_enable,
		uint8_t ch3_enable, uint8_t ch4_enable);
//flag : 0 - Output Mode , flag : 1 - Alternative Output Mode
void m_Init_PWM_GPIO(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pinx, uint8_t flag);
void m_Init_TIM(TIM_TypeDef* TIMx, int Period, int Prescalar);
void m_Init_LED_TIM(TIM_TypeDef* TIMx);
//NeoPixel Data Send
void m_send_BIT(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint8_t bit);

#endif /* CONFIG_PWM_H_ */
