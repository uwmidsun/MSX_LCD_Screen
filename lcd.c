/* *********************************** LCD.c ***********************************	*/
//
// LCD.c: contains functions relevant to the interfacing of LCD
// For all functions:
//		On entry: Assumes LCD enable line already off for some time
//		On exit: Leaves function with enabe line already off for some time
//
/* ********************************************************************************	*/

/* ================================== #include =================================== */

#include "lcd.h"
#include "globals.h"

/* ================================== Private Variable Declarations =================================== */

/* ---------------------------------- LCD Private Function Parameters ----------------------------------- */

// For function LCD_RunCommand(u8 DataMode, u8 ReadMode, u8 DataChar)
#define INSTRUCTION_MODE	0
#define DATA_MODE			1
#define WRITE_MODE			0
#define READ_MODE			1

/* ================================== Private Function Prototypes =================================== */

void LCD_Wait6us (vu16 Count);
u8 LCD_ReadChar(void);
void LCD_LoadChar(u8 DB_Char);
u8 LCD_RunCommand(u8 DataMode, u8 ReadMode, u8 DataChar);
void LCD_FunctionSetInit(void);

/* ================================== Private Function Definitions =================================== */

/* ~~~~~~~~~~~~~~~ LCD_Wait6us Function ~~~~~~~~~~~~~~~ */
// For DCO = approx 2MHz, this function has ~15us overhead, ~6us per NOP iteration
void LCD_Wait6us (vu16 Count) {
	while (Count--) {
		asm("blah1: nop");
	}
}

/* --------------- LCD_ReadChar Function --------------- */
// Note: This function assumes LCD data lines are already set as inputs
u8 LCD_ReadChar(void) {

	u8 DataChar = 0;

	DataChar |= LCD_GET_D7();
	DataChar <<= 1;
	DataChar |= LCD_GET_D6();
	DataChar <<= 1;
	DataChar |= LCD_GET_D5();
	DataChar <<= 1;
	DataChar |= LCD_GET_D4();
	DataChar <<= 1;
	DataChar |= LCD_GET_D3();
	DataChar <<= 1;
	DataChar |= LCD_GET_D2();
	DataChar <<= 1;
	DataChar |= LCD_GET_D1();
	DataChar <<= 1;
	DataChar |= LCD_GET_D0();

	return DataChar;
}

/* --------------- LCD_LoadChar Function --------------- */
// Helper: Loads parameter DB_Char to HW latch pins, but without changing LCD enable line
void LCD_LoadChar(u8 DB_Char) {

	if (DB_Char & 0x01) { // Pin 0
		LCD_SET_D0();
	}
	else {
		LCD_CLR_D0();
	}
	DB_Char >>= 1;

	if (DB_Char & 0x01) { // Pin 1
		LCD_SET_D1();
	}
	else {
		LCD_CLR_D1();
	}
	DB_Char >>= 1;

	if (DB_Char & 0x01) { // Pin 2
		LCD_SET_D2();
	}
	else {
		LCD_CLR_D2();
	}
	DB_Char >>= 1;

	if (DB_Char & 0x01) { // Pin 3
		LCD_SET_D3();
	}
	else {
		LCD_CLR_D3();
	}
	DB_Char >>= 1;

	if (DB_Char & 0x01) { // Pin 4
		LCD_SET_D4();
	}
	else {
		LCD_CLR_D4();
	}
	DB_Char >>= 1;

	if (DB_Char & 0x01) { // Pin 5
		LCD_SET_D5();
	}
	else {
		LCD_CLR_D5();
	}
	DB_Char >>= 1;

	if (DB_Char & 0x01) { // Pin 6
		LCD_SET_D6();
	}
	else {
		LCD_CLR_D6();
	}
	DB_Char >>= 1;

	if (DB_Char & 0x01) { // Pin 7
		LCD_SET_D7();
	}
	else {
		LCD_CLR_D7();
	}

}

