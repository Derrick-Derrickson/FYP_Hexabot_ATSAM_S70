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
#include <asf.h>
#include "../Debug.h"

volatile int* SYST_RVR = (int*)0xE000E014;
volatile uint32_t* SDRAMstart = (uint32_t*)BOARD_SDRAM_ADDR;


void vTask1 (void*);

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	*SYST_RVR = 2;
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
	char buf [20];
	sendDebugString("STARTED TASK 1\n");
	TickType_t xLastWakeTime = xTaskGetTickCount();
	int tg = 1;
	int T = 0;
	for(;;) {
		sendDebugString("TASK1 RUNNING\n");
		
				if(tg) {
					
				pio_set(PIOA,LED0);
				pio_set(PIOA,LED1);
				pio_set(PIOA,LED2);
				pio_set(PIOB,LED3);
				pio_set(PIOB,LED4);
				pio_set(PIOA,LED5);
				pio_set(PIOA,LED6);
				pio_set(PIOA,LED7);
				
				for(int i = 0;i<3;i++) {
					*(SDRAMstart+0x000300) = 0;
					*(SDRAMstart+0x000200) = 0;
					*(SDRAMstart+0x000100) = 0;
				}
				
				tg = !tg;
				}
				else {
				pio_clear(PIOA,LED0);
				pio_clear(PIOA,LED1);
				pio_clear(PIOA,LED2);
				pio_clear(PIOB,LED3);
				pio_clear(PIOB,LED4);
				pio_clear(PIOA,LED5);
				pio_clear(PIOA,LED6);
				pio_clear(PIOA,LED7);
				
				//pio_set(PIOC,1<<15);
				//pio_clear(PIOC,1<<15);
				sprintf(buf,"%x,%x,%x",*((SDRAMstart+0x000300)),*(SDRAMstart+0x1000200),*(SDRAMstart+0x000100));
				sendDebugString(buf);
				sendDebugString("\n");
				
				//for(int i = 0;i<3;i++) {
				//	 if(SDRAMstart[i] != T+i) sendDebugString("MEM ERROR\n");
				//}
					tg = !tg;
					T++;
				}
				
				vTaskDelayUntil(&xLastWakeTime,500);
	}
	
}