
/*============================================================================
 Name        : motor_steuerung.asm
 Author      : G. Massafra
 Version     : 1.0
 Copyright   : Miniproject, Module BTE505 - STGTS
 Description : This module implements two subroutines to steer Step Motor.

 Procedures  : Delay_Time  Delays time and sets the speed for Step Motor
               Step_Right  The Step Motor steers to the right
               Step_Left   The Step Motor steers to the left

 History     : 03.01.2019  GM Created
               08.01.2019  GM & JL brought file to work
               12.01.2019  GM Added Comments
               15.01.2019  Added alternative Motor outputs

 Reference	 : 
 ============================================================================*/

.syntax unified
.cpu cortex-m0
.fpu softvfp
.thumb

/**********************************************************************************/
/* export                                                                         */
/**********************************************************************************/

.global GPIO_Init
.global Step_Right
.global Step_Left

/**********************************************************************************/
/* register definitions                                                           */
/**********************************************************************************/

// Pins: PB2 (CN10 22), PB1 (CN10 24), PB15 (CN10 26), PB14 (CN10 28)
.set GPIOB_BSRR,	0x50000418		// Reset Value: 0000 0000

/**********************************************************************************/
/* Code                                                                           */
/**********************************************************************************/

	.text
	.align

/**********************************************************************************/
/*  Procedure   : Delay_Time                                                      */
/**********************************************************************************/
/*                                                                                */
/*  Function    : Time Delay to set the speed of the Step Motor. It is set to the */
/*                fastest speed possible. The loop lasts about 2.75ms.            */
/*                                                                                */
/*  Type        : Local                                                           */
/*                                                                                */
/*  Input Para  : none                                                            */
/*                                                                                */
/*  Output Para : none                                                            */
/*                                                                                */
/*  Author      : G. Massafra                                                     */
/*                                                                                */
/*  History     : 03.01.2019  GM created                                          */
/*                                                                                */
/**********************************************************************************/

Delay_Time:
	LDR     r3, =50000           // One clock cycle
Delay1:
	SUBS    r3,r3,#1            // One clock cycle
	BNE     Delay1              // Two clock cycles when jumping to Delay3,
	MOV		PC,LR               // 1 clock when continuing to DEC

/**********************************************************************************/
/*  End         : Delay_Time                                                      */
/**********************************************************************************/

/**********************************************************************************/
/*  Prozedur    : Step_Right                                                      */
/**********************************************************************************/
/*                                                                                */
/*  Function    : Steers Step Motor to the right direction.                       */
/*                                                                                */
/*  Type        : Global                                                          */
/*                                                                                */
/*  Input Para  : none                                                            */
/*                                                                                */
/*  Output Para : none                                                            */
/*                                                                                */
/*  Author      : G. Massafra                                                     */
/*                                                                                */
/*  History     : 11.03.2018  GM erstellt                                         */
/*                                                                                */
/**********************************************************************************/

Step_Right:

	PUSH	{lr}				// conserve value of Link Register
	LDR		r0,=GPIOB_BSRR		// address GPIOB Bit Set/Reset Register

	// Abfolge: 3, 4, 8, 9
	// Abfolge alternative Pins: 2, 1, 15, 14
 	// GPIO port bit set/reset register values for Step Motor
	LDR		r2, =0xFFFF0000		// Value for Bit_RESET GPIOB
	STR		r2,[r0]				// Reset GPIOB pins
//	LDR		r1, =0x00000004		// Value for Bit_SET GPIOB pin 2
//	LDR		r1, =0x00000008		// Value for Bit_SET GPIOB pin 3
	LDR		r1, =0x0000000C		// Value for Bit_SET GPIOB normal and alternative pins
	STR		r1,[r0]				// Set GPIOB both motor pins
	BL		Delay_Time			// Wait for about 2.75ms
	STR		r2,[r0]				// Reset GPIOB both motor pins
//	LDR		r1, =0x00000002		// Value for Bit_SET GPIOB pin 1
//	LDR		r1, =0x00000010		// Value for Bit_SET GPIOB pin 4
	LDR		r1, =0x00000012		// Value for Bit_SET GPIOB normal and alternative pins
	STR		r1,[r0]				// Set GPIOB both motor pins
	BL		Delay_Time			// Wait for about 2.75ms
	STR		r2,[r0]				// Reset GPIOB both motor pins
