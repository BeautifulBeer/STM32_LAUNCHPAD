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

	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_TOUCHTH_0, MPR121_TH_TOUCH);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_RELEASETH_0, MPR121_TH_RELEASE);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_TOUCHTH_1, MPR121_TH_TOUCH);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_RELEASETH_1, MPR121_TH_RELEASE);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_TOUCHTH_2, MPR121_TH_TOUCH);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_RELEASETH_2, MPR121_TH_RELEASE);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_TOUCHTH_3, MPR121_TH_TOUCH);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_RELEASETH_3, MPR121_TH_RELEASE);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_TOUCHTH_4, MPR121_TH_TOUCH);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_RELEASETH_4, MPR121_TH_RELEASE);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_TOUCHTH_5, MPR121_TH_TOUCH);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_RELEASETH_5, MPR121_TH_RELEASE);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_TOUCHTH_6, MPR121_TH_TOUCH);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_RELEASETH_6, MPR121_TH_RELEASE);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_TOUCHTH_7, MPR121_TH_TOUCH);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_RELEASETH_7, MPR121_TH_RELEASE);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_TOUCHTH_8, MPR121_TH_TOUCH);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_RELEASETH_8, MPR121_TH_RELEASE);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_TOUCHTH_9, MPR121_TH_TOUCH);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_RELEASETH_9, MPR121_TH_RELEASE);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_TOUCHTH_10, MPR121_TH_TOUCH);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_RELEASETH_10, MPR121_TH_RELEASE);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_TOUCHTH_11, MPR121_TH_TOUCH);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_RELEASETH_11, MPR121_TH_RELEASE);

	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_MHDR, 0x01);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_NHDR, 0x01);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_NCLR, 0x00);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_FDLR, 0x00);

	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_MHDF, 0x01);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_NHDF, 0x01);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_NCLF, 0xFF);
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_FDLF, 0x02);

	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_CONFIG_FILTER, 0x04); // 0.5uS encoding, 1ms period
	//MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_AUTOCONFIG0, 0x00);
	//MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_AUTOCONFIG1, 0x00);
	//MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_UPLIMIT, 0x00);
	//MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_LOWLIMIT, 0x00);
	//MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_TARGETLIMIT, 0x00);
	//MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_ECR, 0x0C);



//  writeRegister(MPR121_AUTOCONFIG0, 0x8F);

//  writeRegister(MPR121_UPLIMIT, 150);
//  writeRegister(MPR121_TARGETLIMIT, 100); // should be ~400 (100 shifted)
//  writeRegister(MPR121_LOWLIMIT, 50);
	// enable all electrodes
	MPR121_I2C_ByteWrite(MPR121_I2CADDR_DEFAULT, MPR121_ECR, 0x0C); // start with first 5 bits of baseline tracking

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

	return buffer[0];
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
	while (I2C_GetFlagStatus(MPR121, I2C_FLAG_BUSY));
	I2C_AcknowledgeConfig(MPR121, ENABLE);
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
	I2C_AcknowledgeConfig(MPR121, DISABLE);
	//Send STOP condition
	I2C_GenerateSTOP(MPR121, ENABLE);

}

void MPR121_I2C_BufferRead(u8 slaveAddr, u8* buffer, u8 readAddr, u16 NumByteToRead) {
	while (I2C_GetFlagStatus(MPR121, I2C_FLAG_BUSY));
	// ENTR_CRT_SECTION();
	I2C_AcknowledgeConfig(MPR121, ENABLE);
	 //Send START condition
	I2C_GenerateSTART(MPR121, ENABLE);
	 //Test on EV5 and clear it
	while (!I2C_CheckEvent(MPR121, I2C_EVENT_MASTER_MODE_SELECT));
	 //Send MPU6050 address for write
	I2C_Send7bitAddress(MPR121, slaveAddr, I2C_Direction_Transmitter);
	 //Test on EV6 and clear it
	while(!I2C_CheckEvent(MPR121, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	//Send register address
	I2C_SendData(MPR121, readAddr);
	//Test on EV8 and clear it
	while(!I2C_CheckEvent(MPR121, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	//Send STRAT condition a second time
	I2C_GenerateSTART(MPR121, ENABLE);
	//Test on EV5 and clear it
	while (!I2C_CheckEvent(MPR121, I2C_EVENT_MASTER_MODE_SELECT));
	//Send MPU6050 address for read
	I2C_Send7bitAddress(MPR121, slaveAddr, I2C_Direction_Receiver);
	//Test on EV6 and clear it
	while(!I2C_CheckEvent(MPR121, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	while(!I2C_CheckEvent(MPR121, I2C_EVENT_MASTER_BYTE_RECEIVED));
	buffer[0] = I2C_ReceiveData(MPR121);
	I2C_AcknowledgeConfig(MPR121, DISABLE);
	I2C_GenerateSTOP(MPR121, ENABLE);
	if(NumByteToRead == 2){
		while(!I2C_CheckEvent(MPR121, I2C_EVENT_MASTER_BYTE_RECEIVED));
		buffer[1] = I2C_ReceiveData(MPR121);
	}
//  EXT_CRT_SECTION();
}


