/*
 * Hexabot_Cmd.h
 *
 * Created: 11/06/2016 1:03:14 PM
 *  Author: to300
 */ 


#ifndef HEXABOT_CMD_H_
#define HEXABOT_CMD_H_
#include <string.h>
#include <asf.h>
#include <../Debug.h>

void cmdLED(int L, int onOff);

void cmdServoMan(int L,int S ,int angle);

void cmdBatVolt();

void cmdDumpImage(int dumpLoc);

void cmdWalk(int maxi);

void cmdTestDW1000();

void cmdDWMsend(char* tosend);

void cmdOverrideLEDDWM1000();

void cmdWriteTestDW1000(uint64_t toRW);

void cmdRelaxSvo(int,int);

void cmdRelaxAll();
#endif /* HEXABOT_CMD_H_ */