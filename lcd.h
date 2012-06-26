/* *********************************** LCD.h ***********************************	*/
//
// Function: contains necessary interface to code contained in LCD.c
//
/* ********************************************************************************	*/

#ifndef LCD_H
#define LCD_H

/* ================================== #includes =================================== */

#include "init.h"
#include "globals.h"

/* ================================== #defines =================================== */

/* --------------- Macros --------------- */

// LCD Macros for Setting/Clearing GPIO States (these macros assumes PINDIR = OUT)
#define LCD_SET_D0()	LCD_DX_PINOUT_REG|=LCD_D0_PINBIT_MASK
#define LCD_SET_D1()	LCD_DX_PINOUT_REG|=LCD_D1_PINBIT_MASK
#define LCD_SET_D2()	LCD_DX_PINOUT_REG|=LCD_D2_PINBIT_MASK
#define LCD_SET_D3()	LCD_DX_PINOUT_REG|=LCD_D3_PINBIT_MASK
#define LCD_SET_D4()	LCD_DX_PINOUT_REG|=LCD_D4_PINBIT_MASK
#define LCD_SET_D5()	LCD_DX_PINOUT_REG|=LCD_D5_PINBIT_MASK
#define LCD_SET_D6()	LCD_DX_PINOUT_REG|=LCD_D6_PINBIT_MASK
#define LCD_SET_D7()	LCD_DX_PINOUT_REG|=LCD_D7_PINBIT_MASK
#define LCD_SET_RS()	LCD_RS_PINOUT_REG|=LCD_RS_PINBIT_MASK	// Data mode
#define LCD_SET_RW()	LCD_RW_PINOUT_REG|=LCD_RW_PINBIT_MASK	// Read mode
#define LCD_SET_E()		LCD_E_PINOUT_REG|=LCD_E_PINBIT_MASK		// Enable LCD
#define LCD_CLR_D0()	LCD_DX_PINOUT_REG&=~LCD_D0_PINBIT_MASK
#define LCD_CLR_D1()	LCD_DX_PINOUT_REG&=~LCD_D1_PINBIT_MASK
#define LCD_CLR_D2()	LCD_DX_PINOUT_REG&=~LCD_D2_PINBIT_MASK
#define LCD_CLR_D3()	LCD_DX_PINOUT_REG&=~LCD_D3_PINBIT_MASK
#define LCD_CLR_D4()	LCD_DX_PINOUT_REG&=~LCD_D4_PINBIT_MASK
#define LCD_CLR_D5()	LCD_DX_PINOUT_REG&=~LCD_D5_PINBIT_MASK
#define LCD_CLR_D6()	LCD_DX_PINOUT_REG&=~LCD_D6_PINBIT_MASK
#define LCD_CLR_D7()	LCD_DX_PINOUT_REG&=~LCD_D7_PINBIT_MASK
#define LCD_CLR_RS()	LCD_RS_PINOUT_REG&=~LCD_RS_PINBIT_MASK	// Instructions mode
#define LCD_CLR_RW()	LCD_RW_PINOUT_REG&=~LCD_RW_PINBIT_MASK	// Write mode
#define LCD_CLR_E()		LCD_E_PINOUT_REG&=~LCD_E_PINBIT_MASK	// Disable LCD

// LCD Macros for reading GPIO states
#define LCD_GET_D0()	(LCD_DX_PININ_REG&LCD_D0_PINBIT_MASK?1:0)
#define LCD_GET_D1()	(LCD_DX_PININ_REG&LCD_D1_PINBIT_MASK?1:0)
#define LCD_GET_D2()	(LCD_DX_PININ_REG&LCD_D2_PINBIT_MASK?1:0)
#define LCD_GET_D3()	(LCD_DX_PININ_REG&LCD_D3_PINBIT_MASK?1:0)
#define LCD_GET_D4()	(LCD_DX_PININ_REG&LCD_D4_PINBIT_MASK?1:0)
#define LCD_GET_D5()	(LCD_DX_PININ_REG&LCD_D5_PINBIT_MASK?1:0)
#define LCD_GET_D6()	(LCD_DX_PININ_REG&LCD_D6_PINBIT_MASK?1:0)
#define LCD_GET_D7()	(LCD_DX_PININ_REG&LCD_D7_PINBIT_MASK?1:0)

