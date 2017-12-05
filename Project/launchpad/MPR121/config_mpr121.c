#include "config_mpr121.h"

void m_Init_MPR121(uint8_t* buffer_) {
	begin(buffer_);
	m_Init_MPR121_GPIOB();
	m_Init_MPR121_I2C1();
}

void m_Init_MPR121_GPIOB() {
	GPIO_InitTypeDef gpio_init_;
	gpio_init_.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	gpio_init_.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_init_.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB, &gpio_init_);
}

void m_Init_MPR121_I2C(I2C_TypeDef *I2Cx) {
	I2C_InitTypeDef i2c_init_;
	i2c_init_.I2C_Mode = I2C_Mode_I2C;
	i2c_init_.I2C_DutyCycle = I2C_DutyCycle_2;
	i2c_init_.I2C_OwnAddress1 = 0x5A;
	i2c_init_.I2C_Ack = I2C_Ack_Enable;
	i2c_init_.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	i2c_init_.I2C_ClockSpeed = 8000000;
	I2C_Init(I2Cx, &i2c_init_);
}

void m_Init_MPR121_I2C1(void) {
	I2C_DeInit(I2C1);
	m_Init_MPR121_I2C(I2C1);
	I2C_Cmd(I2C1, ENABLE);
	I2C_ITConfig(I2C1, I2C_IT_EVT | I2C_IT_ERR, ENABLE);
}

void m_printState(uint16_t lasttouched, uint16_t currtouched, uint8_t* buffer) {
	uint8_t i = 0;

	currtouched = touched(MPR121_I2CADDR_DEFAULT, buffer);

	for (i = 0; i < 12; i++) {
		// it if *is* touched and *wasnt* touched before, alert!
		if ((currtouched & _BV(i)) && !(lasttouched & _BV(i))) {
			GPIOD->BSRR = GPIO_BSRR_BS2;
		}
		// if it *was* touched and now *isnt*, alert!
		if (!(currtouched & _BV(i)) && (lasttouched & _BV(i))) {
			GPIOD->BSRR = GPIO_BSRR_BR2;
		}
	}

	lasttouched = currtouched;
}
