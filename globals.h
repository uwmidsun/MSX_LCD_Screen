/* *********************************** globals.h *********************************** */
//
// Function: Includes all global variables
//
/* ********************************************************************************	*/

#ifndef GLOBALS_H
#define GLOBALS_H

/* ================================== #includes =================================== */

#include <msp430f2272.h>

/* =================================== Variable Declarations =================================== */

/* ---------------------------------- General ----------------------------------- */

#define ON	1
#define OFF	0

#define TRUE	1
#define FALSE	0

#define BIT00_MASK	0x0001
#define BIT01_MASK	0x0002
#define BIT02_MASK	0x0004
#define BIT03_MASK	0x0008
#define BIT04_MASK	0x0010
#define BIT05_MASK	0x0020
#define BIT06_MASK	0x0040
#define BIT07_MASK	0x0080
#define BIT08_MASK	0x0100
#define BIT09_MASK	0x0200
#define BIT10_MASK	0x0400
#define BIT11_MASK	0x0800
#define BIT12_MASK	0x1000
#define BIT13_MASK	0x2000
#define BIT14_MASK	0x4000
#define BIT15_MASK	0x8000

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

#define S8_MAX 0x7F
#define U8_MAX 0xFF
#define S16_MAX 0x7FFF
#define U16_MAX 0xFFFF
#define S32_MAX 0x7FFFFFFF
#define U32_MAX 0xFFFFFFFF

#endif

/* ---------------------------------- Global Variables ----------------------------------- */

extern u8 TimerA0_Flag;

/* ================================== Function Prototypes =================================== */

void Wait_TimerA0(void);
