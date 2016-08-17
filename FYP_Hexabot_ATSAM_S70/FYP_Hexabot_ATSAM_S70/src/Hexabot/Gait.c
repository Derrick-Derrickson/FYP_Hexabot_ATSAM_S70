/*
* Gait.c
*
* Created: 14/08/2016 11:44:45 PM
*  Author: to300
*/
#include "Gait.h"

void Gait0( float* ofst,XZ* xzS,angles* Ang, walk_data* hexabot_walk) {

	ofst[0] = ((float)hexabot_walk.i+(0*(hexabot_walk.Hexabot_leg_cycle_t/6)))/(hexabot_walk.Hexabot_leg_cycle_t)*2.0*M_PI;
	ofst[1] = ((float)hexabot_walk.i+(1*(hexabot_walk.Hexabot_leg_cycle_t/6)))/(hexabot_walk.Hexabot_leg_cycle_t)*2.0*M_PI;
	ofst[2] = ((float)hexabot_walk.i+(2*(hexabot_walk.Hexabot_leg_cycle_t/6)))/(hexabot_walk.Hexabot_leg_cycle_t)*2.0*M_PI;
	ofst[3] = ((float)hexabot_walk.i+(3*(hexabot_walk.Hexabot_leg_cycle_t/6)))/(hexabot_walk.Hexabot_leg_cycle_t)*2.0*M_PI;
	ofst[4] = ((float)hexabot_walk.i+(4*(hexabot_walk.Hexabot_leg_cycle_t/6)))/(hexabot_walk.Hexabot_leg_cycle_t)*2.0*M_PI;
	ofst[5] = ((float)hexabot_walk.i+(5*(hexabot_walk.Hexabot_leg_cycle_t/6)))/(hexabot_walk.Hexabot_leg_cycle_t)*2.0*M_PI;
	
	xzS[0] = calcRotation(hexabot_walk.stance, hexabot_walk.stride*cos(ofst[0]), hexabot_walk.stance, 0, hexabot_walk.movDir,1,hexabot_walk.movTurn);
	xzS[1] = calcRotation(hexabot_walk.stance, hexabot_walk.stride*cos(ofst[1]), hexabot_walk.stance, 0, hexabot_walk.movDir,0,hexabot_walk.movTurn);
	xzS[2] = calcRotation(hexabot_walk.stance, hexabot_walk.stride*cos(ofst[2]), hexabot_walk.stance, 0, hexabot_walk.movDir,1,hexabot_walk.movTurn);
	xzS[3] = calcRotation(hexabot_walk.stance, hexabot_walk.stride*cos(ofst[3]), hexabot_walk.stance, 0, hexabot_walk.movDir,0,hexabot_walk.movTurn);
	xzS[4] = calcRotation(hexabot_walk.stance, hexabot_walk.stride*cos(ofst[4]), hexabot_walk.stance, 0, hexabot_walk.movDir,1,hexabot_walk.movTurn);
	xzS[5] = calcRotation(hexabot_walk.stance, hexabot_walk.stride*cos(ofst[5]), hexabot_walk.stance, 0, hexabot_walk.movDir,0,hexabot_walk.movTurn);

	Ang[0] = legAngCalc(xzS[0].X,  (sin(ofst[0]) < 0)?-hexabot_walk.hgt:(hexabot_walk.pup*sin(ofst[0])-hexabot_walk.hgt)  ,xzS[0].Z);
	Ang[1] = legAngCalc(xzS[1].X,  (sin(ofst[1]) < 0)?-hexabot_walk.hgt:(hexabot_walk.pup*sin(ofst[1])-hexabot_walk.hgt)  ,xzS[1].Z);
	Ang[2] = legAngCalc(xzS[2].X,  (sin(ofst[2]) < 0)?-hexabot_walk.hgt:(hexabot_walk.pup*sin(ofst[2])-hexabot_walk.hgt)  ,xzS[2].Z);
	Ang[3] = legAngCalc(xzS[3].X,  (sin(ofst[3]) < 0)?-hexabot_walk.hgt:(hexabot_walk.pup*sin(ofst[3])-hexabot_walk.hgt)  ,xzS[3].Z);
	Ang[4] = legAngCalc(xzS[4].X,  (sin(ofst[4]) < 0)?-hexabot_walk.hgt:(hexabot_walk.pup*sin(ofst[4])-hexabot_walk.hgt)  ,xzS[4].Z);
	Ang[5] = legAngCalc(xzS[5].X,  (sin(ofst[5]) < 0)?-hexabot_walk.hgt:(hexabot_walk.pup*sin(ofst[5])-hexabot_walk.hgt)  ,xzS[5].Z);
	
}

void standUp()