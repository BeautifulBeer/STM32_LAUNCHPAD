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

void m_Init_GPIOC_Clock(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
}

void m_Init_USART2_Clock(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
}

void m_Init_USART1_Clock(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
}

void m_System_Clock(void){
	RCC_DeInit();
	/* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
	/* Enable HSE */
	RCC_HSEConfig(RCC_CR_HSEON);
	/* Wait till HSE is ready and if Time out is reached exit */
	if (RCC_WaitForHSEStartUp())
	{
		/* Enable Prefetch Buffer */
	    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
	    /* Flash latency set 0*/
	    FLASH_SetLatency(FLASH_Latency_0);
	    /* HCLK = SYSCLK / 2 */
	    RCC_HCLKConfig(RCC_SYSCLK_Div2);
	    /* PCLK2 = HCLK / 2 */
	    RCC_PCLK2Config(RCC_HCLK_Div2);
	    /* PCLK1 = HCLK */
	    RCC_PCLK1Config(RCC_HCLK_Div1);
	    /* Enable PLL */
	    RCC_PLLCmd(ENABLE);
	    RCC_PLLConfig(RCC_CFGR_PLLSRC_PREDIV1, RCC_CFGR_PLLMULL5);
	    /* Enable PLL2 */
	    RCC_PLL2Cmd(ENABLE);
	    RCC_PLL2Config(RCC_CFGR2_PREDIV2_DIV5 | RCC_CFGR2_PLL2MUL8 |
	    	    		RCC_CFGR2_PREDIV1SRC_PLL2 | RCC_CFGR2_PREDIV1_DIV5);
	    /* Select PLL as system clock source */
	    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	    /* Wait till PLL2 is ready */
	    while(RCC_GetFlagStatus(RCC_FLAG_PLL2RDY) == RESET);
	    /* Wait till PLL is ready */
	    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
	    /* Wait till PLL is used as system clock source */
	    while (RCC_GetSYSCLKSource() != RCC_CFGR_SWS_PLL);
	}
}
