/*
 * Hexabot.h
 *
 * Created: 17/05/2016 4:12:00 PM
 *  Author: to300
 */ 



#ifndef HEXABOT_H_
#define HEXABOT_H_
#include <asf.h>
#include <math.h>
#include "../Debug.h"

#define write_SCCB(X, Y) i2cWriteReg(CAMERA_I2C_ADDR,X,Y)

//sdram Check
void SdramCheck();

//cameraSetup
void SetupCameraVga();
void SetupCameraRAW();

//servoManagement
int i2cReadReg(uint8_t,uint8_t);
void i2cWriteReg(uint8_t,uint8_t,uint8_t);
void ServoDriverInit(int);
void WriteServo(int,int,float);


#endif /* HEXABOT_H_ */