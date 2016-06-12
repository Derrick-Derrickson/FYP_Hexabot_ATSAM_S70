/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <Hexabot/Hexabot.h>
#include <asf.h>
#include "../Debug.h"
#include "DW1000.h"
#include <Hexabot/Hexabot_Cmd.h>
#include "libjpeg/libjpeg.h"



char buf [20];


//define task functions
void vTask1 (void*);
void LegControlTask (void*);
void CLItask(void*);

//global variables
int isi_frames_done = 0;

char CLIbuf[100];
int CLIbufIndex = 0;
walk_data hexabot_walk;
int VerboseMode = 0;

int main (void)
{
		
	
	board_init();
	sendDebugString("BOARD INITIALIZATION - FINISHED\n");
	sendDebugString("RTOS TASK INITIALIZATION - STARTED\n");
	
	xTaskCreate(vTask1,"TASK1",400,NULL,4,NULL);
	xTaskCreate(LegControlTask,"LEGCTRLTASK",1600,NULL,3,NULL);
	xTaskCreate(CLItask,"CLITASK",1600,NULL,2,NULL);
	sendDebugString("TASK1 DEFINITION - FINISHED\n");
	
	sendDebugString("STARTING RTOS\n");
	vTaskStartScheduler();
	sendDebugString("RTOS HAS RETURNED. THIS SHOULD EVER HAPPEN. EXTREME ERROR\n");
	return 0;
	/* Insert application code here, after the board has been initialized. */
}

void vTask1 (void* pvParameters) {
	sendDebugString("TASK1 INITIALIZATION - STARTED\n");
	TickType_t xLastWakeTime = xTaskGetTickCount();
	int tg = 1;
	uint8_t T = 0;
	int cleanTest = 1;
	int testCountPass = 0;
	char Qbuf[20];
	char buf[20];
	pio_set(LED0);
	int testCountFail = 0;
	sendDebugString("TASK1 INITIALIZATION - FINISHED | ENTERING INFINITE LOOP\n");
	
	for(;;) {
				if(tg) {
					pio_set(LED0);
					tg = !tg;
				}
				else {
					pio_clear(LED0);	
					tg = !tg;
				}	
				vTaskDelay(1000);
	}
}

void LegControlTask (void* pvParameters) {
	sendDebugString("LEG CONTROL TASK INITIALIZATION - STARTED\n");
	
	float	ofst0;
	float	ofst1;
	float	ofst2;
	float	ofst3;
	float	ofst4;
	float	ofst5;
	
	XZ		xzS0;
	XZ		xzS1;
	XZ		xzS2;
	XZ		xzS3;
	XZ		xzS4;
	XZ		xzS5;
	
	angles	Ang0;
	angles	Ang1;
	angles	Ang2;
	angles	Ang3;
	angles	Ang4;
	angles	Ang5;
	
	hexabot_walk.movTurn = 0;
	hexabot_walk.movDir = 0;
	hexabot_walk.stance = 120;
	hexabot_walk.hgt = 100;
	hexabot_walk.pup = 50;
	hexabot_walk.stride = 250;
	hexabot_walk.Walk_EN = 0;
	hexabot_walk.Hexabot_leg_cycle_t = 20;
	
	sendDebugString("LEG CONTROL TASK INITIALIZATION - FINISHED | ENTERING INFINITE LOOP\n");
	
	for(;;) {
		pio_set(LED7);
		if(hexabot_walk.Walk_EN) {
		  ofst0 = ((float)hexabot_walk.i+(0*(hexabot_walk.Hexabot_leg_cycle_t/6)))/(hexabot_walk.Hexabot_leg_cycle_t)*2.0*M_PI;
		  ofst1 = ((float)hexabot_walk.i+(1*(hexabot_walk.Hexabot_leg_cycle_t/6)))/(hexabot_walk.Hexabot_leg_cycle_t)*2.0*M_PI;
		  ofst2 = ((float)hexabot_walk.i+(2*(hexabot_walk.Hexabot_leg_cycle_t/6)))/(hexabot_walk.Hexabot_leg_cycle_t)*2.0*M_PI;
		  ofst3 = ((float)hexabot_walk.i+(3*(hexabot_walk.Hexabot_leg_cycle_t/6)))/(hexabot_walk.Hexabot_leg_cycle_t)*2.0*M_PI;
		  ofst4 = ((float)hexabot_walk.i+(4*(hexabot_walk.Hexabot_leg_cycle_t/6)))/(hexabot_walk.Hexabot_leg_cycle_t)*2.0*M_PI;
		  ofst5 = ((float)hexabot_walk.i+(5*(hexabot_walk.Hexabot_leg_cycle_t/6)))/(hexabot_walk.Hexabot_leg_cycle_t)*2.0*M_PI;
		  
		  xzS0 = calcRotation(hexabot_walk.stance, hexabot_walk.stride*cos(ofst0), hexabot_walk.stance, 0, hexabot_walk.movDir,1,hexabot_walk.movTurn);
		  xzS1 = calcRotation(hexabot_walk.stance, hexabot_walk.stride*cos(ofst1), hexabot_walk.stance, 0, hexabot_walk.movDir,0,hexabot_walk.movTurn);
		  xzS2 = calcRotation(hexabot_walk.stance, hexabot_walk.stride*cos(ofst2), hexabot_walk.stance, 0, hexabot_walk.movDir,1,hexabot_walk.movTurn);
		  xzS3 = calcRotation(hexabot_walk.stance, hexabot_walk.stride*cos(ofst3), hexabot_walk.stance, 0, hexabot_walk.movDir,0,hexabot_walk.movTurn);
		  xzS4 = calcRotation(hexabot_walk.stance, hexabot_walk.stride*cos(ofst4), hexabot_walk.stance, 0, hexabot_walk.movDir,1,hexabot_walk.movTurn);
		  xzS5 = calcRotation(hexabot_walk.stance, hexabot_walk.stride*cos(ofst5), hexabot_walk.stance, 0, hexabot_walk.movDir,0,hexabot_walk.movTurn);

		  Ang0 = legAngCalc(xzS0.X,  (sin(ofst0) < 0)?-hexabot_walk.hgt:(hexabot_walk.pup*sin(ofst0)-hexabot_walk.hgt)  ,xzS0.Z);
		  Ang1 = legAngCalc(xzS1.X,  (sin(ofst1) < 0)?-hexabot_walk.hgt:(hexabot_walk.pup*sin(ofst1)-hexabot_walk.hgt)  ,xzS1.Z);
		  Ang2 = legAngCalc(xzS2.X,  (sin(ofst2) < 0)?-hexabot_walk.hgt:(hexabot_walk.pup*sin(ofst2)-hexabot_walk.hgt)  ,xzS2.Z);
		  Ang3 = legAngCalc(xzS3.X,  (sin(ofst3) < 0)?-hexabot_walk.hgt:(hexabot_walk.pup*sin(ofst3)-hexabot_walk.hgt)  ,xzS3.Z);
		  Ang4 = legAngCalc(xzS4.X,  (sin(ofst4) < 0)?-hexabot_walk.hgt:(hexabot_walk.pup*sin(ofst4)-hexabot_walk.hgt)  ,xzS4.Z);
		  Ang5 = legAngCalc(xzS5.X,  (sin(ofst5) < 0)?-hexabot_walk.hgt:(hexabot_walk.pup*sin(ofst5)-hexabot_walk.hgt)  ,xzS5.Z);
		  
		  writeLegOut(0,Ang0.S1,Ang0.S2,Ang0.S3);
		  writeLegOut(1,Ang1.S1,Ang1.S2,Ang1.S3);
		  writeLegOut(2,Ang2.S1,Ang2.S2,Ang2.S3);
		  writeLegOut(3,Ang3.S1,Ang3.S2,Ang3.S3);
		  writeLegOut(4,Ang4.S1,Ang4.S2,Ang4.S3);
		  writeLegOut(5,Ang5.S1,Ang5.S2,Ang5.S3);
		  hexabot_walk.i++;
		  if(hexabot_walk.i > hexabot_walk.max_i) hexabot_walk.Walk_EN = 0;
		  pio_clear(LED7);
		}
		else hexabot_walk.i = 0;
		  vTaskDelay(20);
	}
}

