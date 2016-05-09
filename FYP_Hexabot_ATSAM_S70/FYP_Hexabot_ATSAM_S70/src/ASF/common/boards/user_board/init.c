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
#define LED0 PIO_PA28
#define LED1 PIO_PA29
#define LED2 PIO_PA30
#define LED3 PIO_PB12
#define LED4 PIO_PB13
#define LED5 PIO_PA2
#define LED6 PIO_PA31
#define LED7 PIO_PA6

#define USART_SERIAL                 UART4
#define USART_SERIAL_ID              ID_UART4  //USART0 for sam4l
#define USART_SERIAL_BAUDRATE        9600
#define USART_SERIAL_CHAR_LENGTH     US_MR_CHRL_8_BIT
#define USART_SERIAL_PARITY          US_MR_PAR_NO
#define USART_SERIAL_STOP_BIT        US_MR_NBSTOP_1_BIT


void board_init(void)
{
	CONFIG_SYSCLK_SOURCE;
	sysclk_init();
	/* This function is meant to contain board-specific initialization code
	 * for, e.g., the I/O pins. The initialization can rely on application-
	 * specific board configuration, found in conf_board.h.
	 */
	//enable UART4 as our DEBUG LINE
	
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
	uart_set_clock_divisor(UART4,1000);
	pmc_enable_periph_clk(ID_PIOD);
	pio_set_peripheral(PIOD,PIO_TYPE_PIO_PERIPH_C,1<<3 | 1<<18);
	
	sendDebugString("UART CONSOLE STARTED ON UART4\n\n");
}
