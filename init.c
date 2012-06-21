/* *********************************** init.c ***********************************	*/
//
// Function: Includes functions and variables that has to do with configuaring the microcontroller's settings
//
/* ********************************************************************************	*/

/* =================================== #includes =================================== */
#include <msp430f2272.h>
#include "globals.h"
#include "init.h"

/* =================================== Function Definitions =================================== */

/* ~~~~~~~~~~~~~~~ initClocks Function ~~~~~~~~~~~~~~~ */
// Set MCLK = SMCLK = DCOCLK = approx 2.00MHz with Rosc = 100k 1% 0.6W 50ppm/C
// Set ACLK = XT1 in LF mode using external OSC @ 32.768kHz
// OFIE (osc fault) interrupt disabled (default)
void initClocks(void) {

	// Set DCO = 3; no modulator; 
	DCOCTL = DCO0 + DCO1;

	// Disable XT2 (default); XT1 in LF mode (32.768kHz osc XT); ...
	// ... no divider for ACLK; Rsel = 4 (default)
	BCSCTL1 = XT2OFF + RSEL2;

	// Set MCLK = DCOCLK; no divider for MCLK; ...
	// ... set SMCLK = DCOCLK; no divider for SMCLK; use external DCO resistor
	BCSCTL2 = DCOR;
}

/* ~~~~~~~~~~~~~~~ initIO Function ~~~~~~~~~~~~~~~ */
void init_LCD_IO(void) {

	// Configure all LCD GPIO as outputs
	LCD_RS_PINDIR_REG	|= LCD_RS_PINBIT_MASK;
	LCD_RW_PINDIR_REG	|= LCD_RW_PINBIT_MASK;
	LCD_E_PINDIR_REG	|= LCD_E_PINBIT_MASK;
	LCD_D0_PINDIR_REG	|= LCD_D0_PINBIT_MASK;
	LCD_D1_PINDIR_REG	|= LCD_D1_PINBIT_MASK;
	LCD_D2_PINDIR_REG	|= LCD_D2_PINBIT_MASK;
	LCD_D3_PINDIR_REG	|= LCD_D3_PINBIT_MASK;
	LCD_D4_PINDIR_REG	|= LCD_D4_PINBIT_MASK;
	LCD_D5_PINDIR_REG	|= LCD_D5_PINBIT_MASK;
	LCD_D6_PINDIR_REG	|= LCD_D6_PINBIT_MASK;
	LCD_D7_PINDIR_REG	|= LCD_D7_PINBIT_MASK;
	
}

/* ~~~~~~~~~~~~~~~ initTimers Function ~~~~~~~~~~~~~~~ */
// Set timer to up counting mode; set timer period; set timer clock source
void initTimers(void) {

	// Disable capture mode; use compare mode; enable TACCR0 IRQ; clear CCIFG flag
	TACCTL0 = CCIE;

	// Set timer period to 1310/32768 = 40ms or 25Hz
	CCR0 = 1310;

	// Set Timer A clock source = ACLK; no input divider; use up mode (count ...
	// ... to TACCR0); disable TAIV (default - use CCIFG instead)
	TACTL = TASSEL_1 + MC_1; 
}
