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

#define CONST_VOLUME_BASE_XPOS		30
#define CONST_VOLUME_BASE_YPOS		310
#define CONST_MAX_VOLUME			10
#define CONST_CHRACTER_ROW 			2
#define CONST_CHRACTER_COL 			2
#define CONST_MUSIC_NOTE_ROW 		24
#define CONST_TFT_X					240 - CONST_MUSIC_NOTE_ROW
#define CONST_TFT_Y					320 - 16
#define RGB_BIT_SIZE				8

#define _BV(bit) (1 << (bit))


void Music_background(void);
void removeObject(uint16_t x_pos, uint16_t y_pos, const uint16_t* obj);
void printObject(uint16_t x_pos, uint16_t y_pos, const uint16_t* obj);
void printVolumeBar(uint8_t volume);
void removeVolumeBar(uint8_t volume);
//Volume bar y : 8 , x : 20 , gap : 2, increment : 2
//up_down - up : 1 , down : 0
void printVolume(uint8_t cur_volume, uint8_t last_volume, uint8_t up_down);
#endif /* CONFIG_LCD_H_ */
