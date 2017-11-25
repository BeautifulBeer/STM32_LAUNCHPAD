/*
 * config_bluetooth.h
 *
 *  Created on: 2017. 11. 24.
 *      Author: hw_3
 */

#ifndef CONFIG_BLUETOOTH_H_
#define CONFIG_BLUETOOTH_H_

#include <stm32f10x.h>
#include <stm32f10x_exti.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_usart.h>

/*
 *
 * This code implements bluetooth data transmission with android
 *
 * USART3(PC10 - TX, PC11 - RX), USART2(PA2 - TX, PA3 - RX) is used
 *
 */

//Initialize all configuration for usart3 transmission including clock enable
void m_Init_BT_USART3();
//Initialize all configuration for usart2 transmission including clock enable
void m_Init_BT_USART2();
//Initialize GPIOC configuration for USART3
void m_Init_BT_USART3_GPIOC();
//Initialize GPIOA configuration for USART2
void m_Init_BT_USART2_GPIOA();
//Initialize External Interrupt configuration for bluetooth
void m_Init_BT_USART2_EXIT();
//Initialize External Interrupt configuration for bluetooth
void m_Init_BT_USART3_EXIT();
//Initialize USART configuration for bluetooth
void m_Init_BT_USART(USART_TypeDef* USARTx);
//Interrupt Handler for USART2
void USART2_IRQHandler(void);
//Interrupt Handler for USART3
void USART3_IRQHandler(void);


#endif /* CONFIG_BLUETOOTH_H_ */