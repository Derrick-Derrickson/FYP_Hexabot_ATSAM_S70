/**
 * \file
 *
 * \brief User board definition template
 *
 */

 /* This file is intended to contain definitions and configuration details for
 * features and devices that are available on the board, e.g., frequency and
 * startup time for an external crystal, external memory devices, LED and USART
 * pins.
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef USER_BOARD_H
#define USER_BOARD_H

#include <conf_board.h>

// External oscillator settings.
// Uncomment and set correct values if external oscillator is used.
#define BOARD_MCK 150000000
// External oscillator frequency
#define BOARD_XOSC_HZ          12000000

// External oscillator type.
//!< External clock signal
//#define BOARD_XOSC_TYPE        XOSC_TYPE_EXTERNAL
//!< 32.768 kHz resonator on TOSC
//#define BOARD_XOSC_TYPE        XOSC_TYPE_32KHZ
//!< 0.4 to 16 MHz resonator on XTALS
#define BOARD_XOSC_TYPE        XOSC_TYPE_XTAL

// External oscillator startup time
#define BOARD_XOSC_STARTUP_US  500000


//define LED pins and UART settings

#define LED0 PIO_PA28
#define LED1 PIO_PA29
#define LED2 PIO_PA30
#define LED3 PIO_PB12
#define LED4 PIO_PB13
#define LED5 PIO_PA2
#define LED6 PIO_PA31
#define LED7 PIO_PA6
#define BOARD_SDRAM_ADDR  0x70000000

#define GLOBAL_SLOWDOWN 1


#endif // USER_BOARD_H
