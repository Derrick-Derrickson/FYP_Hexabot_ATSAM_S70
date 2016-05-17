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

#define LED0 PIOA,PIO_PA28
#define LED1 PIOA,PIO_PA29
#define LED2 PIOA,PIO_PA30
#define LED3 PIOA,PIO_PA25
#define LED4 PIOB,PIO_PB13
#define LED5 PIOA,PIO_PA2
#define LED6 PIOA,PIO_PA31
#define LED7 PIOA,PIO_PA6
#define BOARD_SDRAM_ADDR  0x70000000

#define GLOBAL_SLOWDOWN 1

#define PWM_CTRL_A_I2C_ADDR_A 0x40
#define PWM_CTRL_A_I2C_ADDR_B 0x41
//First Driver
#define L0_S0 PWM_CTRL_A_I2C_ADDR_A,0x1E
#define L0_S1 PWM_CTRL_A_I2C_ADDR_A,0x22
#define L0_S2 PWM_CTRL_A_I2C_ADDR_A,0x26

#define L2_S0 PWM_CTRL_A_I2C_ADDR_A,0x12
#define L2_S1 PWM_CTRL_A_I2C_ADDR_A,0x16
#define L2_S2 PWM_CTRL_A_I2C_ADDR_A,0x1A

#define L4_S0 PWM_CTRL_A_I2C_ADDR_A,0x06
#define L4_S1 PWM_CTRL_A_I2C_ADDR_A,0x0A
#define L4_S2 PWM_CTRL_A_I2C_ADDR_A,0x0E

//Other driver
#define L1_S0 PWM_CTRL_A_I2C_ADDR_B,0x06
#define L1_S1 PWM_CTRL_A_I2C_ADDR_B,0x0A
#define L1_S2 PWM_CTRL_A_I2C_ADDR_B,0x0E

#define L3_S0 PWM_CTRL_A_I2C_ADDR_B,0x12
#define L3_S1 PWM_CTRL_A_I2C_ADDR_B,0x16
#define L3_S2 PWM_CTRL_A_I2C_ADDR_B,0x1A

#define L5_S0 PWM_CTRL_A_I2C_ADDR_B,0x1E
#define L5_S1 PWM_CTRL_A_I2C_ADDR_B,0x22
#define L5_S2 PWM_CTRL_A_I2C_ADDR_B,0x26




#endif // USER_BOARD_H