// LCD Macros
#define LCD_DATA_MODE()			LCD_SET_RS()	// set data mode
#define LCD_INSTRUCTION_MODE()	LCD_CLR_RS()	// set instruction mode
#define LCD_READ_MODE()			LCD_SET_RW()	// set read mode
#define LCD_WRITE_MODE()		LCD_CLR_RW()	// set write mode
#define LCD_ENABLE()			LCD_SET_E()		// enable LCD
#define LCD_DISABLE()			LCD_CLR_E()		// disable LCD
#define LCD_SET_OUT_DIR()		LCD_DX_PINDIR_REG|=LCD_D0_PINBIT_MASK; \
								LCD_DX_PINDIR_REG|=LCD_D1_PINBIT_MASK; \
								LCD_DX_PINDIR_REG|=LCD_D2_PINBIT_MASK; \
								LCD_DX_PINDIR_REG|=LCD_D3_PINBIT_MASK; \
								LCD_DX_PINDIR_REG|=LCD_D4_PINBIT_MASK; \
								LCD_DX_PINDIR_REG|=LCD_D5_PINBIT_MASK; \
								LCD_DX_PINDIR_REG|=LCD_D6_PINBIT_MASK; \
								LCD_DX_PINDIR_REG|=LCD_D7_PINBIT_MASK;
#define LCD_SET_IN_DIR()		LCD_DX_PINDIR_REG&=~LCD_D0_PINBIT_MASK; \
								LCD_DX_PINDIR_REG&=~LCD_D1_PINBIT_MASK; \
								LCD_DX_PINDIR_REG&=~LCD_D2_PINBIT_MASK; \
								LCD_DX_PINDIR_REG&=~LCD_D3_PINBIT_MASK; \
								LCD_DX_PINDIR_REG&=~LCD_D4_PINBIT_MASK; \
								LCD_DX_PINDIR_REG&=~LCD_D5_PINBIT_MASK; \
								LCD_DX_PINDIR_REG&=~LCD_D6_PINBIT_MASK; \
								LCD_DX_PINDIR_REG&=~LCD_D7_PINBIT_MASK;

/* --------------- LCD Shared Functions' Parameters --------------- */

// For command (3) LCD_Cmd_ConfigEntryMode(u8 DataChar)
#define CURSOR_INCREMENT	0x02
#define CURSOR_DECREMENT	0x00
#define DISPLAY_SHIFT_ON	0x01
#define DISPLAY_SHIFT_OFF	0x00

// For command (4) LCD_Cmd_DisplayConfig(u8 DataChar)
#define DISPLAY_ON			0x04
#define DISPLAY_OFF			0x00
#define CURSOR_ON			0x02
#define CURSOR_OFF			0x00
#define BLINK_ON			0x01
#define BLINK_OFF			0x00

// For command (5) LCD_Cmd_ShiftControl(u8 DataChar)
#define DISPLAY_SHIFT		0X08
#define CURSOR_SHIFT		0X00
#define SHIFT_RIGHT			0X04
#define SHIFT_LEFT			0x00

// For command (6) LCD_Cmd_FunctionSet(u8 DataChar)
#define FOUR_BIT_MODE		0x00
#define EIGHT_BIT_MODE		0x10
#define ONE_LINE_MODE		0x00
#define TWO_LINE_MODE		0x08
#define FIVE_BY_EIGHT_MODE	0x00
#define FIVE_BY_ELEVEN_MODE	0x04

/* --------------- LCD Info --------------- */

#define LINE1_HOME_ADDR			0x00
#define LINE1_LAST_ADDR			0x13
#define LINE2_HOME_ADDR			0x40
#define LINE2_LAST_ADDR			0x53
#define LINE3_HOME_ADDR			0x14
#define LINE3_LAST_ADDR			0x27
#define LINE4_HOME_ADDR			0x54
#define LINE4_LAST_ADDR			0x67
#define NUM_OF_CHAR_PER_LINE	20
#define NUM_OF_LINES			4

/* ================================== Shared Function Prototypes =================================== */

void initLCD(void);
void LCD_Cmd_ClearLine(u8 LineNum);
void LCD_Cmd_WriteLine(u8 LineNum, char * LineData);
void LCD_Cmd_ClearAndHome(void);
void LCD_Cmd_Home(void);
void LCD_Cmd_ConfigEntryMode(u8 DataChar);
void LCD_Cmd_DisplayConfig(u8 DataChar);
void LCD_Cmd_ShiftControl(u8 DataChar);
void LCD_Cmd_FunctionSet(u8 DataChar);
void LCD_Cmd_SetCgramAddr(u8 Addr);
void LCD_Cmd_SetDdramAddr(u8 AC);
void LCD_Cmd_WaitTillReady(void);
u8 LCD_Cmd_ReadCurrentAddr(void);
void LCD_Cmd_WriteData(u8 DataChar);
u8 LCD_Cmd_ReadDataChar(void);

#endif
