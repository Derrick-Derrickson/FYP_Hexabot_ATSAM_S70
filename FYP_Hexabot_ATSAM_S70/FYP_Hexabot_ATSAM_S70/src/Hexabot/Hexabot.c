/*
 * Hexabot.c
 *
 * Created: 17/05/2016 4:11:50 PM
 *  Author: to300
 */ 
#include "Hexabot/Hexabot.h"
void SdramCheck() {
	int T=0;
	int cleanTest = 1;
	char buf[20];
	for(int i = 0;i<BOARD_SDRAM_ADDR_NUM;i++) {
		((uint16_t*)BOARD_SDRAM_ADDR)[i] = T;
		T++;
	}
	
	for(int i = 0;i<BOARD_SDRAM_ADDR_NUM;i++) {
		if(((uint16_t*)BOARD_SDRAM_ADDR)[i] != T){
			sprintf(buf,"MEM ERROR AT 0x%x\n",i);
			sendDebugString(buf);
			cleanTest = 0;
		}
		T++;
	}
	if(cleanTest) sendDebugString("SDRAM FULL CHECK COMPLETE");
}

void i2cWriteReg(uint8_t chipin,uint8_t reg,uint8_t val) {
	int writeVal = val;
	twihs_packet_t ledApacket = {
		.addr[0] = reg,
		.addr_length = 1,
		.chip = (chipin),
		.buffer = &val,
	.length = 1 };
	
	if(twihs_master_write(TWIHS0,&ledApacket) != TWIHS_SUCCESS) {
		sendDebugString("I2C ERR!\n");
	}
}

int i2cReadReg(uint8_t chipin,uint8_t reg) {
	int retVal = 0;
	twihs_packet_t ledApacket = {
		.addr[0] = reg,
		.addr_length = 1,
		.chip = (chipin),
		.buffer = &retVal,
	.length = 1 };
	twihs_master_read(TWIHS0,&ledApacket);
	return retVal;
}

void ServoDriverInit(int ServoAddr) {
	char buf[20];
	sprintf(buf,"%x, ",i2cReadReg(ServoAddr,0x00));
	sendDebugString(buf);
	sprintf(buf,"%x, ",i2cReadReg(ServoAddr,0x01));
	sendDebugString(buf);
	sprintf(buf,"%x, ",i2cReadReg(ServoAddr,0x1E));
	sendDebugString(buf);
	sprintf(buf,"%x, ",i2cReadReg(ServoAddr,0xFE));
	sendDebugString(buf);
	
	delay_ms(1);
	i2cWriteReg(ServoAddr,0x00,0x01<<4);
	delay_ms(2);
	i2cWriteReg(ServoAddr,0xFE,0x80);
	delay_ms(2);
	i2cWriteReg(ServoAddr,0x00,0x00);
	
	i2cWriteReg(ServoAddr,0x00,0x01<<4);
	i2cWriteReg(ServoAddr,0x01,0x04);
	i2cWriteReg(ServoAddr,0x00,0x00);
	delay_ms(2);
	i2cWriteReg(ServoAddr,0x00,0x01<<7);
	sendDebugString("SERVO DRIVER SETUP COMPLEATE\n");
}

void WriteServo(int i2cAddr,int baseReg,float angle) 
{
	 uint16_t stop = (int)((1.00+(angle/180.00))*(4095.00/(20.00)));
	
	i2cWriteReg(i2cAddr,baseReg,0x01);
	i2cWriteReg(i2cAddr,baseReg+1,0x00);
	i2cWriteReg(i2cAddr,baseReg+2,stop);
	i2cWriteReg(i2cAddr,baseReg+3,stop >> 8);
	
}