void CLItask(void* pvParameters) {
	sendDebugString("CLI TASK INITIALIZATION - STARTED\n");
	memset(CLIbuf,0,100);
	char* BaseCmd;
	sendDebugString("CLI TASK INITIALIZATION - FINISHED | ENTERING INFINITE LOOP\n");
	sendDebugString("COMMAND LINE STARTED\n");
	sendDebugString("\n");
	sendDebugString("\n");
	
	
	sendDebugString("FYP_Hexabot_ATSAMS70_MELLATRON9000>");
	for(;;) {
			
		if(CLIbuf[CLIbufIndex-1] ==  '\n') {
			CLIbufIndex=0;
			//sendDebugString(CLIbuf);
			BaseCmd = strtok(CLIbuf," ");
			
			if(!strcmp(BaseCmd,"led")) cmdLED( atoi(strtok(NULL," "))  , atoi(strtok(NULL," ")) );
			
			else if(!strcmp(BaseCmd,"manusvo"))  cmdServoMan(atoi(strtok(NULL," ")) , atoi(strtok(NULL," ")) , atoi(strtok(NULL," ")));
			
			else if(!strcmp(BaseCmd,"batvolt\n")) cmdBatVolt();
			
			else if(!strcmp(BaseCmd,"dumpimg\n")) dumpFrame();
			
			else if(!strcmp(BaseCmd,"walk")) cmdWalk(atoi(strtok(NULL," ")));
			
			else if(!strcmp(BaseCmd,"walkcytime")) hexabot_walk.Hexabot_leg_cycle_t = atoi(strtok(NULL," "));
			
			else if(!strcmp(BaseCmd,"verbose")) VerboseMode = atoi(strtok(NULL," "));
			
			else if(!strcmp(BaseCmd,"dumpimg\n")) cmdJPEGEncodeFrame();
			
			sendDebugString("FYP_Hexabot_ATSAMS70_MELLATRON9000>");
			memset(CLIbuf,0,100);
			//Figure out function, then commit;
		}
		
		vTaskDelay(1);
	}
	
	
}

	/* ######################################
	   ######################################
			 	INTERUPT HANDLERS
	   ######################################
	   ###################################### */
	
void ISI_Handler(void) {
	uint32_t status,imr;
	status = ISI->ISI_SR;
	imr = ISI->ISI_IMR;
	//pio_set(LED3);
	isi_frames_done++;
}

void UART4_Handler(void) {
	uint32_t imr = ISI->ISI_IMR;
	char temp;
	uart_read(UART4,&temp);
	CLIbuf[CLIbufIndex] = temp;
	CLIbufIndex++;
	
}
