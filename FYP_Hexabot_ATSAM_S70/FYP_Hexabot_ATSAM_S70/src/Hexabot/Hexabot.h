/*
 * Hexabot.h
 *
 * Created: 17/05/2016 4:12:00 PM
 *  Author: to300
 */ 



#ifndef HEXABOT_H_
#define HEXABOT_H_
#include <asf.h>
#include <arm_math.h>
#include "../Debug.h"

#define write_SCCB(X, Y) i2cWriteReg(CAMERA_I2C_ADDR,X,Y)
#define write_SCCB_76(X, Y) i2cWriteReg(CAMERA_I2C_ADDR_OV7670,X,Y)
#define CAM_FRAME0_ADDR  BOARD_SDRAM_ADDR
#define CAM_FRAME1_ADDR  BOARD_SDRAM_ADDR+320*240*2 + 0x10;
#define CAM_FRAME_DIF_ADDR  BOARD_SDRAM_ADDR+320*240*2*8


#define A 120.00
#define B 65.00
#define C 70.00
#define HEXABOT_LEG_CYCLE_T 50

typedef struct walk_data_s {
	float movTurn;
	float movDir;
	int stance;
	int hgt;
	int pup;
	int stride;
	int Hexabot_leg_cycle_t;
	int Walk_EN;
	int max_i;
	int i;
	int ret;
	int gaitIndex;
	int standing;
} walk_data;

//typedefs
typedef struct angles_s  {
	float S1;
	float S2;
	float S3;
} angles;

typedef struct XZ_s {
	float X;
	float Z;
} XZ;

//sdram Check
void SdramCheck();

//cameraSetup
void SetupCameraVga();
void SetupCameraRAW();
void SetupCameraC();
void SetupCameraYUVVGA();
void setupcameraLinuxDriver();
void dumpFrame();
void SetupCameraYUVVGA_OV7670();

//servoManagement
int i2cReadReg(uint8_t,uint8_t);
void i2cWriteReg(uint8_t,uint8_t,uint8_t);
void ServoDriverInit(int);
void WriteServo(int,int,float);
void relaxServo(int,int);

//batteryManagement
float getBatVoltage();

//Leg walking functions
XZ calcRotation(float inX, float inZ, float cenX,  float cenZ, float rotAng, int opside, float turn);
int sign(float in);
angles legAngCalc(float x, float y, float z);
void writeLegOut(int leg, float S0, float S1, float S2);

//
void byteToLEDs(uint8_t disp,uint8_t mask);
void calibServos(float*);
void calibServoSpec(float* calData,int Leg,int Svo);

void cmdInterp(uint8_t* cmd,int cmdLen,walk_data* hexabot_walk);

//
void surprise();
#endif /* HEXABOT_H_ */