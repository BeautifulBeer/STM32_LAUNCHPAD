/*
 * system_config.h
 *
 *  Created on: 2017. 11. 24.
 *      Author: hw_3
 */

#ifndef SYSTEM_CONFIG_H_
#define SYSTEM_CONFIG_H_

#include <misc.h>
#include <stm32f10x.h>
#include <stm32f10x_rcc.h>


//Enable GPIOA
void m_Init_GPIOA_Clock();
//Enable GPIOC
void m_Init_GPIOC_Clock();
//Enable USART2
void m_Init_USART2_Clock();
//Enable USART3
void m_Init_USART3_Clock();

#endif /* SYSTEM_CONFIG_H_ */
