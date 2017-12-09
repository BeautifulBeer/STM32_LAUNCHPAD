#include "config_mpr121.h"

void m_Init_MPR121(uint8_t* buffer_) {
	begin(buffer_);
}

void m_Init_MPR121_GPIO(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pinx, uint8_t flag){
	GPIO_InitTypeDef gpio_init_;
	gpio_init_.GPIO_Pin = GPIO_Pinx;
	gpio_init_.GPIO_Speed = GPIO_Speed_50MHz;
	if(flag){
		gpio_init_.GPIO_Mode = GPIO_Mode_AF_PP;
	}else{
		gpio_init_.GPIO_Mode = GPIO_Mode_IPU;
	}
	GPIO_Init(GPIOx, &gpio_init_);
}

void m_Init_MPR121_I2C(I2C_TypeDef *I2Cx) {
	I2C_InitTypeDef i2c_init_;
	I2C_DeInit(I2Cx);
	I2C_Cmd(I2Cx, DISABLE);
	i2c_init_.I2C_Mode = I2C_Mode_I2C;
	i2c_init_.I2C_DutyCycle = I2C_DutyCycle_2;
	i2c_init_.I2C_OwnAddress1 = MPR121_I2CADDR_DEFAULT;
	i2c_init_.I2C_Ack = I2C_Ack_Enable;
	i2c_init_.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	i2c_init_.I2C_ClockSpeed = MPR121_ClockSpeed;
	I2C_Init(I2Cx, &i2c_init_);
	I2C_ITConfig(I2Cx, I2C_IT_EVT | I2C_IT_ERR, ENABLE);
	I2C_Cmd(I2Cx, ENABLE);
	while (I2C_GetFlagStatus(MPR121, I2C_FLAG_BUSY));
}

void m_printState(uint16_t lasttouched, uint16_t currtouched, uint8_t* buffer) {
	uint8_t i = 0;

	currtouched = touched(MPR121_I2CADDR_DEFAULT, buffer);

	for (i = 0; i < 12; i++) {
		// it if *is* touched and *wasnt* touched before, alert!
		if ((currtouched & _BV(i)) && !(lasttouched & _BV(i))) {
			GPIO_SetBits(GPIOD, GPIO_Pin_2);
		}
		// if it *was* touched and now *isnt*, alert!
		if (!(currtouched & _BV(i)) && (lasttouched & _BV(i))) {
			GPIO_ResetBits(GPIOD, GPIO_Pin_2);
		}
	}

	lasttouched = currtouched;
}
