/***********************************************************
*Info LCD Code 
*Author : Xin Jin 
*
*Vehicle: MSX 
*
*Last updated Date: July 10th, 2011 
*
*Revision 1
************************************************************/


#include "msp430x22x2.h"
#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "spi.h"
#include "can.h"
#include "init.h" 
#include "lcd.h"

int main (void)
{
  	//===Declarations===
  	char text[NUM_OF_CHAR_PER_LINE + 1]; // one extra for '\0', 'char' for stdio.hs
	
  	WDTCTL = WDTPW + WDTHOLD;             // Stop watchdog timer
  	P2DIR |= 0x02;                        // Set P2.1 to output direction
	
	//===Device Configuration and Setup===
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT
	initClocks();
	initIO();
	initTimers();
	
	
	//===LCD Setup===
	initLCD();
	LCD_Cmd_DisplayConfig(DISPLAY_ON | CURSOR_OFF | BLINK_OFF);
	//LCD_Cmd_SetDdramAddr(LINE1_HOME_ADDR);
	LCD_Cmd_Home();

	//_BIS_SR(GIE); // enable maskable interrupts

  
    volatile unsigned int i;            // volatile to prevent optimization
  //LCD_Cmd_ClearLine(1);
  while(1)
  {
    P2OUT ^= 0x02;               // Toggle P2.2 using exclusive-OR
    sprintf(text, "INFO LCD Screen 1");
	LCD_Cmd_WriteLine(1, text);
	sprintf(text, "INFO LCD Screen 2");
	LCD_Cmd_WriteLine(2, text);
	sprintf(text, "INFO LCD Screen 3");
	LCD_Cmd_WriteLine(3, text);
	sprintf(text, "INFO LCD Screen 4");
	LCD_Cmd_WriteLine(4, text);
    i = 0;                          // SW Delay
    for (i=0; i<50000;i++);
  }
  
  return 1;
}

