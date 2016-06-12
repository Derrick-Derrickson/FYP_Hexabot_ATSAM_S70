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

void cmdDumpImage();

void cmdWalk(int maxi);

#endif /* HEXABOT_CMD_H_ */