/*
 * config_interrupt.h
 *
 *  Created on: 2017. 11. 24.
 *      Author: hw_3
 */

#ifndef CONFIG_INTERRUPT_H_
#define CONFIG_INTERRUPT_H_

#include <stm32f10x.h>
#include <misc.h>

/*
 * Priority
 * USART2 : 0/0
 * USART3 : 0/0
 *
 *
 */

//Initialize nested vectored interrupt controller configuration for USART2, bluetooth
void m_Init_USART2_NVIC(void);
//Initialize nested vectored interrupt controller configuration for USART3, bluetooth
void m_Init_USART1_NVIC(void);
//Initialize nested vectored interrupt controller configuration for I2C1 - flag : 1 = Event Interrupt / flag : 0 = Error Interrupt
void m_Init_I2C_NVIC(I2C_TypeDef* I2Cx, uint8_t flag);
//Initialize nested vectored interrupt controller configuration for TIMx
void m_Init_TIM_NVIC(TIM_TypeDef* TIMx, uint32_t Priority);

#endif /* CONFIG_INTERRUPT_H_ */
