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

char buf [20];
volatile int* SYST_RVR = (int*)0xE000E014;
volatile uint32_t* SDRAMstart = (uint32_t*)BOARD_SDRAM_ADDR;

void vTask1 (void*);

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	//*SYST_RVR = 2;
	//final i2C init
		
	
	board_init();
	sendDebugString("BOARD INIT COMPLETE\n");
	
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
	int T = 0;
	for(;;) {
		sendDebugString("TASK1 RUNNING\n");
		
				if(tg) {
				pio_set(LED0);
					
				WriteServo(L0_S0,0);
				
				tg = !tg;
				}
				
				
				else {
				pio_clear(LED0);	
				
				WriteServo(L0_S0,180);
				
				tg = !tg;
				T++;
				}
				
				vTaskDelayUntil(&xLastWakeTime,1000);
	}
	
}