void SetupCameraVga() {
	write_SCCB(0x12, 0x80);
	write_SCCB(0x11, 0x83);
	write_SCCB(0x6b, 0x4a);
	write_SCCB(0x6a, 0x3e);
	write_SCCB(0x3b, 0x09);
	write_SCCB(0x13, 0xe0);
	write_SCCB(0x01, 0x80);
	write_SCCB(0x02, 0x80);
	write_SCCB(0x00, 0x00);
	write_SCCB(0x10, 0x00);
	write_SCCB(0x13, 0xe5);	//
	write_SCCB(0x39, 0x43); //50 for 30fps
	write_SCCB(0x38, 0x12); //92 for 30fps
	write_SCCB(0x37, 0x00);
	write_SCCB(0x35, 0x91); //81 for 30fps
	write_SCCB(0x0e, 0xa0);
	write_SCCB(0x1e, 0x04);	//
	write_SCCB(0xa8, 0x80);
	write_SCCB(0x12, 0x44);
	write_SCCB(0x04, 0x00);
	write_SCCB(0x0c, 0x04);
	write_SCCB(0x0d, 0x80);
	write_SCCB(0x18, 0xc6);
	write_SCCB(0x17, 0x26);
	write_SCCB(0x32, 0xad);
	write_SCCB(0x03, 0x00);
	write_SCCB(0x1a, 0x3d);
	write_SCCB(0x19, 0x01);
	write_SCCB(0x3f, 0xa6);
	write_SCCB(0x14, 0x2e);
	write_SCCB(0x15, 0x02);
	write_SCCB(0x41, 0x00);
	write_SCCB(0x42, 0x08);
	//
	write_SCCB(0x1b, 0x00);
	write_SCCB(0x16, 0x06);
	write_SCCB(0x33, 0xe2); //c0 for internal regulator
	write_SCCB(0x34, 0xbf);
	write_SCCB(0x96, 0x04);
	write_SCCB(0x3a, 0x00);
	write_SCCB(0x8e, 0x00);
	//
	write_SCCB(0x3c, 0x77);
	write_SCCB(0x8b, 0x06);
	write_SCCB(0x94, 0x88);
	write_SCCB(0x95, 0x88);
	write_SCCB(0x40, 0xd1);
	write_SCCB(0x29, 0x3f); //2f for internal regulator
	write_SCCB(0x0f, 0x42);
	//
	write_SCCB(0x3d, 0x90);
	write_SCCB(0x69, 0x40);
	write_SCCB(0x5c, 0xb9);
	write_SCCB(0x5d, 0x96);
	write_SCCB(0x5e, 0x10);
	write_SCCB(0x59, 0xc0);
	write_SCCB(0x5a, 0xaf);
	write_SCCB(0x5b, 0x55);
	write_SCCB(0x43, 0xf0);
	write_SCCB(0x44, 0x10);
	write_SCCB(0x45, 0x68);
	write_SCCB(0x46, 0x96);
	write_SCCB(0x47, 0x60);
	write_SCCB(0x48, 0x80);
	write_SCCB(0x5f, 0xe0);
	write_SCCB(0x60, 0x8c); //0c for advanced AWB (related to lens)
	write_SCCB(0x61, 0x20);	write_SCCB(0xa5, 0xd9);
	write_SCCB(0xa4, 0x74);
	write_SCCB(0x8d, 0x02);
	write_SCCB(0x13, 0xe7);
	//
	write_SCCB(0x4f, 0xb7);
	write_SCCB(0x50, 0x2e);
	write_SCCB(0x51, 0x09);
	write_SCCB(0x52, 0x1f);
	write_SCCB(0x53, 0xb1);
	write_SCCB(0x54, 0x12);
	write_SCCB(0x55, 0x06);
	write_SCCB(0x56, 0x55);
	write_SCCB(0x57, 0xdb);
	write_SCCB(0x58, 0x77);
	//
	write_SCCB(0x8c, 0x23);
	write_SCCB(0x3e, 0x02);
	write_SCCB(0xa9, 0xb8);
	write_SCCB(0xaa, 0x92);
	write_SCCB(0xab, 0x0a);
	//
	write_SCCB(0x8f, 0xdf);
	write_SCCB(0x90, 0x00);
	write_SCCB(0x91, 0x00);
	write_SCCB(0x9f, 0x00);
	write_SCCB(0xa0, 0x00);
	write_SCCB(0x3a, 0x01);
	//
	write_SCCB(0x24, 0x70);
	write_SCCB(0x25, 0x64);
	write_SCCB(0x26, 0xc3);
	//
	write_SCCB(0x2a, 0x00); //10 for 50Hz
	write_SCCB(0x2b, 0x00); //40 for 50Hz
	//
	//gamma
	write_SCCB(0x6c, 0x40);
	write_SCCB(0x6d, 0x30);
	write_SCCB(0x6e, 0x4b);
	write_SCCB(0x6f, 0x60);
	write_SCCB(0x70, 0x70);
	write_SCCB(0x71, 0x70);
	write_SCCB(0x72, 0x70);
	write_SCCB(0x73, 0x70);
	write_SCCB(0x74, 0x60);
	write_SCCB(0x75, 0x60);
	write_SCCB(0x76, 0x50);
	write_SCCB(0x77, 0x48);
	write_SCCB(0x78, 0x3a);
	write_SCCB(0x79, 0x2e);
	write_SCCB(0x7a, 0x28);
	write_SCCB(0x7b, 0x22);
	write_SCCB(0x7c, 0x04);
	write_SCCB(0x7d, 0x07);
	write_SCCB(0x7e, 0x10);
	write_SCCB(0x7f, 0x28);
	write_SCCB(0x80, 0x36);
	write_SCCB(0x81, 0x44);
	write_SCCB(0x82, 0x52);
	write_SCCB(0x83, 0x60);
	write_SCCB(0x84, 0x6c);
	write_SCCB(0x85, 0x78);
	write_SCCB(0x86, 0x8c);
	write_SCCB(0x87, 0x9e);
	write_SCCB(0x88, 0xbb);
	write_SCCB(0x89, 0xd2);
	write_SCCB(0x8a, 0xe6);
	//
	write_SCCB(0x09, 0x11);
	write_SCCB(0x09, 0x01);
	
}

