/*
 * main.c
 *
 *  Created on: 2017. 11. 24.
 *      Author: hw_3
 */

/*
 * flash setting
 *
flash load "./launchpad/flashclear.axf"

flash load "./launchpad/Debug/launchpad.axf"
 */
#include "bluetooth/config_bluetooth.h"
#include "init/config_system.h"
#include "init/config_nvic.h"
#include "init/config_exti.h"
#include <lcd.h>
#include <touch.h>
#include "core_cm3.h"
#include "MPR121/config_mpr121.h"
#include "PWM/config_pwm.h"

//static int led_status = 1;
static int led_status_update = 1;
static int led_status_cc3 = 1;

#define CONST_CHRACTER_ROW 2
#define CONST_CHRACTER_COL 2
#define CONST_MUSIC_NOTE_ROW 24

//TFT LCD Variables
int Xposition;
int Yposition;
uint32_t DestAddr;
//uint16_t MUSIC_NOTE[CONST_MUSIC_NOTE_ROW] ={
//	0b0000000000000000,
//	0b0001111111111110,
//	0b0001111111111110,
//	0b0001100000000110,
//	0b0001100000000110,
//	0b0001111111111110,
//	0b0001111111111110,
//	0b0001100000000110,
//	0b0001100000000110,
//	0b0001100000000110,
//	0b0001100000000110,
//	0b0001100000000110,
//	0b0001100000000110,
//	0b0001100000000110,
//	0b0001100000000110,
//	0b0001100000000110,
//	0b0001100000001110,
//	0b0001100000011111,
//	0b0011100000111111,
//	0b0111110000111111,
//	0b1111110000011110,
//	0b1111110000001100,
//	0b0111100000000000,
//	0b0011000000000000
//};



//I2C Variables
uint16_t lasttouched;
uint16_t currtouched;
uint8_t I2C_Buffer[2];

//System State
int EXTI0_flag;
int EXTI1_flag;
int EXTI2_flag;
int EXTI3_flag;
int EXTI4_flag;
int EXTI5_flag;
int TIM4_IT_UPDATE_flag;
int TIM4_CC3_flag;

void printObject(int** data, int start_x, int start_y, int data_row, int data_col){
	//for()
}

void InterruptEnable(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//Interrupt
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
}

//void Show_LCD_Status(){
//		for(Xposition=1;Xposition<=240;Xposition++){
//				for(Yposition=1;Yposition<=320;Yposition++){
//					LCD_DrawPoint(Xposition,Yposition);
//		}
//	}
//}

