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
#include "Hexabot/Hexabot.h"
#include "DW1000.h"
#include <stdlib.h>
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
	
	//enable FPU
	fpu_enable();
	
	
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
	uart_set_clock_divisor(UART4,(1000));
	pmc_enable_periph_clk(ID_PIOD);
	pio_set_peripheral(PIOD,PIO_TYPE_PIO_PERIPH_C,1<<3 | 1<<18);
	//Test UART
	sendDebugString("MELLATRON9000 BOOT SEQUENCE\nUART CONSOLE STARTED ON UART4\nBaudRate: 115200\nBits: 8\nNo stop bits \n");
	
	
	
	
	/* ######################################
	   ######################################
					Enable LEDS
	   ######################################
	   ###################################### */
	sendDebugString("LED INITIALIZATION - STARTED\n");
		pio_set_peripheral(PIOB,PIO_TYPE_PIO_OUTPUT_1,1<<12);
		pmc_enable_periph_clk(ID_PIOA);
		pmc_enable_periph_clk(ID_PIOB);
		pio_set_output(LED0,LOW,DISABLE,DISABLE);
		pio_set_output(LED1,LOW,DISABLE,DISABLE);
		pio_set_output(LED2,LOW,DISABLE,DISABLE);		
		pio_set_output(LED3,LOW,DISABLE,DISABLE);
		
		pio_set_output(LED4,LOW,DISABLE,DISABLE);
		pio_set_output(LED5,LOW,DISABLE,DISABLE);
		pio_set_output(LED6,LOW,DISABLE,DISABLE);
		pio_set_output(LED7,LOW,DISABLE,DISABLE);
		
		sendDebugString("LED INITIALIZATION - FINISHED\n");
		
	/* ######################################
	   ######################################
					Disable Watchdog
	   ######################################
	   ###################################### */
		sendDebugString("WATCHDOG INITIALIZATION - STARTED\n");
		wdt_disable(WDT);
		sendDebugString("WATCHDOG INITIALIZATION - FINISHED\n");
		
		
		
	/* ######################################
	   ######################################
					Enable IRQ
	   ######################################
	   ###################################### */
		sendDebugString("GLOBAL IRQ INITIALIZATION - STARTED\n");
		cpu_irq_enable();
		sendDebugString("GLOBAL IRQ INITIALIZATION - FINISHED\n");
	/* ######################################
	   ######################################
					Setup SDRAM
	   ######################################
	   ###################################### */
	//Build Memory device settings:
	sendDebugString("SDRAM INITIALIZATION - STARTED\n");
	const sdramc_memory_dev_t SDRAM_ALLIANCE_AS4C = {
		25,
		//0b00000000010000000001000000,
		//0x0FFFFFFF,
		//0,
		//0b000000000110000,
		0b0001000000001000000,
		(
			SDRAMC_CR_NC_COL9		|
			SDRAMC_CR_NR_ROW13		|
			SDRAMC_CR_NB_BANK4		|
			SDRAMC_CR_CAS_LATENCY3	|
			SDRAMC_CR_DBW			|
			SDRAMC_CR_TWR(5)		|
			SDRAMC_CR_TRC_TRFC(12)	|
			SDRAMC_CR_TRP(5)		|
			SDRAMC_CR_TRCD(5)		|
			SDRAMC_CR_TRAS(8)		|
			SDRAMC_CR_TXSR(12)		)
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
	sdramc_init((sdramc_memory_dev_t *)&SDRAM_ALLIANCE_AS4C,sysclk_get_main_hz());
	sendDebugString("SDRAM CONTROLLER STARTED\n");
	//checkSDRAM
	//SdramCheck();
	memset(BOARD_SDRAM_ADDR,0,BOARD_SDRAM_ADDR_NUM);
	sendDebugString("SDRAM INITIALIZATION - FINISHED\n");
	
	/* ######################################
	   ######################################
					 Setup i2c
	   ######################################
	   ###################################### */
	sendDebugString("TWIHS INITIALIZATION - STARTED\n");
	pio_set_output(PIOD,PIO_PD26,LOW,DISABLE,DISABLE);
	pio_set(PIOD,PIO_PD26);
	pio_set_output(PIOA,PIO_PA26,LOW,DISABLE,DISABLE);
	pio_clear(PIOA,PIO_PA26);
	
	pmc_enable_periph_clk(ID_TWIHS0);
	pio_set_peripheral(PIOA,PIO_TYPE_PIO_PERIPH_A,1<<3 | 1<<4);
	pio_set_output(PIOD,PIO_PD26,LOW,DISABLE,DISABLE);
	pio_set(PIOD,PIO_PD26);
	
	Twihs_reinit();
	
	//twihs_reset(TWIHS0);
	//twihs_enable_master_mode(TWIHS0);
	//twihs_options_t twihs_opts;
	//twihs_opts.master_clk = sysclk_get_cpu_hz();
	//twihs_opts.speed = 200000;
	//twihs_master_init(TWIHS0,&twihs_opts);
	sendDebugString("TWIHS INITIALIZATION - FINISHED\n");
	
	
	/* ######################################
	   ######################################
				 Setup Servo Driver
	   ######################################
	   ###################################### */
	sendDebugString("SERVO DRIVER INITIALIZATION - STARTED\n");
	ServoDriverInit(PWM_CTRL_A_I2C_ADDR_A);
	ServoDriverInit(PWM_CTRL_A_I2C_ADDR_B);
	sendDebugString("SERVO DRIVER INITIALIZATION - FINISHED\n");
	
	/* ######################################
	   ######################################
			 		Setup Camera
	   ######################################
	   ###################################### */

	sendDebugString("CAMERA INITIALIZATION - STARTED\n");
	pio_set_output(PIOD,PIO_PD10,LOW,DISABLE,DISABLE);
	pio_set(PIOD,PIO_PD10);
	delay_ms(10);
	//pio_clear(PIOD,PIO_PD10);
	pio_set_peripheral(PIOD,PIO_TYPE_PIO_PERIPH_D,
	1<<22	|
	1<<21	|
	1<<11	|
	1<<12	|
	1<<27	|
	1<<28	|
	1<<24	|
	1<<25	);
	
	pio_pull_up(PIOD,
	1<<22	|
	1<<21	|
	1<<11	|
	1<<12	|
	1<<27	|
	1<<28	|
	1<<24	|
	1<<25	,0);
	
	pio_pull_down(PIOD,
	1<<22	|
	1<<21	|
	1<<11	|
	1<<12	|
	1<<27	|
	1<<28	|
	1<<24	|
	1<<25	,1);
	
	pio_set_peripheral(PIOB,PIO_TYPE_PIO_PERIPH_D,
	1<<3);
	
	pio_pull_up(PIOB,1<<3,0);
	pio_pull_down(PIOB,1<<3,1);
	
	pio_set_peripheral(PIOA,PIO_TYPE_PIO_PERIPH_D,
	1<<27	|
	1<<24	);
	
	pio_set_peripheral(PIOA,PIO_TYPE_PIO_PERIPH_B,
		1<<9	|
		1<<5	);
	
	pio_pull_up(PIOA,
	1<<9	|
	1<<5	|
	1<<27	|
	1<<24	,0);
	
	pio_pull_down(PIOA,
	1<<9	|
	1<<5	|
	1<<27	|
	1<<24	,1);
	
	pmc_enable_periph_clk(ID_ISI);
	
	//set camera to 640x480
	//SetupCameraYUVVGA();
	SetupCameraYUVVGA_OV7670();
	//Optional Test Mode
	//write_SCCB(0x8D,1<<4);
	isi_reset(ISI);
	
	struct isi_config_t isiConf;
	isiConf.hpol = 1;
	isiConf.vpol = 1;
	isiConf.pck_plo = 0;
	isiConf.emb_sync = 0;
	isiConf.crc_sync = 0;
	isiConf.sld = 1;
	isiConf.sfd =0;
	isiConf.image_fmt = ISI_INPUT_YUV;
	isiConf.image_hsize = 640;
	isiConf.image_vsize = 480;
	isiConf.thmask = 2;
	

	memset(BOARD_SDRAM_ADDR,0,BOARD_SDRAM_ADDR_NUM);
	struct isi_frame_buffer_descriptors* isiFBD0 = (struct isi_frame_buffer_descriptors*) malloc(3*4);
	struct isi_frame_buffer_descriptors* isiFBD1 = (struct isi_frame_buffer_descriptors*) malloc(3*4);
	
	isiFBD0->next = isiFBD1;
	isiFBD0->current =CAM_FRAME0_ADDR;
	isiFBD0->control =0x1;
	
	isiFBD1->next = isiFBD0;
	isiFBD1->current =CAM_FRAME0_ADDR;
	isiFBD1->control =0x1;
	
	isi_init(ISI,&isiConf);
	//isi_set_dma_codec_path(ISI,0,1,0,0,0);
	//ISI->ISI_PDECF = 2*16;
	isi_set_dma_preview_path(ISI,0,isiFBD0,0x01,isiFBD0->current);
	isi_dma_channel_enable(ISI,1);
	
	isi_size_configure(ISI,640,640,320,320);
	ISI->ISI_CFG2 = ISI->ISI_CFG2 | ISI_CFG2_YCC_SWAP_MODE1;
	//ISI->ISI_PDECF = 32;
	isi_enable(ISI);
	sendDebugString("CAMERA INITIALIZATION - FINISHED\n");
	
	/* ######################################
	   ######################################
			 	Setup Wireless Module
	   ######################################
	   ###################################### */
	
		sendDebugString("QSPI INITIALIZATION - STARTED\n");
	    struct qspi_config_t qspiConf;
	    qspiConf.serial_memory_mode = 0;
	    qspiConf.loopback_en = 0;
	    qspiConf.wait_data_for_transfer = 0;
	    qspiConf.csmode = 0;
	    qspiConf.bits_per_transfer = QSPI_MR_NBBITS_8_BIT;
	    qspiConf.baudrate = 16000000;
		qspiConf.min_delay_qcs = 4;
		qspiConf.delay_between_ct = 10;
		qspiConf.clock_polarity = 0;
		qspiConf.clock_phase = 0;
				
		pio_set_peripheral(PIOA,PIO_TYPE_PIO_PERIPH_A,
		1<<17	|
		1<<12	|
		1<<13	|
		1<<14	|
		1<<11);
		
		pio_pull_up(PIOA,
		1<<17	|
		1<<12	|
		1<<13	|
		1<<14	|
		1<<11,1);
		
		pio_set_peripheral(PIOD,PIO_TYPE_PIO_PERIPH_A,
		1<<31);
		
		pmc_enable_periph_clk(ID_QSPI);

		qspi_disable(QSPI);
		qspi_reset(QSPI);
		qspi_initialize(QSPI,&qspiConf);
		qspi_enable(QSPI);
		
		qspi_disable(QSPI);
		qspi_reset(QSPI);
		qspi_initialize(QSPI,&qspiConf);
		delay_ms(100);
		qspi_enable(QSPI);
		delay_ms(100);
		//DW1000_initialise();
		sendDebugString("QSPI INITIALIZATION - FINISHED\n");
		
		//Initalize the dwm1000 module 
		sendDebugString("DWM1000 INITIALIZATION - STARTED\n");
		//DW1000_initialise2();
		//DW1000_toggleGPIO_MODE();
		sendDebugString("DWM1000 INITIALIZATION - FINISHED\n");
		
		
		
		
	/* ######################################
	   ######################################
			 		Setup ADC
	   ######################################
	   ###################################### */
		sendDebugString("ADC INITIALIZATION - STARTED\n");
		struct afec_config confDefaults;
		pmc_enable_periph_clk(AFEC0);
		
		afec_enable(AFEC0);
		afec_get_config_defaults(&confDefaults);
		afec_init(AFEC0,&confDefaults);
		afec_set_trigger(AFEC0,AFEC_TRIG_SW);
		
		pmc_enable_periph_clk(AFEC1);
		
		afec_enable(AFEC1);
		afec_get_config_defaults(&confDefaults);
		afec_init(AFEC1,&confDefaults);
		afec_set_trigger(AFEC1,AFEC_TRIG_SW);
		
		afec_channel_enable(AFEC1,AFEC_CHANNEL_0);
		
		pio_pull_up(PIOB,1<<1,0);
		pio_pull_down(PIOB,1<<1,0);
		sendDebugString("ADC INITIALIZATION - FINISHED\n");
		
	/* ######################################
	   ######################################
                  Setup SWITCHES
	   ######################################
	   ###################################### */
		sendDebugString("SWITCH INITIALIZATION - STARTED\n");
		pio_set_input(PIOC,1<<12,PIO_PULLUP | PIO_DEBOUNCE);
		pio_set_input(PIOC,1<<11,PIO_PULLUP | PIO_DEBOUNCE);
		pio_set_input(PIOC,1<<10,PIO_PULLUP | PIO_DEBOUNCE);
		pio_set_input(PIOC,1<<9,PIO_PULLUP | PIO_DEBOUNCE);
		sendDebugString("SWITCH INITIALIZATION - FINISHED\n");
	/* ######################################
	   ######################################
                  Setup USB POWER
	   ######################################
	   ###################################### */
		sendDebugString("SWITCH INITIALIZATION - STARTED\n");
		pio_set_input(PIOD,1<<9,PIO_PULLUP | PIO_DEBOUNCE);
		sendDebugString("SWITCH INITIALIZATION - FINISHED\n");
	/* ######################################
	   ######################################
                  Setup Interrupts
	   ######################################
	   ###################################### */
	
		sendDebugString("PERIFERAL IRQ INITIALIZATION - STARTED\n");
		//ISI
		//isi_enable_interrupt(ISI,1<<16|1<<17);
		//NVIC_ClearPendingIRQ(ISI_IRQn);
		//NVIC_SetPriority(ISI_IRQn,7);
		//NVIC_EnableIRQ(ISI_IRQn);
		
		//UART4
		uart_enable_interrupt(UART4,UART_IER_RXRDY);
		NVIC_ClearPendingIRQ(UART4_IRQn);
		NVIC_SetPriority(UART4_IRQn,6);
		NVIC_EnableIRQ(UART4_IRQn);
		sendDebugString("PERIFERAL IRQ INITIALIZATION - FINISHED\n");
}