//	LDR		r1, =0x00008000		// Value for Bit_SET GPIOB pin 15
//	LDR		r1, =0x00000100		// Value for Bit_SET GPIOB pin 8
	LDR		r1, =0x00008100		// Value for Bit_SET GPIOB normal and alternative pins
	STR		r1,[r0]				// Set GPIOB both motor pins
	BL		Delay_Time			// Wait for about 2.75ms
	STR		r2,[r0]				// Reset GPIOB both motor pins
//	LDR		r1, =0x00004000		// Value for Bit_SET GPIOB pin 14
//	LDR		r1, =0x00000200		// Value for Bit_SET GPIOB pin 9
	LDR		r1, =0x00004200		// Value for Bit_SET GPIOB normal and alternative pins
	STR		r1,[r0]				// Set GPIOB both motor pins
	BL		Delay_Time			// Wait for about 2.75ms
	STR		r2,[r0]				// Reset GPIOB both motor pins

	POP		{pc}				// return

/**********************************************************************************/
/*  End         : Step_Right                                                      */
/**********************************************************************************/

/**********************************************************************************/
/*  Prozedur    : Step_Left                                                       */
/**********************************************************************************/
/*                                                                                */
/*  Function    : Steers Step Motor to the left direction.                        */
/*                                                                                */
/*  Type        : Global                                                          */
/*                                                                                */
/*  Input Para  : none                                                            */
/*                                                                                */
/*  Output Para : none                                                            */
/*                                                                                */
/*  Author      : G. Massafra                                                     */
/*                                                                                */
/*  History     : 11.03.2018  GM erstellt                                         */
/*                                                                                */
/**********************************************************************************/

Step_Left:

	PUSH	{lr}
	LDR		r0,=GPIOB_BSRR		// address GPIOB Bit Set/Reset Register

	// Abfolge: 9, 8, 4, 3
	// Abfolge alternative Pins: 14, 15, 1, 2
 	// GPIO port bit set/reset register values for Step Motor
	LDR		r2, =0xFFFF0000		// Value for Bit_RESET GPIOB
	STR		r2,[r0]				// Reset GPIOB pins
//	LDR		r1, =0x00004000		// Value for Bit_SET GPIOB pin 14
//	LDR		r1, =0x00000200		// Value for Bit_SET GPIOB pin 9
	LDR		r1, =0x00004200		// Value for Bit_SET GPIOB normal and alternative pins
	STR		r1,[r0]				// Set GPIOB both motor pins
	BL		Delay_Time			// Wait for about 2.75ms
	STR		r2,[r0]				// Reset GPIOB both motor pins
//	LDR		r1, =0x00008000		// Value for Bit_SET GPIOB pin 15
//	LDR		r1, =0x00000100		// Value for Bit_SET GPIOB pin 8
	LDR		r1, =0x00008100		// Value for Bit_SET GPIOB normal and alternative pins
	STR		r1,[r0]				// Set GPIOB both motor pins
	BL		Delay_Time			// Wait for about 2.75ms
	STR		r2,[r0]				// Reset GPIOB both motor pins
//	LDR		r1, =0x00000002		// Value for Bit_SET GPIOB pin 1
//	LDR		r1, =0x00000010		// Value for Bit_SET GPIOB pin 4
	LDR		r1, =0x00000012		// Value for Bit_SET GPIOB normal and alternative pins
	STR		r1,[r0]				// Set GPIOB both motor pins
	BL		Delay_Time			// Wait for about 2.75ms
	STR		r2,[r0]				// Reset GPIOB both motor pins
//	LDR		r1, =0x00000004		// Value for Bit_SET GPIOB pin 2
//	LDR		r1, =0x00000008		// Value for Bit_SET GPIOB pin 3
	LDR		r1, =0x0000000C		// Value for Bit_SET GPIOB normal and alternative pins
	STR		r1,[r0]				// Set GPIOB both motor pins
	BL		Delay_Time			// Wait for about 2.75ms
	STR		r2,[r0]				// Reset GPIOB both motor pins

	POP		{pc}				// return

/**********************************************************************************/
/*  End         : Step_Left                                                       */
/**********************************************************************************/

/**********************************************************************************/
/*  End         : motor_steuerung.asm                                             */
/**********************************************************************************/
