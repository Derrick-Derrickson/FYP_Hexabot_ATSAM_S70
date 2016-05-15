/**
 * \file
 *
 * \brief User board initialization template
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>
#include "../Debug.h"

//define board specific paramaters

#define CONF_BOARD_SDRAMC
#define USART_SERIAL                 UART4
#define USART_SERIAL_ID              ID_UART4  //USART0 for sam4l
#define USART_SERIAL_BAUDRATE        9600
#define USART_SERIAL_CHAR_LENGTH     US_MR_CHRL_8_BIT
#define USART_SERIAL_PARITY          US_MR_PAR_NO
#define USART_SERIAL_STOP_BIT        US_MR_NBSTOP_1_BIT



void board_init(void)
{
	/* ######################################
	   ######################################
					Setup Clock
	   ######################################
	   ###################################### */
	CONFIG_SYSCLK_SOURCE;
	supc_switch_sclk_to_32kxtal(SUPC,0);
	sysclk_init();
	delay_init(150000000);
	/* This function is meant to contain board-specific initialization code
	 * for, e.g., the I/O pins. The initialization can rely on application-
	 * specific board configuration, found in conf_board.h.
	 */
	//enable UART4 as our DEBUG LINE
	
	
	
	/* ######################################
	   ######################################
					Enable UART
	   ######################################
	   ###################################### */
	const sam_uart_opt_t usart_console_settings = {
		USART_SERIAL_BAUDRATE,
		USART_SERIAL_CHAR_LENGTH,
		USART_SERIAL_PARITY,
		USART_SERIAL_STOP_BIT,
		US_MR_CHMODE_NORMAL
	};
	sysclk_enable_peripheral_clock(USART_SERIAL_ID);
	pmc_enable_periph_clk(ID_UART4);
	uart_init(USART_SERIAL, &usart_console_settings);
	uart_enable(USART_SERIAL);
	uart_enable_tx(USART_SERIAL);
	uart_enable_rx(USART_SERIAL);
	uart_set_clock_divisor(UART4,(1000/GLOBAL_SLOWDOWN));
	pmc_enable_periph_clk(ID_PIOD);
	pio_set_peripheral(PIOD,PIO_TYPE_PIO_PERIPH_C,1<<3 | 1<<18);
	//Test UART
	sendDebugString("UART CONSOLE STARTED ON UART4\n\n");
	
	
	
	/* ######################################
	   ######################################
					Enable LEDS
	   ######################################
	   ###################################### */
		pio_set_peripheral(PIOB,PIO_TYPE_PIO_OUTPUT_1,1<<12);
	
		pmc_enable_periph_clk(ID_PIOA);
		pmc_enable_periph_clk(ID_PIOB);
		pio_set_output(PIOA,LED0,LOW,DISABLE,DISABLE);
		pio_set_output(PIOA,LED1,LOW,DISABLE,DISABLE);
		pio_set_output(PIOA,LED2,LOW,DISABLE,DISABLE);
		
		pio_set_output(PIOB,LED3,LOW,DISABLE,DISABLE);
		pio_set_output(PIOB,LED4,LOW,DISABLE,DISABLE);
		
		pio_set_output(PIOA,LED5,LOW,DISABLE,DISABLE);
		pio_set_output(PIOA,LED6,LOW,DISABLE,DISABLE);
		pio_set_output(PIOA,LED7,LOW,DISABLE,DISABLE);
		
		sendDebugString("LED INIT COMPLETE\n");
		
	/* ######################################
	   ######################################
					Disable Watchdog
	   ######################################
	   ###################################### */
		
		wdt_disable(WDT);
		
		
		
	/* ######################################
	   ######################################
					Enable IRQ
	   ######################################
	   ###################################### */
		cpu_irq_enable();
		
	/* ######################################
	   ######################################
					Setup SDRAM
	   ######################################
	   ###################################### */
	//Build Memory device settings:
	sendDebugString("BEGINING SDRAM INIT\n");
	const sdramc_memory_dev_t SDRAM_ALLIANCE_AS4C = {
		24,
		//0b00000000010000000001000000,
		0x0FFFFFFF,
		//0,
		//0b000000000110000,
		//0b00000000010000000001000000,
		(
			SDRAMC_CR_NC_COL9		|
			SDRAMC_CR_NR_ROW13		|
			SDRAMC_CR_NB_BANK4		|
			SDRAMC_CR_CAS_LATENCY3	|
			SDRAMC_CR_DBW			|
			SDRAMC_CR_TWR(1)		|
			SDRAMC_CR_TRC_TRFC(1)	|
			SDRAMC_CR_TRP(1)		|
			SDRAMC_CR_TRCD(1)		|
			SDRAMC_CR_TRAS(1)		|
			SDRAMC_CR_TXSR(1)		)
	};
	//enable the clock for the SDRAM Controller
	pmc_enable_periph_clk(ID_SDRAMC);
	
	pmc_enable_periph_clk(ID_PIOC);
	pmc_enable_periph_clk(ID_PIOD);
	pmc_enable_periph_clk(ID_PIOE);
	//set all the SDRAMC pins to SDRAMC Mode (This took way too fucking long)
	pio_set_peripheral(PIOC,PIO_TYPE_PIO_PERIPH_A,
	1<<0	|
	1<<1	|
	1<<2	|
	1<<3	|
	1<<4	|
	1<<5	|
	1<<6	|
	1<<7	|
	1<<18	|
	1<<19	|
	1<<20	|
	1<<21	|
	1<<22	|
	1<<23	|
	1<<24	|
	1<<25	|
	1<<26	|
	1<<27	|
	1<<28	|
	1<<29	|
	1<<30	|
	1<<31	);
	
	pio_pull_down(PIOC,
	1<<0	|
	1<<1	|
	1<<2	|
	1<<3	|
	1<<4	|
	1<<5	|
	1<<6	|
	1<<7	|
	1<<18	|
	1<<19	|
	1<<20	|
	1<<21	|
	1<<22	|
	1<<23	|
	1<<24	|
	1<<25	|
	1<<26	|
	1<<27	|
	1<<28	|
	1<<29	|
	1<<30	|
	1<<31	,
	1);
	
	pio_pull_up(PIOC,
	1<<15	|
	1<<0	|
	1<<1	|
	1<<2	|
	1<<3	|
	1<<4	|
	1<<5	|
	1<<6	|
	1<<7	|
	1<<18	|
	1<<19	|
	1<<20	|
	1<<21	|
	1<<22	|
	1<<23	|
	1<<24	|
	1<<25	|
	1<<26	|
	1<<27	|
	1<<28	|
	1<<29	|
	1<<30	|
	1<<31	,
	0);
	
	
	pio_set_peripheral(PIOA,PIO_TYPE_PIO_PERIPH_A,
	1<<15	|
	1<<16	);
	
	pio_pull_down(PIOA,1<<15	|	1<<16	,0);
	pio_pull_up(PIOA,1<<15	|	1<<16	,1);
	
	pio_set_peripheral(PIOA,PIO_TYPE_PIO_PERIPH_C,
	1<<18	|
	1<<19	|
	1<<20	|
	1<<0	);
	
	pio_pull_down(PIOA,
	1<<18	|
	1<<19	|
	1<<20	|
	1<<0	,
	1);
	pio_pull_up(PIOA,
	1<<18	|
	1<<19	|
	1<<20	|
	1<<0	,
	0);
	
	pio_set_peripheral(PIOD,PIO_TYPE_PIO_PERIPH_C,
	1<<15	|
	1<<16	|
	1<<17	|
	1<<13	|
	1<<23	|
	1<<14	|
	1<<29	);
	
	pio_pull_down(PIOD,1<<15	|
	1<<16	|
	1<<17	|
	1<<13	|
	1<<23	|
	1<<14	|
	1<<29	,
	1);
	pio_pull_up(PIOD,1<<15	|
	1<<16	|
	1<<17	|
	1<<13	|
	1<<23	|
	1<<14	|
	1<<29	,
	0);
	
	pio_set_peripheral(PIOE,PIO_TYPE_PIO_PERIPH_A,
	1<<2	|
	1<<3	|
	1<<0	|
	1<<1	|
	1<<4	|
	1<<5	);
	
	pio_pull_down(PIOE,
	1<<2	|
	1<<3	|
	1<<0	|
	1<<1	|
	1<<4	|
	1<<5	,
	1);
	
	pio_pull_up(PIOE,
	1<<2	|
	1<<3	|
	1<<0	|
	1<<1	|
	1<<4	|
	1<<5	,
	0);
	
	//THIS LINE IS A CUNT
	MATRIX->CCFG_SMCNFCS = MATRIX->CCFG_SMCNFCS | CCFG_SMCNFCS_SDRAMEN;
	//WHAT A CUNT, RIGHT?
	
	pio_set_peripheral(PIOC,PIO_TYPE_PIO_PERIPH_A,1<<15);
	sdramc_init((sdramc_memory_dev_t *)&SDRAM_ALLIANCE_AS4C,sysclk_get_main_hz()/4);
	sendDebugString("SDRAM CONTROLLER STARTED.. I dont think it works...\n");
	
	pio_set_output(PIOD,PIO_PD26,LOW,DISABLE,DISABLE);
	pio_set(PIOD,PIO_PD26);
	
	MATRIX->CCFG_SYSIO = MATRIX->CCFG_SYSIO | CCFG_SYSIO_SYSIO12; 
    //qspi_config_t qspiConf;
	//qspiConf->serial_memory_mode = 0;
	//qspiConf->loopback_en = 0;
	//qspiConf->wait_data_for_transfer = 0;
	//qspiConf->csmode = 0;
	//qspiConf->bits_per_transfer = QSPI_MR_NBBITS_8_BIT;
	//qspiConf->baudrate = 1000000;
	
		
}
