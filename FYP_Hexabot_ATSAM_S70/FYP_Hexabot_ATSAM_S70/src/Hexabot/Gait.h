/*
 * Gait.h
 *
 * Created: 14/08/2016 11:45:07 PM
 *  Author: to300
 */ 


#ifndef GAIT_H_
#define GAIT_H_
#include "Hexabot/Hexabot.h"
#include "Hexabot/Hexabot_Cmd.h"
#define STAND_UP_START_HGT 75
#define STAND_UP_TIME 30.00

void Gait0( float* ofst,XZ* xzS,angles* Ang, walk_data* hexabot_walk);

void Gait1( float* ofst,XZ* xzS,angles* Ang, walk_data* hexabot_walk);

void Gait2( float* ofst,XZ* xzS,angles* Ang, walk_data* hexabot_walk);

void standUp( float* ofst,XZ* xzS,angles* Ang, walk_data* hexabot_walk);

void sitDown( float* ofst,XZ* xzS,angles* Ang, walk_data* hexabot_walk);
#endif /* GAIT_H_ */