/***************************************************
 This is a library for the MPR121 I2C 12-chan Capacitive Sensor

 Designed specifically to work with the MPR121 sensor from Adafruit
 ----> https://www.adafruit.com/products/1982

 These sensors use I2C to communicate, 2+ pins are required to
 interface
 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries.
 BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Adafruit_MPR121.h"


void begin(uint8_t* buffer_) {

	uint8_t c;

	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_SOFTRESET, 0x63);

	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_ECR, 0x0);

	c = readRegister8(MPR121_I2CADDR_DEFAULT, MPR121_CONFIG2, buffer_);

	if (c != 0x24)
		return;

	setThresholds(12, 6);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_MHDR, 0x01);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_NHDR, 0x01);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_NCLR, 0x0E);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_FDLR, 0x00);

	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_MHDF, 0x01);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_NHDF, 0x05);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_NCLF, 0x01);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_FDLF, 0x00);

	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_NHDT, 0x00);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_NCLT, 0x00);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_FDLT, 0x00);

	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_DEBOUNCE, 0);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_CONFIG1, 0x10); // default, 16uA charge current
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_CONFIG2, 0x20); // 0.5uS encoding, 1ms period

//  writeRegister(MPR121_AUTOCONFIG0, 0x8F);

//  writeRegister(MPR121_UPLIMIT, 150);
//  writeRegister(MPR121_TARGETLIMIT, 100); // should be ~400 (100 shifted)
//  writeRegister(MPR121_LOWLIMIT, 50);
	// enable all electrodes
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_ECR, 0x8F); // start with first 5 bits of baseline tracking

}

void setThreshholds(uint8_t touch, uint8_t release) {

	setThresholds(touch, release);
}

void setThresholds(uint8_t touch, uint8_t release) {
	uint8_t i = 0;

	for (i = 0; i < 12; i++) {
		MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_TOUCHTH_0 + 2 * i, touch);
		MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_RELEASETH_0 + 2 * i, release);
	}
}

uint16_t filteredData(uint8_t addr, uint8_t* buffer, uint8_t t) {
	if (t > 12)
		return 0;
	return readRegister16(addr, MPR121_FILTDATA_0L + t * 2, buffer);
}

uint16_t baselineData(uint8_t addr, uint8_t* buffer, uint8_t t) {
	uint8_t b1;

	if (t > 12)
		return 0;
	b1 = readRegister8(addr, MPR121_BASELINE_0 + t, buffer);
	return (b1 << 2);
}

uint16_t touched(uint8_t addr, uint8_t* buffer) {
	uint16_t t;

	t = readRegister16(addr, MPR121_TOUCHSTATUS_L, buffer);
	return t & 0x0FFF;
}

uint8_t readRegister8(uint8_t addr, uint8_t reg, uint8_t* buffer) {

	MPR121_I2C_BufferRead(addr, buffer, reg, 1);

	return *buffer;
}

uint16_t readRegister16(uint8_t addr, uint8_t reg, uint8_t* buffer) {
	uint16_t data;

	MPR121_I2C_BufferRead(addr, buffer, reg, 2);

	data = (buffer[0] << 8) | buffer[1];

	return data;
}

//************************************************************************
//!
// @brief  Writes 8-bits to the specified destination register
//
//************************************************************************
void MPR121_I2C_ByteWrite(uint8_t slaveAddr, uint8_t writeAddr, uint8_t value) {

	 //Send START condition
	I2C_GenerateSTART(MPR121, ENABLE);

	 //Test on EV5 and clear it
	while (!I2C_CheckEvent(MPR121, I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(MPR121, slaveAddr, I2C_Direction_Transmitter);

	 //Test on EV6 and clear it
	while (!I2C_CheckEvent(MPR121, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	 //Send the MPU6050's internal address to write to
	I2C_SendData(MPR121, writeAddr);

	 //Test on EV8 and clear it
	while (!I2C_CheckEvent(MPR121, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	 //Send the byte to be written
	I2C_SendData(MPR121, value);

	 //Test on EV8 and clear it
	while (!I2C_CheckEvent(MPR121, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	 //Send STOP condition
	I2C_GenerateSTOP(MPR121, ENABLE);

}

void MPR121_I2C_BufferRead(u8 slaveAddr, u8* buffer, u8 readAddr, u16 NumByteToRead) {
	// ENTR_CRT_SECTION();

	 //While the bus is busy
	while (I2C_GetFlagStatus(MPR121, I2C_FLAG_BUSY));

	 //Send START condition
	I2C_GenerateSTART(MPR121, ENABLE);

	 //Test on EV5 and clear it
	while (!I2C_CheckEvent(MPR121, I2C_EVENT_MASTER_MODE_SELECT));

	 //Send MPU6050 address for write
	I2C_Send7bitAddress(MPR121, slaveAddr, I2C_Direction_Transmitter);

	 //Test on EV6 and clear it
	while (!I2C_CheckEvent(MPR121, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	 //Clear EV6 by setting again the PE bit
	I2C_Cmd(MPR121, ENABLE);

	// Send the MPU6050's internal address to write to
	I2C_SendData(MPR121, readAddr);

	 //Test on EV8 and clear it
	while (!I2C_CheckEvent(MPR121, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	 //Send STRAT condition a second time
	I2C_GenerateSTART(MPR121, ENABLE);

	 //Test on EV5 and clear it
	while (!I2C_CheckEvent(MPR121, I2C_EVENT_MASTER_MODE_SELECT));

	 //Send MPU6050 address for read
	I2C_Send7bitAddress(MPR121, slaveAddr, I2C_Direction_Receiver);

	 //Test on EV6 and clear it
	while (!I2C_CheckEvent(MPR121, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

	 //While there is data to be read
	while (NumByteToRead) {
		if (NumByteToRead == 1) {
			 //Disable Acknowledgement
			I2C_AcknowledgeConfig(MPR121, DISABLE);

			 //Send STOP Condition
			I2C_GenerateSTOP(MPR121, ENABLE);
		}

		 //Test on EV7 and clear it
		if (I2C_CheckEvent(MPR121, I2C_EVENT_MASTER_BYTE_RECEIVED)) {
			 //Read a byte from the MPU6050
			*buffer = I2C_ReceiveData(MPR121);

			 //Point to the next location where the byte read will be saved
			buffer++;

			 //Decrement the read bytes counter
			NumByteToRead--;
		}
	}

	 //Enable Acknowledgement to be ready for another reception
	I2C_AcknowledgeConfig(MPR121, ENABLE);
//  EXT_CRT_SECTION();

}

