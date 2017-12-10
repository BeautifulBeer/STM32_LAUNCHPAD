/*
 * config_lcd.h
 *
 *  Created on: 2017. 12. 10.
 *      Author: hw_4
 */

#ifndef CONFIG_LCD_H_
#define CONFIG_LCD_H_

#include <lcd.h>
#include <touch.h>
#include <stm32f10x_tim.h>

#define CONST_VOLUME_BASE_XPOS		50
#define CONST_VOLUME_BASE_YPOS		295

#define CONST_MAX_VOLUME			10

#define CONST_CHRACTER_ROW 			2
#define CONST_CHRACTER_COL 			2

#define CONST_MUSIC_NOTE_ROW 		24
#define CONST_TREBLE_ROW			80
#define CONST_TREBLE_COL			2

#define CONST_TFT_X					240 - CONST_MUSIC_NOTE_ROW
#define CONST_TFT_Y					320 - 16

#define RGB_BIT_SIZE				8
#define TFT_BACKGROUND_WIDTH		11
#define TFT_BACKGROUND_HEIGHT		288
#define TFT_BACKGROUND_BASE_XPOS	32
#define TFT_BACKGROUND_BASE_YPOS	16
#define LCD_TIM_PERIOD				1000
#define LCD_TIM_PESCALAR			20000

#define _BV(bit) (1 << (bit))


void loading_TFT(uint16_t data[][TFT_BACKGROUND_WIDTH]);
void Music_background(uint16_t* SPEAKER, uint16_t TREBLE[][CONST_TREBLE_COL]);
void removeObject(uint16_t x_pos, uint16_t y_pos, const uint16_t* obj);
void printObject(uint16_t x_pos, uint16_t y_pos, const uint16_t* obj);
void printVolumeBar(uint8_t volume);
void removeVolumeBar(uint8_t volume);
//Volume bar y : 8 , x : 20 , gap : 2, increment : 2
//up_down - up : 1 , down : 0
void printVolume(uint8_t cur_volume, uint8_t last_volume, uint8_t up_down);
void m_Init_LCD_TIM(TIM_TypeDef* TIMx);

#endif /* CONFIG_LCD_H_ */
