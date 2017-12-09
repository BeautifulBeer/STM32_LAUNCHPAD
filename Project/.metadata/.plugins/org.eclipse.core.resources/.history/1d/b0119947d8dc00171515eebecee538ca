#ifndef CONFIG_MPR121_H_
#define CONFIG_MPR121_H_

#include <Adafruit_MPR121.h>
#include <stm32f10x.h>
#include <stm32f10x_i2c.h>
#include <stm32f10x_gpio.h>

void m_Init_MPR121(uint8_t* buffer_);
void m_Init_MPR121_I2C1(void);
void m_Init_MPR121_GPIOB(void);
void m_Init_MPR121_I2C(I2C_TypeDef *I2Cx);
void m_printState(uint16_t lasttouched, uint16_t currtouched, uint8_t* buffer);

#endif /* CONFIG_MPR121_H_ */