void EXTI0_IRQHandler(void) {
	if(EXTI_GetITStatus(EXTI_Line0) != RESET){
		EXTI0_flag = 1;
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}


void EXTI4_IRQHandler(void){ // draw music status
	if(EXTI_GetITStatus(EXTI_Line4) != RESET){
		EXTI4_flag =1;
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}


void EXTI9_5_IRQHandler(void){ //volume up status
	if(EXTI_GetITStatus(EXTI_Line5) != RESET){
		EXTI5_flag =1;
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
}

void EXTI2_IRQHandler(void){ //volume down status
	if(EXTI_GetITStatus(EXTI_Line2) != RESET){
		EXTI2_flag =1;
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}

void TIM4_IRQHandler(void){
	//GPIO_SetBits(GPIOD, GPIO_Pin_2);

	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET){
		TIM4_IT_UPDATE_flag =1;
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
	if(TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET){
		TIM4_CC3_flag =1;
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC3);
	}
}


//void USART2_IRQHandler(void){
//	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
//		uint16_t data = USART_ReceiveData(USART2);
//		m_USART_byteSend(USART1, data);
//		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
//	}
//}
//
//void USART1_IRQHandler(void){
//	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
//		uint16_t data = USART_ReceiveData(USART1);
//		//m_USART_DataSend(USART1, data);
//		m_USART_byteSend(USART2, data);
//		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
//	}
//}

void Configure_LED() {
   GPIO_InitTypeDef GPIO_init;

   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

   GPIO_init.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_init.GPIO_Pin = (GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_7);
   GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;

   GPIO_Init(GPIOD, &GPIO_init);
}

int main(){
	//char buffer_[BT_STR_MAX_LENGTH];
	//System Configuration Initialization
	SysInit();
	//m_System_Clock();
	SetSysClock();

	//Clock Enable
	m_Init_GPIOA_Clock();
	m_Init_AFIO_Clock();
	m_Init_I2C_Clock();
	m_Init_GPIOB_Clock();
	m_Init_GPIOE_Clock();
	m_Init_TIM4_Clock();

	//USARTx
//	m_Init_USART2_Clock();
//	m_Init_USART1_Clock();

	//Interrupt Configuration - EXTI
//	m_Init_BT_USART2_EXIT();
//	m_Init_BT_USART1_EXIT();

	//Initialize USART1/2 GPIOA
//	m_Init_BT_USART1_GPIOA();
//	m_Init_BT_USART2_GPIOA();
	//MCO Port Init
	//m_Init_MCO_GPIOA();

	//Initialize USART1/2
//	m_Init_BT_USART1();
//	m_Init_BT_USART2();

	//Interrupt Configuration - NVIC
//	m_Init_USART2_NVIC();
//	m_Init_USART1_NVIC();
	m_Init_TIM4_NVIC();


	//Timer GPIO Setting
	m_Init_TIM4_CH3_GPIOB();
	m_Init_PWM_TIM(TIM4);
	//m_Init_TIM4();


	//External Interrupt Configuration - EXTI
	//m_EXTI_GPIO_Interrupt(GPIO_PortSourceGPIOC, GPIO_PinSource4, EXTI_Line4, EXTI4_IRQn);
	//m_EXTI_GPIO_Interrupt(GPIO_PortSourceGPIOC, GPIO_PinSource5, EXTI_Line5, EXTI9_5_IRQn); // volume up
	//m_EXTI_GPIO_Interrupt(GPIO_PortSourceGPIOC, GPIO_PinSource2, EXTI_Line2, EXTI2_IRQn); // volume down
	//m_EXTI_GPIO_Interrupt(GPIO_PortSourceGPIOE, GPIO_PinSource0, EXTI_Line0, EXTI0_IRQn); // volume down


//	m_USART_DataSend(USART2, "AT+BTSCAN", buffer_);
//
	//m_MCO_Enable();

//	GPIOD->BSRR = GPIO_BSRR_BS2;
//	GPIOD->BSRR = GPIO_BSRR_BS3;
//	GPIOD->BSRR = GPIO_BSRR_BS4;
//	GPIOD->BSRR = GPIO_BSRR_BS7;


	//Module Initialization
	//m_Init_MPR121(I2C_Buffer);

	Configure_LED();
	//LCD_Init();


	//Main Loop
	while(1){
//		m_printState(lasttouched, currtouched, I2C_Buffer);
//		GPIOD->BSRR = GPIO_BSRR_BR2;
		if(EXTI0_flag){
			//Show_LCD_Status();
			GPIOD->BSRR = GPIO_BSRR_BS2;
			EXTI0_flag = 0;
		}
		if(EXTI4_flag){
			//Show_LCD_Status();
			EXTI4_flag = 0;
		}
		if(EXTI5_flag) {
			LCD_Clear(WHITE);
			LCD_ShowNum(100, 100, DestAddr++, 4, BLACK, WHITE);
			EXTI5_flag = 0;
		}
		if(EXTI2_flag) {
			LCD_Clear(WHITE);
			LCD_ShowNum(100, 100, DestAddr--, 4, BLACK, WHITE);
			EXTI2_flag = 0;
		}
		if(TIM4_IT_UPDATE_flag) {
			if(led_status_update){
				GPIO_SetBits(GPIOD,GPIO_Pin_3);
				led_status_update=0;
			}else{
				GPIO_ResetBits(GPIOD,GPIO_Pin_3);
				led_status_update=1;
			}
		}
		if(TIM4_CC3_flag) {
			if(led_status_cc3){
				GPIO_SetBits(GPIOD,GPIO_Pin_4);
				led_status_cc3=0;
			}else{
				GPIO_ResetBits(GPIOD,GPIO_Pin_4);
				led_status_cc3=1;
			}
		}
	}
}
