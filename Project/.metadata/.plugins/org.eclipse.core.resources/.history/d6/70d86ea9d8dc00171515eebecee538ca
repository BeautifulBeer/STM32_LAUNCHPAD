/*
 * config_system.c
 *
 *  Created on: 2017. 11. 24.
 *      Author: hw_3
 */

#include "config_system.h"

void m_Init_GPIO_Clock(GPIO_TypeDef* GPIOx){
	if(GPIOx == GPIOA){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	}else if(GPIOx == GPIOB){
		RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	}else if(GPIOx == GPIOC){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	}else if(GPIOx == GPIOD){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	}else if(GPIOx == GPIOE){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	}
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
	    RCC_PCLK1Config(RCC_HCLK_Div1);
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
void m_Init_TIM_Clock(TIM_TypeDef* TIMx){
	if(TIMx == TIM1){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	}else if(TIMx == TIM2){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	}else if(TIMx == TIM3){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	}else if(TIMx == TIM4){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	}else if(TIMx == TIM5){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	}
}
void SetSysClock(void) //40MHz
{
   volatile int StartUpCounter = 0, HSEStatus = 0;

   /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
   /* Enable HSE */
   RCC->CR |= (RCC_CR_HSEON);

   /* Wait till HSE is ready and if Time out is reached exit */
   do
   {
      HSEStatus = RCC->CR & RCC_CR_HSERDY;
      StartUpCounter++;
   } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

   if ((RCC->CR & RCC_CR_HSERDY) != RESET)
   {
      HSEStatus = 0x01;
   }
   else
   {
      HSEStatus = 0x00;
   }

   if (HSEStatus == 0x01)
   {
      /* Enable Prefetch Buffer */
      FLASH->ACR |= FLASH_ACR_PRFTBE;

      /* Flash 0 wait state */
      FLASH->ACR &= (~FLASH_ACR_LATENCY);
      FLASH->ACR |= FLASH_ACR_LATENCY_0;

      /* HCLK = SYSCLK / 2 */
      RCC->CFGR |= RCC_CFGR_HPRE_DIV2;

      /* PCLK2 = HCLK / 2 */
      RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;

      /* PCLK1 = HCLK */
      RCC->CFGR |= RCC_CFGR_PPRE1_DIV1;

      /* Configure PLLs ------------------------------------------------------*/
      /* PLL configuration: PLLCLK = PREDIV1 * 5 = 40MHz */
      RCC->CFGR &= ~(RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL);
      RCC->CFGR |= (RCC_CFGR_PLLXTPRE_PREDIV1 | RCC_CFGR_PLLSRC_PREDIV1 |
            RCC_CFGR_PLLMULL5);

      /* PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40MHz */
      /* PREDIV1 configuration: PREDIV1CLK = PLL2 / 5 = 8MHz */
      RCC->CFGR2 &= (~(RCC_CFGR2_PREDIV2 | RCC_CFGR2_PLL2MUL |
            RCC_CFGR2_PREDIV1 | RCC_CFGR2_PREDIV1SRC));
      RCC->CFGR2 |= (RCC_CFGR2_PREDIV2_DIV5 | RCC_CFGR2_PLL2MUL8 |
            RCC_CFGR2_PREDIV1SRC_PLL2 | RCC_CFGR2_PREDIV1_DIV5);

      /* Enable PLL2 */
      RCC->CR |= RCC_CR_PLL2ON;
      /* Wait till PLL2 is ready */
      while((RCC->CR & RCC_CR_PLL2RDY) == 0)
      {
      }

      /* Enable PLL */
      RCC->CR |= RCC_CR_PLLON;

      /* Wait till PLL is ready */
      while((RCC->CR & RCC_CR_PLLRDY) == 0)
      {
      }

      /* Select PLL as system clock source */
      RCC->CFGR &= (~(RCC_CFGR_SW));
      RCC->CFGR |= RCC_CFGR_SW_PLL;

      /* Wait till PLL is used as system clock source */
      while ((RCC->CFGR & RCC_CFGR_SWS) != 0x08)
      {
      }
   }
   else
   { /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
   }
}

void SysInit(void) {
   /* Set HSION bit */
   /* Internal Clock Enable */
   RCC->CR |= 0x00000001;

   /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
   RCC->CFGR &= 0xF0FF0000;

   /* Reset HSEON, CSSON and PLLON bits */
   RCC->CR &= 0xFEF6FFFF;

   /* Reset HSEBYP bit */
   RCC->CR &= 0xFFFBFFFF;

   /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
   RCC->CFGR &= 0xFF80FFFF;

   /* Reset PLL2ON and PLL3ON bits */
   RCC->CR &= 0xEBFFFFFF;

   /* Disable all interrupts and clear pending bits  */
   RCC->CIR = 0x00FF0000;

   /* Reset CFGR2 register */
   RCC->CFGR2 = 0x00000000;
}