void SetupCameraRAW() {
	write_SCCB(0x12, 0x80);
	write_SCCB(0x11, 0x81);
	write_SCCB(0x6b, 0x4a);
	write_SCCB(0x3b, 0x01);
	write_SCCB(0x6a, 0x83);
	write_SCCB(0x13, 0xe2);
	write_SCCB(0x10, 0x00);
	write_SCCB(0x00, 0x00);
	write_SCCB(0x01, 0x80);
	write_SCCB(0x02, 0x80);
	write_SCCB(0x13, 0xe7);	write_SCCB(0x39, 0x50);
	write_SCCB(0x38, 0x93);
	write_SCCB(0x37, 0x00);
	write_SCCB(0x35, 0x81);
	write_SCCB(0x0e, 0xa0);
	//
	write_SCCB(0xa8, 0x80);
	write_SCCB(0x12, 0x05);
	write_SCCB(0x04, 0x00);
	write_SCCB(0x0c, 0x00);	write_SCCB(0x0d, 0x00);
	write_SCCB(0x18, 0xbb);
	write_SCCB(0x17, 0x1b);
	write_SCCB(0x32, 0xa4);
	write_SCCB(0x19, 0x01);
	write_SCCB(0x1a, 0x81);
	write_SCCB(0x03, 0x12);
	//
	write_SCCB(0x1b, 0x00);
	write_SCCB(0x16, 0x07);
	write_SCCB(0x33, 0xe2); //c0 for internal regulator
	write_SCCB(0x34, 0xbf);
	write_SCCB(0x41, 0x00);
	write_SCCB(0x96, 0x04);
	//
	write_SCCB(0x3d, 0x19);
	write_SCCB(0x69, 0x40);
	write_SCCB(0x3a, 0x0d);
	write_SCCB(0x8e, 0x00);
	//
	write_SCCB(0x3c, 0x73);
	write_SCCB(0x8f, 0xdf);
	write_SCCB(0x8b, 0x06);
	write_SCCB(0x8c, 0x20);
	write_SCCB(0x94, 0x88);
	write_SCCB(0x95, 0x88);
	write_SCCB(0x40, 0xc1);
	write_SCCB(0x29, 0x3f); //2f for internal regulator
	write_SCCB(0x0f, 0x42);
	write_SCCB(0xa5, 0x80);
	write_SCCB(0x1e, 0x04);
	write_SCCB(0xa9, 0xb8);
	write_SCCB(0xaa, 0x92);
	write_SCCB(0xab, 0x0a);
	//
	write_SCCB(0x24, 0x68);
	write_SCCB(0x25, 0x5c);
	write_SCCB(0x26, 0xc3);
	write_SCCB(0x14, 0x2e);}