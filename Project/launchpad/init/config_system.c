/*
 * config_system.c
 *
 *  Created on: 2017. 11. 24.
 *      Author: hw_3
 */

#include "config_system.h"

void m_Init_GPIOA_Clock(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
}

void m_Init_GPIOB_Clock(void){
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
}

void m_Init_GPIOC_Clock(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
}

void m_Init_GPIOE_Clock(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
}

void m_Init_USART2_Clock(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
}

void m_Init_USART1_Clock(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
}

void m_Init_I2C_Clock(void){
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
}

void m_System_Clock(void){
	RCC_DeInit();
	/* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
	/* Enable HSE */
	RCC_HSEConfig(RCC_HSE_ON);
	/* Wait till HSE is ready and if Time out is reached exit */
	if (RCC_WaitForHSEStartUp())
	{
		/* Enable Prefetch Buffer */
	    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
	    /* Flash latency set 0*/
	    FLASH_SetLatency(FLASH_Latency_0);
	    /* HCLK = SYSCLK / 1 */
	    RCC_HCLKConfig(RCC_SYSCLK_Div1);
	    /* PCLK2 = HCLK / 1 */
	    RCC_PCLK2Config(RCC_HCLK_Div1);
	    /* PCLK1 = HCLK / 2 */
	    RCC_PCLK1Config(RCC_HCLK_Div2);
	    /* Enable PLL2 */
	   	RCC_PLL2Cmd(ENABLE);
	   	RCC_PREDIV2Config(RCC_PREDIV2_Div5);
	   	RCC_PLL2Config(RCC_PLL2Mul_8);
	   	/* Wait till PLL2 is ready */
	   	while(RCC_GetFlagStatus(RCC_FLAG_PLL2RDY) != SET);
	   	//Select PREVIV1 MUX Source as PLL2 and div4
	    RCC_PREDIV1Config(RCC_PREDIV1_Source_PLL2, RCC_PREDIV1_Div5);
	    /* Enable PLL */
	    RCC_PLLCmd(ENABLE);
	    /* Wait till PLL is ready */
	    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != SET);
	    //Select PLL MUX Source as PLLCLK and mul5
	    RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_9);
	    /* Select PLL as system clock source */
	    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	    /* Wait till PLL is used as system clock source */
	    while (RCC_GetSYSCLKSource() != RCC_CFGR_SWS_PLL);
	}
}
void m_Init_MCO_GPIOA(void){
	GPIO_InitTypeDef gpio_;
	gpio_.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_.GPIO_Pin = GPIO_Pin_8;
	gpio_.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_);
}

void m_Init_AFIO_Clock(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
}

void m_MCO_Enable(void){
	RCC_MCOConfig(RCC_MCO_SYSCLK);
}

void m_Init_TIM2_Clock(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}
