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

//Enable GPIOA
void m_Init_GPIOA_Clock(void);
//Enable GPIOC
void m_Init_GPIOC_Clock(void);
//Enable USART2
void m_Init_USART2_Clock(void);
//Enable USART1
void m_Init_USART1_Clock(void);
//Setting System clock to predefined - 8MHz
void m_System_Clock(void);
//Use MCO as System clock
void m_MCO_Enable(void);
//Enable MCO - GPIOA 8 Pin
void m_Init_MCO_GPIOA(void);

#endif /* SYSTEM_CONFIG_H_ */