/* --------------- LCD_RunCommand Function --------------- */
u8 LCD_RunCommand(u8 DataMode, u8 ReadMode, u8 DataChar) {
	u8 DataRetrieved = 0;

	LCD_Cmd_WaitTillReady();
	if (ReadMode) {
		LCD_SET_IN_DIR();
		LCD_READ_MODE();
		if (DataMode) {
			LCD_DATA_MODE();
		}
		else {
			LCD_INSTRUCTION_MODE();
		}
		LCD_Wait6us(1); // Wait 300ns min
		LCD_ENABLE();
		LCD_Wait6us(1); // Wait 1.2us min
		DataRetrieved = LCD_ReadChar();
		LCD_DISABLE();
		LCD_Wait6us(1); // Wait 300ns min
	}
	else {
		LCD_SET_OUT_DIR();
		LCD_LoadChar(DataChar);
		LCD_WRITE_MODE();
		if (DataMode) {
			LCD_DATA_MODE();
		}
		else {
			LCD_INSTRUCTION_MODE();
		}
		LCD_Wait6us(1); // Wait 300ns min
		LCD_ENABLE();
		LCD_Wait6us(1); // Wait 1.2us min
		LCD_DISABLE();
		LCD_Wait6us(1); // Wait 300ns min
		LCD_SET_IN_DIR();
	}
	LCD_Cmd_WaitTillReady();

	return DataRetrieved;
}

/* --------------- LCD_FunctionSetInit Function --------------- */
// Without using function 'LCD_Cmd_WaitTillReady()'
void LCD_FunctionSetInit(void) {
	LCD_DISABLE();
	LCD_SET_OUT_DIR();
	LCD_LoadChar(0x38); // 8-bit interface, two lines, 5x8 dots
	LCD_WRITE_MODE();
	LCD_INSTRUCTION_MODE();
	LCD_Wait6us(1);
	LCD_ENABLE();
	LCD_Wait6us(1);
	LCD_DISABLE();
	LCD_Wait6us(1);
	LCD_SET_IN_DIR();
}

/* ================================== Shared Function Definitions =================================== */

/* --------------- (extra) initLCDFunction --------------- */
void initLCD(void) {
	LCD_DISABLE();
	LCD_Wait6us(2500); // Wait 15ms min
	LCD_FunctionSetInit();
	LCD_Wait6us(682); // Wait 4.1ms min
	LCD_FunctionSetInit();
	LCD_Wait6us(15); // Wait 100us min
	LCD_FunctionSetInit();

	LCD_Cmd_FunctionSet(EIGHT_BIT_MODE | TWO_LINE_MODE | FIVE_BY_EIGHT_MODE);
	LCD_Cmd_DisplayConfig(DISPLAY_OFF | CURSOR_OFF | BLINK_OFF);
	LCD_Cmd_ClearAndHome();
	LCD_Cmd_ConfigEntryMode(CURSOR_INCREMENT | DISPLAY_SHIFT_OFF);
}

/* --------------- (extra) LCD_Cmd_ClearLine Function --------------- */
void LCD_Cmd_ClearLine(u8 LineNum) {
	u8 index;

	switch (LineNum) {

		case 1:
			LCD_Cmd_SetDdramAddr(LINE1_HOME_ADDR);
			break;

		case 2:
			LCD_Cmd_SetDdramAddr(LINE2_HOME_ADDR);
			break;

		case 3:
			LCD_Cmd_SetDdramAddr(LINE3_HOME_ADDR);
			break;

		case 4:
			LCD_Cmd_SetDdramAddr(LINE4_HOME_ADDR);
			break;

		default:
			break;
	}

	if (LineNum > 0 && LineNum <= NUM_OF_LINES) {
		for (index = 0; index < NUM_OF_CHAR_PER_LINE; index++) {
			LCD_Cmd_WriteData(' ');
		}
	}
}

/* --------------- (extra) LCD_Cmd_WriteLine Function --------------- */
void LCD_Cmd_WriteLine(u8 LineNum, char * LineData) {
	u8 index;
	u8 NullReached = FALSE;

	switch (LineNum) {

		case 1:
			LCD_Cmd_SetDdramAddr(LINE1_HOME_ADDR);
			break;

		case 2:
			LCD_Cmd_SetDdramAddr(LINE2_HOME_ADDR);
			break;

		case 3:
			LCD_Cmd_SetDdramAddr(LINE3_HOME_ADDR);
			break;

		case 4:
			LCD_Cmd_SetDdramAddr(LINE4_HOME_ADDR);
			break;

		default:
			break;
	}

	if (LineNum > 0 && LineNum <= NUM_OF_LINES) {
		for (index = 0; index < NUM_OF_CHAR_PER_LINE; index++) {

			if ((*LineData == '\0') || (NullReached)) { // null encountered, write blank
				LCD_Cmd_WriteData(' ');
				NullReached = TRUE;
			}
			else { // Null not yet encountered, write char to LCD
				LCD_Cmd_WriteData(*LineData);
				LineData++;
			}
		}
	}
}

