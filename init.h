/* *********************************** init.h ***********************************	*/
//
// Function: Includes variables and prototypes for microcontroller setup & config
//
/* ********************************************************************************	*/

#ifndef INITDSPIC_H
#define INITDSPIC_H


#include <msp430f2272.h>

/* =================================== Function Prototypes =================================== */

void initClocks(void );
void initIO(void);
void initTimers(void);

/* =================================== #defines =================================== */

/* ---------------------------------- Clock Config ----------------------------------- */

// For reference only -- does not actually change the actual hardware frequencies
#define FACLK	32768		// ACLK frequency = XT1 frequency
#define FMCLK	2000000		// MCLK frequency = approx 2MHz
#define FSMCLK	2000000		// SMCLK frequency = approx 2MHz

/* ---------------------------------- LCD GPIO ----------------------------------- */

// LCD GPIO port output register - must match GPIO port direction #defines
#define LCD_D0_PINOUT_REG		P4OUT
#define LCD_D1_PINOUT_REG		P4OUT
#define LCD_D2_PINOUT_REG		P4OUT
#define LCD_D3_PINOUT_REG		P4OUT
#define LCD_D4_PINOUT_REG		P4OUT
#define LCD_D5_PINOUT_REG		P4OUT
#define LCD_D6_PINOUT_REG		P4OUT
#define LCD_D7_PINOUT_REG		P4OUT
#define LCD_DX_PINOUT_REG		P4OUT
#define LCD_RS_PINOUT_REG		P2OUT
#define LCD_BK_PINOUT_REG		P2OUT
#define LCD_RW_PINOUT_REG		P3OUT
#define LCD_E_PINOUT_REG		P3OUT

// LCD GPIO port input register - must match GPIO port direction #defines
#define LCD_D0_PININ_REG		P4IN
#define LCD_D1_PININ_REG		P4IN
#define LCD_D2_PININ_REG		P4IN
#define LCD_D3_PININ_REG		P4IN
#define LCD_D4_PININ_REG		P4IN
#define LCD_D5_PININ_REG		P4IN
#define LCD_D6_PININ_REG		P4IN
#define LCD_D7_PININ_REG		P4IN
#define LCD_DX_PININ_REG		P4IN
#define LCD_RS_PININ_REG		P2IN
#define LCD_BK_PININ_REG		P2IN
#define LCD_RW_PININ_REG		P3IN
#define LCD_E_PININ_REG			P3IN

// LCD GPIO port direction register - 1 = OUT, 0 = IN (e.g. PxDIR for Px.y)
#define LCD_D0_PINDIR_REG		P4DIR
#define LCD_D1_PINDIR_REG		P4DIR
#define LCD_D2_PINDIR_REG		P4DIR
#define LCD_D3_PINDIR_REG		P4DIR
#define LCD_D4_PINDIR_REG		P4DIR
#define LCD_D5_PINDIR_REG		P4DIR
#define LCD_D6_PINDIR_REG		P4DIR
#define LCD_D7_PINDIR_REG		P4DIR
#define LCD_DX_PINDIR_REG		P4DIR
#define LCD_RS_PINDIR_REG		P2DIR
#define LCD_BK_PINDIR_REG		P2DIR
#define LCD_RW_PINDIR_REG		P3DIR
#define LCD_E_PINDIR_REG		P3DIR

// LCD GPIO channel mask (e.g. bit mask for bit 'y' in Px.y)
#define LCD_D0_PINBIT_MASK		BIT00_MASK
#define LCD_D1_PINBIT_MASK		BIT01_MASK
#define LCD_D2_PINBIT_MASK		BIT02_MASK
#define LCD_D3_PINBIT_MASK		BIT03_MASK
#define LCD_D4_PINBIT_MASK		BIT04_MASK
#define LCD_D5_PINBIT_MASK		BIT05_MASK
#define LCD_D6_PINBIT_MASK		BIT06_MASK
#define LCD_D7_PINBIT_MASK		BIT07_MASK
#define LCD_RS_PINBIT_MASK		BIT02_MASK
#define LCD_BK_PINBIT_MASK		BIT01_MASK
#define LCD_RW_PINBIT_MASK		BIT07_MASK
#define LCD_E_PINBIT_MASK		BIT06_MASK

/* ================================== Function Prototypes =================================== */

#endif
