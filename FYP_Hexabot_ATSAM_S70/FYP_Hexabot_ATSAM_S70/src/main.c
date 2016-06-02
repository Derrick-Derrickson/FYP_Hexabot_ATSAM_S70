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

char buf [20];
volatile int* SYST_RVR = (int*)0xE000E014;
volatile uint16_t* SDRAMstart = (uint16_t*)BOARD_SDRAM_ADDR;

void vTask1 (void*);

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	//*SYST_RVR = 2;
	//final i2C init
		
	
	board_init();
	sendDebugString("BOARD INIT COMPLETE\n");
	//DW1000_writeReg(0x26,DW1000_SUB,0x08,0xF0,1);
	//DW1000_writeReg(0x26,DW1000_SUB,0x0C,0xFF,1);
	xTaskCreate(vTask1,"TASK1",400,NULL,2,NULL);
	sendDebugString("STARTING RTOS\n");
	vTaskStartScheduler();
	sendDebugString("MEMORY ERROR\n");
	return 0;
	/* Insert application code here, after the board has been initialized. */
}

void vTask1 (void* pvParameters) {
	
	sendDebugString("STARTED TASK 1\n");
	TickType_t xLastWakeTime = xTaskGetTickCount();
	int tg = 1;
	uint8_t T = 0;
	int cleanTest = 1;
	int testCountPass = 0;
	char Qbuf[20];
	char buf[20];
	pio_set(LED0);
	int testCountFail = 0;
	for(;;) {
		//sendDebugString("TASK1 RUNNING\n");
		
				if(tg) {
				pio_set(LED0);
					
				
					
				
				tg = !tg;
				}
				
				
				
				else {
				pio_clear(LED0);	
					
					
					
				tg = !tg;
				}
				
				vTaskDelayUntil(&xLastWakeTime,400);
	}
	
}