/*
 * system_config.h
 *
 *  Created on: 2017. 11. 24.
 *      Author: hw_3
 */

#ifndef SYSTEM_CONFIG_H_
#define SYSTEM_CONFIG_H_

#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_flash.h>
#include <stm32f10x_gpio.h>
#include <system_stm32f10x.h>



//Enable TIMER
void m_Init_TIM_Clock(TIM_TypeDef* TIMx);
//Enable AFIO
void m_Init_AFIO_Clock(void);
//Enable GPIOx
void m_Init_GPIO_Clock(GPIO_TypeDef* GPIOx);
//Enable USART2
void m_Init_USART2_Clock(void);
//Enable USART1
void m_Init_USART1_Clock(void);
//Enable I2c1
void m_Init_I2C_Clock(void);
//Setting System clock to predefined - 8MHz
void m_System_Clock(void);
//Use MCO as System clock
void m_MCO_Enable(void);
//Enable MCO - GPIOA 8 Pin
void m_Init_MCO_GPIOA(void);
//System Clock Setting
void SetSysClock(void);
//System Init
void SysInit(void);
#endif /* SYSTEM_CONFIG_H_ */
