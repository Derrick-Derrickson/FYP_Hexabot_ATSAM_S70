/*
 * Hexabot_Cmd.c
 *
 * Created: 11/06/2016 1:03:02 PM
 *  Author: to300
 */ 
#include <Hexabot/Hexabot_Cmd.h>
#include <Hexabot/Hexabot.h>

void cmdLED(int L, int onOff) {
	extern int VerboseMode;
	char buf[100];
	
	switch(L) {
		case 0:
			if(onOff) pio_set(LED0);
			else pio_clear(LED0);
		break;
		
		case 1:
			if(onOff) pio_set(LED1);
			else pio_clear(LED1);
		break;
		
		case 2:
			if(onOff) pio_set(LED2);
			else pio_clear(LED2);
		break;
		
		case 3:
			if(onOff) pio_set(LED3);
			else pio_clear(LED3);
		break;
		
		case 4:
			if(onOff) pio_set(LED4);
			else pio_clear(LED4);
		break;
		
		case 5:
			if(onOff) pio_set(LED5);
			else pio_clear(LED5);
		break;
		
		case 6:
			if(onOff) pio_set(LED6);
			else pio_clear(LED6);
		break;
		
		case 7:
			if(onOff) pio_set(LED7);
			else pio_clear(LED7);
		break;
		
		case 9:
			if(onOff) {
				pio_set(LED0);
				pio_set(LED1);
				pio_set(LED2);
				pio_set(LED3);
				pio_set(LED4);
				pio_set(LED5);
				pio_set(LED6);
				pio_set(LED7);
			}
			else
			{
				 pio_clear(LED0);
				 pio_clear(LED1);
				 pio_clear(LED2);
				 pio_clear(LED3);
				 pio_clear(LED4);
				 pio_clear(LED5);
				 pio_clear(LED6);
				 pio_clear(LED7); 
			}
		break;
		
	}
		if(VerboseMode) {
		sprintf(buf,"LED%d SET TO %d\n",L,onOff);
		sendDebugString(buf);
	}

}

void cmdServoMan(int L,int S ,int angle) {
	extern int VerboseMode;
	char buf[100];
	
	switch (L) {
		
	case 0:
	WriteServo(L0_S0+0x04*S,angle);
	break;
	
	case 1:
	WriteServo(L1_S0+0x04*S,angle);
	break;
	
	case 2:
	WriteServo(L2_S0+0x04*S,angle);
	break;
	
	case 3:
	WriteServo(L3_S0+0x04*S,angle);
	break;
	
	case 4:
	WriteServo(L4_S0+0x04*S,angle);
	break;
	
	case 5:
	WriteServo(L5_S0+0x04*S,angle);
	break;
	}
	
	if(VerboseMode) {
		sprintf(buf,"SERVO LEG:%d,SERVO:%d MOVED TO %d\n",L,S,angle);
		sendDebugString(buf);
	}
	
}

void cmdBatVolt() {
	char buf[100];
	sprintf(buf,"Battery Voltage:%f\n",getBatVoltage());
	sendDebugString(buf);
}

void cmdDumpImage() {
	dumpFrame();
}

void cmdWalk(int maxi) {
	extern walk_data hexabot_walk;
	hexabot_walk.i = 0;
	hexabot_walk.max_i = maxi;
	hexabot_walk.Walk_EN = 1;
}