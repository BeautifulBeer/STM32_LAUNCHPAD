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


#define CONST_CHRACTER_ROW 			2
#define CONST_CHRACTER_COL 			2
#define CONST_MUSIC_NOTE_ROW 		24
#define RGB_BIT_SIZE				8
#define MPR121_BUFFER_SIZE			2

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
uint8_t I2C_Buffer[MPR121_BUFFER_SIZE];

//System State

//Interrupt
int EXTI0_flag;
int EXTI1_flag;
int EXTI2_flag;
int EXTI3_flag;
int EXTI4_flag;
int EXTI5_flag;
int I2C1_ER_flag;
int I2C1_ER_Status;
int LED_BLINK;

//PMM
//static int pwm_delay;
//static int TIM4_IT_UPDATE_flag;
int cur_pixel, cur_rgb, cur_pos, cur_reset;
uint8_t PIXEL_PATTERN_1[CONST_PIXEL_NUM][CONST_RGB_NUM] = {
		{235, 245, 127},
		{13 , 134, 178},
		{56 , 200, 155},
		{15 , 40 , 113},
		{175, 100, 35 },
		{51 , 158, 147},
		{175, 100, 52 },
		{78 , 200, 3  }
};

void printObject(int** data, int start_x, int start_y, int data_row, int data_col){
	//for()
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
		if(LED_BLINK){
			GPIO_ResetBits(GPIOD, GPIO_Pin_7);
			LED_BLINK = 0;
		}else{
			GPIO_SetBits(GPIOD, GPIO_Pin_7);
			LED_BLINK = 1;
		}

		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

/*void I2C1_EV_IRQHandler(void){
	GPIO_SetBits(GPIOD, GPIO_Pin_4);
}*/


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

void TIM3_IRQHandler(void){
	if(TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET){
		if(cur_pixel != CONST_PIXEL_NUM){
			if(cur_rgb != CONST_RGB_NUM){
				if(cur_pos != RGB_BIT_SIZE){
					m_send_BIT(TIM3, TIM_Channel_2,
							PIXEL_PATTERN_1[cur_pixel][cur_rgb] & _BV(7 - cur_pos));
					cur_pos++;
				}else{
					cur_pos = 0;
					cur_rgb++;
				}
			}else{
				cur_rgb = 0;
				cur_pixel++;
			}
		}else{
			if(cur_reset != CONST_RESET_PERIOD){
				m_send_BIT(TIM3, TIM_Channel_2, 2);
				cur_reset++;
			}else{
				//Initialize all variables
				cur_reset = 0;
				cur_pixel = 0;
			}
		}
		TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);
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

void I2C1_ER_IRQHandler(void){
	I2C1_ER_flag = 1;
	if(I2C_GetITStatus(I2C1, I2C_IT_BERR) != RESET){
		I2C1_ER_Status = 0;
	}else if(I2C_GetITStatus(I2C1, I2C_IT_ARLO) != RESET){
		I2C1_ER_Status = 1;
	}else if(I2C_GetITStatus(I2C1, I2C_IT_AF) != RESET){
		I2C1_ER_Status = 2;
	}else if(I2C_GetITStatus(I2C1, I2C_IT_OVR) != RESET){
		I2C1_ER_Status = 3;
	}else if(I2C_GetITStatus(I2C1, I2C_IT_PECERR) != RESET){
		I2C1_ER_Status = 4;
	}else if(I2C_GetITStatus(I2C1, I2C_IT_TIMEOUT) != RESET){
		I2C1_ER_Status = 5;
	}else if(I2C_GetITStatus(I2C1, I2C_IT_SMBALERT) != RESET){
		I2C1_ER_Status = 6;
	}
}

void Configure_LED() {
   GPIO_InitTypeDef GPIO_init;

   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

   GPIO_init.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_init.GPIO_Pin = (GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_7);
   GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;

   GPIO_Init(GPIOD, &GPIO_init);
}

int main(){
	//int delay;
	//char buffer_[BT_STR_MAX_LENGTH];

	//System Configuration Initialization
	SysInit();
	//m_System_Clock();
	SetSysClock();

	//Clock Enable
	m_Init_GPIO_Clock(GPIOA);
	m_Init_GPIO_Clock(GPIOB);
	m_Init_GPIO_Clock(GPIOC);
	m_Init_GPIO_Clock(GPIOE);
	m_Init_GPIO_Clock(GPIOD);
	m_Init_AFIO_Clock(); //for timer
	m_Init_I2C_Clock(I2C1);
	//m_Init_TIM_Clock(TIM3);

	//LED
	Configure_LED();


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
	m_Init_MCO_GPIOA();

	//Initialize USART1/2
//	m_Init_BT_USART1();
//	m_Init_BT_USART2();

	//Interrupt Configuration - NVIC
//	m_Init_USART2_NVIC();
//	m_Init_USART1_NVIC();
	//m_Init_TIM_NVIC(TIM3);
	m_Init_I2C_NVIC(I2C1, 0); // enable I2C ER Interrupt



	//I2C MPR121
	m_Init_MPR121_GPIO(GPIOB, GPIO_Pin_6, 1);
	m_Init_MPR121_GPIO(GPIOB, GPIO_Pin_7, 1);
	m_Init_MPR121_GPIO(GPIOE, GPIO_Pin_0, 0);
	//m_Init_MPR121_GPIO(GPIOB, GPIO_Pin_10, 1);
	//m_Init_MPR121_GPIO(GPIOB, GPIO_Pin_11, 1);
	m_Init_MPR121_I2C(I2C1);
	//m_Init_MPR121(I2C_Buffer);



	//Timer PWM PA7 Should be selected

	//Timer Initialization - GPIO setting
	/*m_Init_TIM(TIM3, PERIOD, PRESCALAR);
	m_Init_PWM_GPIO(GPIOA, GPIO_Pin_6, 1);
	m_Init_PWM_GPIO(GPIOA, GPIO_Pin_7, 1);
	m_Init_PWM_GPIO(GPIOB, GPIO_Pin_0, 1);
	m_Init_PWM_GPIO(GPIOB, GPIO_Pin_1, 1);

	m_Init_PWM_TIM(TIM3, 1, 1, 1, 1);
*/
	//External Interrupt Configuration - EXTI
	//m_EXTI_GPIO_Interrupt(GPIO_PortSourceGPIOC, GPIO_PinSource4, EXTI_Line4, EXTI4_IRQn);
	//m_EXTI_GPIO_Interrupt(GPIO_PortSourceGPIOC, GPIO_PinSource5, EXTI_Line5, EXTI9_5_IRQn); // volume up
	//m_EXTI_GPIO_Interrupt(GPIO_PortSourceGPIOC, GPIO_PinSource2, EXTI_Line2, EXTI2_IRQn); // volume down
	//m_EXTI_GPIO_Interrupt(GPIO_PortSourceGPIOE, GPIO_PinSource0, EXTI_Line0, EXTI0_IRQn); // volume down

	//MPR121 GPIOE Pin 0 - IRQn
	m_EXTI_GPIO_Interrupt(GPIO_PortSourceGPIOE, GPIO_PinSource0, EXTI_Line0, EXTI0_IRQn);

//	m_USART_DataSend(USART2, "AT+BTSCAN", buffer_);
//
	m_MCO_Enable();

	LCD_Configuration();
	LCD_Init();


	//Main Loop
	while(1){
		//m_printState(lasttouched, currtouched, I2C_Buffer);
		if(EXTI0_flag){
			//Show_LCD_Status();
			//GPIOD->BSRR = GPIO_BSRR_BS2;
			m_printState(lasttouched, currtouched, I2C_Buffer);
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
		if(I2C1_ER_flag){
			LCD_Clear(WHITE);
			LCD_ShowNum(100, 100, I2C1_ER_Status, 4, BLACK, WHITE);
			I2C1_ER_flag = 0;
		}
		/*if(LED_DATASEND) {
			m_send_pixel_data(&TIM4_IT_UPDATE_flag, PIXEL_PATTERN_1);
			m_delay(&TIM4_IT_UPDATE_flag, RESET_CODE);

		}*/
	}
}
