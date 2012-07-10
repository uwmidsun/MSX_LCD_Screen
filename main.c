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
			

	//Initialise the necessary IO ports
	initIO();	
	//Initialise the SPI module
	spi_init(0); //use SMCLK (faster than ACLK)	
	//Initialise the attached CAN controller via SPI
	can_init();
	//enable interrupts
	//int_init();
	spi_init(1);
	//Initialise the necessary clocks, from the right sources
	initClocks();
	//Initialise the timer/CCR module
	initTimers();	
	
	_BIS_SR(GIE);
	
	// Device Configuration and Setup
	initClocks();
	initTimers();
		
	//===LCD Setup===
	initLCD();
	LCD_Cmd_DisplayConfig(DISPLAY_ON | CURSOR_OFF | BLINK_OFF);
	//LCD_Cmd_SetDdramAddr(LINE1_HOME_ADDR);
	LCD_Cmd_Home();
	
	P2OUT |= 0x02; 
	
    volatile unsigned int i;            // volatile to prevent optimization
	while (1)
	{	
	    sprintf(text, "CAN_Activity: %d", CAN_Activity);
		LCD_Cmd_WriteLine(1, text);
		sprintf(text, "CAN Error: %d", CAN_error);
		LCD_Cmd_WriteLine(2, text);
		sprintf(text, "Velocity: %d", actual_velocity);
		LCD_Cmd_WriteLine(3, text);
	    i = 0;                          // SW Delay
	    for (i; i<500000;i++);
	}
	
	//return 0;
}

