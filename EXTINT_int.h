/*
 * EXTINT_int.h
 *
 *  Created on: Oct 11, 2021
 *      Author: haneenahmed
 */
#include "stdtypes.h"
#ifndef EXTINT_V1_EXTINT_INT_H_
#define EXTINT_V1_EXTINT_INT_H_
/*
 * EXTINT0 = PD2
 * EXTINT1 = PD3
 * EXTINT2 = PB2
 */
#define INT0                         (u8)   0
#define INT1                         (u8)   1
#define INT2                         (u8)   2
#define G_DIS                        (u8)   3

#define INT0_EN                      (u8)0b01000000
#define INT1_EN                      (u8)0b10000000
#define INT2_EN                      (u8)0b00100000
#define GLOBAL_INTERRUPT_ENABLE      (u8)0b10000000


typedef enum
{
	EXT_INT_0_SC_eINT0_LOW_LEVEL_EN = 0b00000000,
	EXT_INT_0_SC_eINT0_LOGIC_CHG_EN = 0b00000001,
	EXT_INT_0_SC_eINT0_FALL_EDGE_EN = 0b00000010,
	EXT_INT_0_SC_eINT0_RISE_EDGE_EN = 0b00000011
}EXT_INT_0_SC_e;

typedef enum
{
	EXT_INT_1_SC_eINT1_LOW_LEVEL_EN = 0b00000000,
	EXT_INT_1_SC_eINT1_LOGIC_CHG_EN = 0b00000100,
	EXT_INT_1_SC_eINT1_FALL_EDGE_EN = 0b00001000,
	EXT_INT_1_SC_eINT1_RISE_EDGE_EN = 0b00001100
}EXT_INT_1_SC_e;

typedef enum
{
	EXT_INT_2_SC_eINT2_FALL_EDGE_EN = 0b00000000,
	EXT_INT_2_SC_eINT2_RISE_EDGE_EN = 0b01000000
}EXT_INT_2_SC_e;





u8 EXTINT_u8Enable(u8 Copy_u8ExtInt);
u8 EXTINT_u8Disable(u8 Copy_u8ExtInt);
u8 EXTINT_u8SenseCtrl(u8 Copy_u8ExtInt,u8 Copy_u8ISCStatus);
void set_call_back_INT0(void (*ptr)(void));
void set_call_back_INT1(void (*ptr)(void));
void set_call_back_INT2(void (*ptr)(void));
#endif /* ISR_V1_ISR_INT_H_ */
