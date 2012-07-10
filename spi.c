/*
 *
 * Last Modified: Xin Jin, 16 February 2012
 *
 * - Implements the following SPI interface functions
 *	- init
 *	- transmit
 *	- exchange
 *
 */

// Include files
#include <msp430f2272.h> 
#include "main.h"
#include "spi.h"

/*
 * Initialise SPI port
 * 	- Master, 8 bits, mode 0:0, max speed, 3 wire
 * 	- Clock = 0: SMCLK  (works with no external clock input, DCO only)
 *	- Clock = 1: ACLK   (fastest possible, from external clock input)
 */
 //Updated by Xin on Feb 16, 2012. 
void spi_init( unsigned char clock )
{
	
	// --set the direction // P3SEL |= CAN_MOSI | CAN_MISO | CAN_SCLK;	
	//Note, may have to play around with polarity and clock edging 
	UCB0CTL1 |= UCSWRST; //Hold module in logic freeze
	UCB0CTL0 |= UCCKPL | UCMSB | UCMST | UCSYNC; // UCMODE 3-pin,8-bit SPI master
	//UCMSB sets the 3wire vs 4 wire mode, old DCU seems to have used 4 pin mode. 
	if( clock == 0 ) 
	{
		UCB0CTL1 =	UCSSEL1 ;//  BRCLK = ACLK
	}
	else 
	{
		UCB0CTL1 = UCSSEL1 | UCSSEL0 ;	// Mode 0:0, BRCLK = SMCL
	}
	UC0IE |= UCB0RXIE & UCB0TXIE; //Enable Recieve and Transmit interrupt flags 
	UCB0CTL1 &= ~UCSWRST; //Release module for code execution 
	
}

/*
 * Transmits data on SPI connection
 *	- Busy waits until entire shift is complete
 *	- On devices with hardware SPI support, this function is identical to spi_exchange,
 *	  with the execption of not returning a value
 *	- On devices with software (bit-bashed) SPI support, this function can run faster
 *	  because it does not require data reception code
 */
void spi_transmit( unsigned char data )
{
	UCB0TXBUF = data;
	while(( IFG2 & UCB0TXIFG ) == 0x00 );	// Wait for Rx completion (implies Tx is also complete)
	//U0RXBUF; vestigial line from old DCU, shouldn't be needed. 
	// being left here for now for continuity sake 
}

/*
 * Exchanges data on SPI connection
 *	- Busy waits until entire shift is complete
 *	- This function is safe to use to control hardware lines that rely on shifting being finalised
 */
unsigned char spi_exchange( unsigned char data )
{
	UCB0TXBUF = data;
	while(( IFG2 & UCB0RXIFG ) == 0x00 );// Wait for Rx completion (implies Tx is also complete)
	return( UCB0RXBUF );
}
