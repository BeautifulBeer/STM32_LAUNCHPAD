/*
 * config_exti.h
 *
 *  Created on: 2017. 12. 4.
 *      Author: hw_3
 */

#ifndef CONFIG_EXTI_H_
#define CONFIG_EXTI_H_

#include <stm32f10x_exti.h>
#include <stm32f10x_gpio.h>
#include <misc.h>

/*
 * void EXTI0_IRQHandler(void);
 * void EXTI1_IRQHandler(void);
 * void EXTI2_IRQHandler(void);
 * void EXTI3_IRQHandler(void);
 * void EXTI4_IRQHandler(void);
 * void EXTI9_5_IRQHandler(void);
 * void EXTI15_10_IRQHandler(void);

1. Example

void EXTI2_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line2) != RESET){

		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}

 *
*/
void m_EXTI_GPIO_Interrupt(uint8_t GPIO_PortSourceGPIOx, uint8_t GPIO_PinSourcex, uint32_t EXTI_Linex, int EXTIx_IRQn);


#endif /* CONFIG_EXTI_H_ */
