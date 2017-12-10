/*
 * config_lcd.c
 *
 *  Created on: 2017. 12. 10.
 *      Author: hw_4
 */

#include "config_lcd.h"


void Music_background() {
	LCD_Clear(WHITE);
	LCD_DrawLine(72, 0, 72, 320);
	LCD_DrawLine(84, 0, 84, 320);
	LCD_DrawLine(96, 0, 96, 320);
	LCD_DrawLine(108, 0, 108, 320);
	LCD_DrawLine(120, 0, 120, 320);
}

void removeObject(uint16_t x_pos, uint16_t y_pos, const uint16_t* obj) {
	int i, j;
	for (i = 0; i < CONST_MUSIC_NOTE_ROW; i++) {
		for (j = 15; j >= 0; j--) {
			if (obj[i] & _BV(j)) {
				if ((x_pos + i) % 12 != 0) {
					LCD_ClearPoint(x_pos + i, y_pos + j);
				}
			}
		}
	}
}

void printObject(uint16_t x_pos, uint16_t y_pos, const uint16_t* obj) {
	int i, j;
	for (i = 0; i < CONST_MUSIC_NOTE_ROW; i++) {
		for (j = 15; j >= 0; j--) {
			if (obj[i] & _BV(j)) {
				LCD_DrawPoint(x_pos + i, y_pos + j);
			}
		}
	}
}

void printVolumeBar(uint8_t volume){
	int i,j;
	for(i=0; i < volume * 2; i++){
		for(j=0; j<8;j++){
			LCD_DrawPoint(CONST_VOLUME_BASE_XPOS - i,
					CONST_VOLUME_BASE_YPOS - (volume*10) - j);
		}
	}
}

void removeVolumeBar(uint8_t volume){
	int i,j;
		for(i=0; i < volume * 2; i++){
			for(j=0; j<8;j++){
				LCD_ClearPoint(CONST_VOLUME_BASE_XPOS - i,
						CONST_VOLUME_BASE_YPOS - (volume*10) - j);
			}
		}
}

void printVolume(uint8_t cur_volume, uint8_t last_volume, uint8_t up_down){
	if(cur_volume != last_volume){
		if(up_down){
			printVolumeBar(cur_volume);
		}else{
			removeVolumeBar(last_volume);
			printVolumeBar(cur_volume);
		}

	}
}