/* --------------- (1) LCD_Cmd_ClearAndHome Function --------------- */
void LCD_Cmd_ClearAndHome(void) {
	LCD_RunCommand(INSTRUCTION_MODE, WRITE_MODE, 0x01);
}

/* --------------- (2) LCD_Cmd_Home Function --------------- */
void LCD_Cmd_Home(void) {
	LCD_RunCommand(INSTRUCTION_MODE, WRITE_MODE, 0x02);
}

/* --------------- (3) LCD_Cmd_ConfigEntryMode Function --------------- */
void LCD_Cmd_ConfigEntryMode(u8 DataChar) {
	LCD_RunCommand(INSTRUCTION_MODE, WRITE_MODE, 0x04 | DataChar);
}

/* --------------- (4) LCD_Cmd_DisplayConfig Function --------------- */
void LCD_Cmd_DisplayConfig(u8 DataChar) {
	LCD_RunCommand(INSTRUCTION_MODE, WRITE_MODE, 0x08 | DataChar);
}

/* --------------- (5) LCD_Cmd_ShiftControl Function --------------- */
void LCD_Cmd_ShiftControl(u8 DataChar) {
	LCD_RunCommand(INSTRUCTION_MODE, WRITE_MODE, 0x10 | DataChar);
}

/* --------------- (6) LCD_Cmd_FunctionSet --------------- */
void LCD_Cmd_FunctionSet(u8 DataChar) {
	LCD_RunCommand(INSTRUCTION_MODE, WRITE_MODE, 0x20 | DataChar);
}

/* --------------- (7) LCD_Cmd_SetCgramAddr Function --------------- */
void LCD_Cmd_SetCgramAddr(u8 Addr) {
	Addr &= ~0x80; // Ensure MSB in address char is 0
	LCD_RunCommand(INSTRUCTION_MODE, WRITE_MODE, 0x40 | Addr);
}

/* --------------- (8) LCD_Cmd_SetDdramAddr Function --------------- */
void LCD_Cmd_SetDdramAddr(u8 Addr) {
	LCD_RunCommand(INSTRUCTION_MODE, WRITE_MODE, 0x80 | Addr);
}

/* --------------- (9a) LCD_Cmd_WaitTillReady Function --------------- */
void LCD_Cmd_WaitTillReady(void) {
	u8 BusyFlag = 1;

	LCD_DISABLE();
	LCD_SET_IN_DIR();
	while (BusyFlag) {
		LCD_READ_MODE();
		LCD_INSTRUCTION_MODE();
		LCD_Wait6us(1); // Wait 300ns min
		LCD_ENABLE();
		LCD_Wait6us(1); // Wait 1.2us min
		BusyFlag = LCD_GET_D7();
		LCD_DISABLE();
		LCD_Wait6us(1); // Wait 300ns min
	}
}

/* --------------- (9b) LCD_Cmd_ReadCurrentAddr Function --------------- */
u8 LCD_Cmd_ReadCurrentAddr(void) {
	u8 DataChar = 0;

	DataChar = LCD_RunCommand(INSTRUCTION_MODE, READ_MODE, 0);
	DataChar &= ~0x80; // Ensure MSBit is not set (not used)

	return DataChar;
}

/* --------------- (10) LCD_Cmd_WriteData Function --------------- */
void LCD_Cmd_WriteData(u8 DataChar) {
	LCD_RunCommand(DATA_MODE, WRITE_MODE, DataChar);
}

/* --------------- (11) LCD_Cmd_ReadDataChar Function --------------- */
u8 LCD_Cmd_ReadDataChar(void) {
	return LCD_RunCommand(DATA_MODE, READ_MODE, 0);
}
