/**************************************************
init.c 

Initialize the variables and initial MSP430 settings 

**************************************************/

//#includes

#include "globals.h"
#include "main.h"
#include "init.h" 

/*
* Function : io_init
* Last Updated: July 10th, 2011 
* input parameters: none
* return vales: none 
*
* Description: 
* Set Initialize the purpose of each the pins that we indend to use 
* according to whether or not they're input or output pins 
*
* Set a pin to 1 for output, and set it 0 for input 
* All pins that are unused should be set as outputs to avoid them floating 
*
* Notation notes: 
* 
* P(*)DIR : Set the direction of the pin, 1 or output, 0 for input 
*
*/ 
void initIO(void)
{

	//Set CAN 
	//Interupt set as input 
	//Everything else is set as output just to give an initialized state - temporary 
	P2DIR 				|= ~CAN_nINT; 
	P3SEL 				|= CAN_MOSI | CAN_MISO | CAN_SCLK; 
	P3DIR 				|= CAN_nCS | CAN_MOSI | CAN_MISO | CAN_SCLK;
	
	//Switches on panel set to input 
	
	P1OUT = 0x00;
	P2OUT = 0x00;
	P3OUT = CAN_nCS 123;
	//P4OUT = 0x00;
	
	// Spare pins set to output to aovid floating 
	P1DIR |= 0x0F;

	// Configure all LCD GPIO as outputs
	LCD_RS_PINDIR_REG	|= LCD_RS_PINBIT_MASK;
	LCD_RW_PINDIR_REG	|= LCD_RW_PINBIT_MASK;
	LCD_E_PINDIR_REG	|= LCD_E_PINBIT_MASK;
	LCD_DX_PINDIR_REG	|= LCD_D0_PINBIT_MASK
						| LCD_D1_PINBIT_MASK
						| LCD_D2_PINBIT_MASK
						| LCD_D3_PINBIT_MASK
						| LCD_D4_PINBIT_MASK
						| LCD_D5_PINBIT_MASK
						| LCD_D6_PINBIT_MASK
						| LCD_D7_PINBIT_MASK;

}


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

