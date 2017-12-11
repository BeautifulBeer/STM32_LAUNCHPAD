#ifndef CONFIG_MPR121_H_
#define CONFIG_MPR121_H_

#include <Adafruit_MPR121.h>
#include <stm32f10x.h>
#include <stm32f10x_i2c.h>
#include <stm32f10x_gpio.h>



#define MPR121_ClockSpeed			200000




//void m_Init_MPR121(void);
//flag : 1 - Alternative push pull , flag : 0 - Input mode
void m_Init_MPR121_GPIO(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pinx, uint8_t flag);
//void m_Init_MPR121_I2C(I2C_TypeDef *I2Cx);
//void m_printState(uint16_t lasttouched, uint16_t currtouched);

#endif /* CONFIG_MPR121_H_ */
