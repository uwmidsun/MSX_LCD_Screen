#ifndef MAIN_CAN_BOARD_H
#define MAIN_CAN_BOARD_H

//
//
// Pin Definitions
// Port 1
#define CAN_nCS 		0x1
#define CAN_SCLK 		0x08
#define CAN_MOSI		0x02
#define CAN_MISO		0x04
//Port 3
#define CAN_nINT 		0x1

// Typedefs for quickly joining multiple bytes/ints/etc into larger values
// These rely on byte ordering in CPU & memory - i.e. they're not portable across architectures
typedef union _group_64 {
	float data_fp[2];
	unsigned char data_u8[8];
	unsigned int data_u16[4];
	unsigned long data_u32[2];
} group_64;

typedef union _group_32 {
	float data_fp;
	unsigned char data_u8[4];
	unsigned int data_u16[2];
	unsigned long data_u32;
} group_32;

typedef union _group_16 {
	unsigned char data_u8[2];
	unsigned int data_u16;
} group_16;


#endif /*MAIN_CAN_BOARD_H*/

