/* 
* 
* Pin Definitions and masks 
* chip MSP430F272 
* 
* Author: Xin Jin 
* 
* Last modified : July 10th, 2011
* 
*/ 


#include <msp430x12x2.h>

//Boolean Defintions 

#define ON	1
#define OFF	0

#define TRUE	1
#define FALSE	0

//Mask Definitions 

#define BIT_00_MASK				0x0001
#define BIT_01_MASK				0x0002
#define BIT_02_MASK				0x0004
#define BIT_03_MASK				0x0008
#define BIT_04_MASK				0x0010
#define BIT_05_MASK				0x0020
#define BIT_06_MASK				0x0040
#define BIT_07_MASK				0x0080
#define BIT_08_MASK				0x0100
#define BIT_09_MASK				0x0200
#define BIT_10_MASK				0x0400
#define BIT_11_MASK				0x0800
#define BIT_12_MASK				0x1000
#define BIT_13_MASK				0x2000
#define BIT_14_MASK				0x4000
#define BIT_15_MASK				0x8000

//Pin Defintions for MSP430 

//Port 1 
#define P1_UNUSED				BIT_00_MASK | BIT_01_MASK | BIT_02_MASK | BIT_03_MASK
#define P1_Progamming_Head		BIT_04_MASK |  BIT_05_MASK | BIT_06_MASK | BIT_07_MASK
	
//Port 2 

#define CAN_int_pin 			BIT_00_MASK
#define LCD_BK  				BIT_01_MASK 
#define LCD_RE 					BIT_02_MASK
#define Panel_SW1				BIT_03_MASK
#define Panel_SW2				BIT_04_MASK 
#define ROSC					BIT_05_MASK
#define XIN 					BIT_06_MASK
#define XOUT 					BIT_07_MASK

//Port 3

#define CAN_nCS					BIT_00_MASK
#define CAN_MOSI				BIT_01_MASK
#define CAN_MISO 				BIT_02_MASK
#define CAN_SCLK				BIT_03_MASK
#define UART_TX					BIT_04_MASK
#define UART_RX 				BIT_05_MASK
#define LCD_E 					BIT_06_MASK
#define LCD_RW					BIT_07_MASK

//Port 4 

//LCD GPIO channel mask (e.g. bit mask for bit 'y' in Px.y)
#define LCD_D0_PINBIT_MASK		BIT_00_MASK
#define LCD_D1_PINBIT_MASK		BIT_01_MASK
#define LCD_D2_PINBIT_MASK		BIT_02_MASK
#define LCD_D3_PINBIT_MASK		BIT_03_MASK
#define LCD_D4_PINBIT_MASK		BIT_04_MASK
#define LCD_D5_PINBIT_MASK		BIT_05_MASK
#define LCD_D6_PINBIT_MASK		BIT_06_MASK
#define LCD_D7_PINBIT_MASK		BIT_07_MASK
#define LCD_RS_PINBIT_MASK		BIT_02_MASK
#define LCD_RW_PINBIT_MASK		BIT_07_MASK
#define LCD_E_PINBIT_MASK		BIT_06_MASK

//LCD definitions 

// LCD GPIO port output register - must match GPIO port direction #defines
#define LCD_DX_PINOUT_REG		P4OUT
#define LCD_RS_PINOUT_REG		P2OUT
#define LCD_RW_PINOUT_REG		P3OUT
#define LCD_E_PINOUT_REG		P3OUT

// LCD GPIO port input register - must match GPIO port direction #defines
#define LCD_DX_PININ_REG		P4IN
#define LCD_RS_PININ_REG		P2IN
#define LCD_RW_PININ_REG		P3IN
#define LCD_E_PININ_REG			P3IN

// LCD GPIO port direction register - 1 = OUT, 0 = IN (e.g. PxDIR for Px.y)
#define LCD_DX_PINDIR_REG		P4DIR
#define LCD_RS_PINDIR_REG		P2DIR
#define LCD_RW_PINDIR_REG		P3DIR
#define LCD_E_PINDIR_REG		P3DIR


//Type Definitions 

typedef char s8;
typedef volatile char vs8;
typedef unsigned char u8;
typedef volatile unsigned char vu8;

typedef int s16;
typedef volatile int vs16;
typedef unsigned int u16;
typedef volatile unsigned int vu16;

typedef long s32;
typedef volatile long vs32;
typedef unsigned long u32;
typedef volatile unsigned long vu32;

// Typedefs for quickly joining multiple bytes/ints/etc into larger values
// These rely on byte ordering in CPU & memory - i.e. they're not portable across architectures




#define S8_MAX 0x7F
#define U8_MAX 0xFF
#define S16_MAX 0x7FFF
#define U16_MAX 0xFFFF
#define S32_MAX 0x7FFFFFFF
#define U32_MAX 0xFFFFFFFF


/* ---------------------------------- Global Variables ----------------------------------- */

extern u8 TimerA0_Flag;

/* ================================== Function Prototypes =================================== */

void Wait_TimerA0(void);

