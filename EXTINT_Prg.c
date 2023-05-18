/*
 * EXTINT_Prg.c
 *
 *  Created on: Oct 11, 2021
 *      Author: haneenahmed
 */
#include"../LIB/stdtypes.h"
#include"../LIB/BIT_MATH.h"
#include "EXTINT_int.h"
#include "EXTINT_reg.h"
#define RT_OK    (u8)   0
#define RT_NOK   (u8)   1
#define NULL     (void*) 0
#define INT0_SC_CLR_MASK    (u8)0b11111100
#define INT1_SC_CLR_MASK    (u8)0b11110011
#define INT2_SC_CLR_MASK    (u8)0b10111111
volatile u8 Temp_Reg;
volatile u8 EN_Reg;
/*
 * Created a struct of pointer to function to use it in callBack
 */
typedef struct{
void (*INT_0)(void);
void (*INT_1)(void);
void (*INT_2)(void);
}EXTINT_N_PTR;



/*
 *creating a member (Pointer) from the struct
 */

EXTINT_N_PTR * ISR;

/*
 * A CallBack Function That takes the Argument (Pointer to Function(ptr))
 * (The function of ISR that you created before main)
 *  and Equalize it with The pointer to function (INT_0)
 *  Note that we asked if the pointer = Null or not before operation
 */

void set_call_back_INT0(void (*ptr)(void))
{
	if(ptr != NULL)
	{
		 ISR->INT_0 = ptr ;
	}
}
/*
 * Calling The Function that in the Pointer (ptr) by it's New Name (INT_0)
 * in the function of (Vector_1) to set ISR of INT_0
 *  Note that we asked if the pointer = Null or not before operation
 */

void __vector_1 (void)  __attribute__ ((signal,__INTR_ATTRS));
void __vector_1 (void)
{
	if(ISR->INT_0 != NULL)
	{
	ISR->INT_0();
	}
}

/*
 * A CallBack Function That takes the Argument (Pointer to Function(ptr))
 * (The function of ISR that you created before main)
 *  and Equalize it with The pointer to function (INT_1)
 *  Note that we asked if the pointer = Null or not before operation
 */
void set_call_back_INT1(void (*ptr)(void))
{
	if(ptr != NULL)
	{
		ISR->INT_1 = ptr ;
	}
}

/*
 * Calling The Function that in the Pointer (ptr) by it's New Name (INT_1)
 * in the function of (Vector_2) to set ISR of INT_1
 *  Note that we asked if the pointer = Null or not before operation
 */

void __vector_2 (void)  __attribute__ ((signal,__INTR_ATTRS));
void __vector_2 (void)
{
	if(ISR->INT_1  != NULL)
	{
	ISR->INT_1 ();
	}
}

/*
 * A CallBack Function That takes the Argument (Pointer to Function(ptr))
 * (The function of ISR that you created before main)
 *  and Equalize it with The pointer to function (INT_2)
 *  Note that we asked if the pointer = Null or not before operation
 */
void set_call_back_INT2(void (*ptr)(void))
{
	if(ptr != NULL)
	{
	ISR->INT_2 = ptr ;
	}
}

/*
 * Calling The Function that in the Pointer (ptr) by it's New Name (INT_1)
 * in the function of (Vector_2) to set ISR of INT_1
 *  Note that we asked if the pointer = Null or not before operation
 */
void __vector_3 (void)  __attribute__ ((signal,__INTR_ATTRS));
void __vector_3 (void)
{
	if(ISR->INT_2 != NULL)
	{
	ISR->INT_2();
	}
}

/*
 * A function to enable External Interrupt
 */

u8 EXTINT_u8Enable(u8 Copy_u8ExtInt)
{
	u8 Local_u8errStatus = RT_OK;
	S_REG |= GLOBAL_INTERRUPT_ENABLE;   //Enable GIE
	switch(Copy_u8ExtInt)
	{
	case INT0 : GIC_REG |= INT0_EN ; break;
	case INT1 : GIC_REG |= INT1_EN ; break;
	case INT2 : GIC_REG |= INT2_EN ; break;
	default : Local_u8errStatus = RT_NOK ;
	}
	return Local_u8errStatus;
}

/*
 * A function to disable External Interrupt
 */

u8 EXTINT_u8Disable(u8 Copy_u8ExtInt)
{
	u8 Local_u8errStatus = RT_OK;

	switch(Copy_u8ExtInt)
	{
	case INT0 : CLR_BIT(GIC_REG,6) ; break;
	case INT1 : CLR_BIT(GIC_REG,7) ; break;
	case INT2 : CLR_BIT(GIC_REG,5) ; break;
	case G_DIS : CLR_BIT(S_REG,7) ; break;
	default : Local_u8errStatus = RT_NOK;
	}
	return Local_u8errStatus;
}

/*
 * A function to Set sense control of interrupt by taking the arguments
 * (Interrupt Number , Status of sense control)
 */
u8 EXTINT_u8SenseCtrl(u8 Copy_u8ExtInt,u8 Copy_u8ISCStatus)
{
	u8 Local_u8errStatus = RT_OK;
	switch(Copy_u8ExtInt)
	{
	case INT0 :
		Temp_Reg = MCUC_REG;
		Temp_Reg &= INT0_SC_CLR_MASK;
		Temp_Reg |= Copy_u8ISCStatus;
		MCUC_REG = Temp_Reg;
		break;
	case INT1 :
		Temp_Reg = MCUC_REG;
		Temp_Reg &= INT1_SC_CLR_MASK;
		Temp_Reg |= Copy_u8ISCStatus;
		MCUC_REG = Temp_Reg;
		break;
	case INT2 :
		Temp_Reg = MCUCS_REG;
		Temp_Reg &= INT2_SC_CLR_MASK;
		Temp_Reg |= Copy_u8ISCStatus;
		MCUCS_REG = Temp_Reg;
		break;
	default : Local_u8errStatus = RT_NOK;
	}
	return Local_u8errStatus;
}

