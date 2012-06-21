#include <msp430f2272.h>
#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "init.h"
#include "lcd.h"
#include "can.h"
#include "spi.h"
#include "main.h"


#define DEBUG
char text[NUM_OF_CHAR_PER_LINE + 1]; 
int CAN_error=0;
float actual_velocity;
int CAN_Activity=0;

//=====Initialization Functions======

/*+++++++++++++++++++++++++++
 * Initialise the DCO clock module (used as input to SMCLK)
 *  - Increase frequency to approx. 5 MHz
+++++++++++++++++++++++++++++ */
void clock_init( void )
{
	DCOCTL =  DCO0 + DCO1 + DCO2; //set DCO to 7, MOD to 0 (lower 5 bits)
	BCSCTL1 = RSEL2 + RSEL1 + RSEL0; //enable LFCLK (32768 Hz osc.) with no divider, set RSEL to 7 (DCO -> ~5 MHz)
	BCSCTL2 = 0x00;  //clock sources and dividers for MCLK/SMCLK will be DCO w/ no divider
}

/*+++++++++++++++++++++++++
 * Initialise I/O port directions and states
 *	- Drive unused pins as outputs to avoid floating inputs
 ++++++++++++++++++++++++++*/
void io_init( void )
{
	//SPI pins to peripheral module
	P3SEL |= 0x0E;                            // P3.1-3 SPI option select
	
	//SPI CS pin to output
	P3DIR |= 0x01;                            // P3.0 output direction
	P3OUT |= 0x01;
	
	//CAN interrupt pin to input
	P1DIR &= ~0x01;
	
	init_LCD_IO();
	
	//spare pins to output to avoid floating pins
	P1DIR |= 0x2; 						//P1.1
	P2DIR |= 0x1 | 0x2 | 0x4; 			//P2 pins 0-2
	P3DIR |= 0x8 | 0x10 | 0x20 | 0x40; 	//P3 pins 4-7
}

/*+++++++++++++++++++++++++++++++++++++++++++++++
 * Initialise the timer and CCR registers
 *	- 1.5 Hz output that will be used to driver blinkers
++++++++++++++++++++++++++++++++++++++++++++++++++*/
void timer_init( void )
{
	TACCR0 = 5446; //32678 / 1.5 Hz / 4 (divider) = 
	CCR1 = 0;
	CCR2 = 0;
	CCTL1 = OUTMOD_4;		//toggle output on TACCR1 value
	CCTL2 = OUTMOD_4;		//toggle output on TACCR1 value
	TACTL = TASSEL_1 + MC_1 + ID_2; //run from ACLK (32768 Hz Xtal), count-up mode (to TACCR0)
}
/*+++++++++++++++++++++++++++++++++++++++++++++++
 * Initialise the interupt
++++++++++++++++++++++++++++++++++++++++++++++++++*/
void int_init( void )
{
	//Possible site of error TODO
	P2IES |= 0x01; //interrupt on hi-to-lo transition
	P2IE |= 0x01; //enable P2.0 interrupt
}
//=====Program======

//+++++Interrupts+++++
#pragma vector=PORT2_VECTOR
__interrupt void can_interrupt(void)
{
	//TODO another possible location of error. Set this to check P2IFG & 0x01 == 0x01 to only check P2IFG.0
	P2IFG = 0x00; //clear interrupt
	can_receive();
	
	if(CAN_Activity == 1)
	{
		CAN_Activity =0;
	}
	else
	{
		CAN_Activity =1;
	}
	if(can.status == CAN_OK){
		switch(can.address){
			case MC_CAN_BASE + MC_VELOCITY:
				actual_velocity = can.data.data_fp[1];
				break;
		}
	}
	if(can.status == CAN_ERROR){
		CAN_error = 1;
	}
	else
	{
		CAN_error = 0;
	}
}		

#pragma vector=TIMERA0_VECTOR
__interrupt void TimerA0_ISR (void) {
	TimerA0_Flag = TRUE;
}

//=========Functions========

//+++++delay the next step from running++++
void delay (int time)
{
	
}
//========Main method===========

int main()
{
	//unsigned int i;
	
	
	WDTCTL = WDTPW + WDTHOLD; //Kill watchdog timer 
	
	//asm("nop");
			
	//Initialise the necessary clocks, from the right sources
	clock_init();
	//Initialise the necessary IO ports
	io_init();	
	//Initialise the timer/CCR module
	timer_init();	
	//Initialise the SPI module
	spi_init(0); //use SMCLK (faster than ACLK)	
	//Initialise the attached CAN controller via SPI
	can_init();
	//enable interrupts
	int_init();
	
	_BIS_SR(LPM3_bits + GIE);
	
	// Device Configuration and Setup
	initClocks();
	initTimers();
	
	P2OUT |= 0x02; 
	sprintf(text, "Hello, my name is ");
	LCD_Cmd_WriteLine(1, text);
	Wait_TimerA0();
	//sprintf(text, "Midnight Sun X!");
	//LCD_Cmd_WriteLine(2, text);
	//Wait_TimerA0();
	//sprintf(text, "I am a solar car.");
	//LCD_Cmd_WriteLine(3, text);
	//Wait_TimerA0();
	                          // SW Delay
    //for (i=0; i<50000000;i++);
    volatile unsigned int i;            // volatile to prevent optimization
	while (1)
	{	
    
	    sprintf(text, "CAN_Activity: CAN_Activity %i", CAN_Activity);
		LCD_Cmd_WriteLine(1, text);
		sprintf(text, "CAN Error: %i", CAN_error);
		LCD_Cmd_WriteLine(2, text);
		sprintf(text, "Velocity: %f", actual_velocity);
		LCD_Cmd_WriteLine(3, text);
	    i = 0;                          // SW Delay
	    for (i; i<500000;i++);
	}
	
	//return 0;
}

/*
//=====Code that might be useful later=============

//===HelloWorld Testing code====

void main(void)
{
  	//===Declarations===
  	char text[NUM_OF_CHAR_PER_LINE + 1]; // one extra for '\0', 'char' for stdio.hs
	
  	WDTCTL = WDTPW + WDTHOLD;             // Stop watchdog timer
  	P2DIR |= 0x02;                        // Set P1.0 to output direction
	

	
	//===Device Configuration and Setup===
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT
	initClocks();
	initIO();
	initTimers();

	//===LCD Setup===
	initLCD();
	LCD_Cmd_DisplayConfig(DISPLAY_ON | CURSOR_OFF | BLINK_OFF);
	LCD_Cmd_SetDdramAddr(LINE1_HOME_ADDR);


	
	

	//_BIS_SR(GIE); // enable maskable interrupts

  

  LCD_Cmd_ClearLine(1);
  while(1)
  {
    volatile unsigned int i;            // volatile to prevent optimization

    P2OUT ^= 0x02;                      // Toggle P2.2 using exclusive-OR
    sprintf(text, "Hello, my name is ");
	LCD_Cmd_WriteLine(1, text);
	sprintf(text, "Midnight Sun X!");
	LCD_Cmd_WriteLine(2, text);
	sprintf(text, "I am a solar car.");
	LCD_Cmd_WriteLine(3, text);
    i = 0;                          // SW Delay
    for (i; i<500000;i++);
  }
 
}
*/
