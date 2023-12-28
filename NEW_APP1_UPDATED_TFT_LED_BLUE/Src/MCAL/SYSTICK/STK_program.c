/*********************************************************/
/********** Author 		: Mahmoud Korayem ****************/
/********** Date        : 11 SEP 2020     ****************/
/********** version     : V 01			  ****************/
/********** Description : STK-private.h   ****************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "../Inc/MCAL/SYSTICK/STK_interface.h"
#include "../Inc/MCAL/SYSTICK/STK_private.h"
#include "../Inc/MCAL/SYSTICK/STK_config.h"

u8 remaining_sec=0;
/* Define Callback Global Variable */
static void(*MSTK_CallBack)(void);

/* Define Variable for interval mode */
static u8 MSTK_u8ModeOfInterval;

void MSTK_voidInit(void)
{
#if MSTK_CLK_SRC == MSTK_SRC_AHB
    /* Disable STK - Disable STK Interrupt - Set clock source AHB */
	MSTK -> CTRL = 0x00000004;
#else
    /* Disable STK - Disable STK Interrupt - Set clock source AHB/8 */
	MSTK -> CTRL = 0;
	
#endif
}

void MSTK_voidSetBusyWait( u32 Copy_u32Ticks )
{
	/* Load ticks to load register */
	MSTK -> LOAD = Copy_u32Ticks;
	
	/* Start Timer */
	SET_BIT(MSTK->CTRL, 0);
	
	/* Wait till flag is raised */
	while( (GET_BIT(MSTK->CTRL,16)) == 0);
	
	/* Stop Timer */
	SET_BIT(MSTK->CTRL, 0);
	MSTK -> LOAD = 0;
	MSTK -> VAL  = 0;
	
}
void MSTK_voidSetIntervalSec(u8 sec ,void (*Copy_ptr)(void))
{
	/* Disable Timer */
	CLR_BIT(MSTK->CTRL,0);
	MSTK -> VAL = 0;
	if(sec<16)
	{
		/* Load ticks to load register */
		MSTK -> LOAD = sec*1000000;
	}
	if(sec>16)
	{
		/* Load ticks to load register */
		MSTK -> LOAD = 15*1000000;
		remaining_sec = sec-15;
	}
	/* Start Timer */
	SET_BIT(MSTK->CTRL, 0);
	/* Save CallBack */
	MSTK_CallBack = Copy_ptr;
	/* Set Mode to Single */
	MSTK_u8ModeOfInterval = MSTK_SINGLE_INTERVAL;
	/* Enable STK Interrupt */
	SET_BIT(MSTK->CTRL, 1);
}
void MSTK_voidSetIntervalSingle  ( u32 Copy_u32Ticks, void (*Copy_ptr)(void) )
{
	/* Disable Timer */
	CLR_BIT(MSTK->CTRL,0);
	MSTK -> VAL = 0;
	/* Load ticks to load register */
	MSTK -> LOAD = Copy_u32Ticks;
	/* Start Timer */
	SET_BIT(MSTK->CTRL, 0);
	/* Save CallBack */
	MSTK_CallBack = Copy_ptr;
	/* Set Mode to Single */
	MSTK_u8ModeOfInterval = MSTK_SINGLE_INTERVAL;
	/* Enable STK Interrupt */
	SET_BIT(MSTK->CTRL, 1);
}


void MSTK_voidSetIntervalPeriodic( u32 Copy_u32Ticks, void (*Copy_ptr)(void) )
{
	/* Load ticks to load register */
	MSTK -> LOAD = Copy_u32Ticks;
	
	/* Start Timer */
	SET_BIT(MSTK->CTRL, 0);
	
	/* Save CallBack */
	MSTK_CallBack = Copy_ptr;
	
	/* Set Mode to Single */
	MSTK_u8ModeOfInterval = MSTK_PERIOD_INTERVAL;
	
	/* Enable STK Interrupt */
	SET_BIT(MSTK->CTRL, 1);
}

void MSTK_voidStopInterval(void)
{
	/* Disable STK Interrupt */
	CLR_BIT(MSTK->CTRL, 1);
	
	/* Stop Timer */
	SET_BIT(MSTK->CTRL, 0);
	MSTK -> LOAD = 0;
	MSTK -> VAL  = 0;
}

u32  MSTK_u32GetElapsedTime(void)
{
	u32 Local_u32ElapsedTime;
	
	Local_u32ElapsedTime = MSTK -> LOAD - MSTK -> VAL ;
	
	return Local_u32ElapsedTime;
}

u32  MSTK_u32GetRemainingTime(void)
{
	u32 Local_u32RemainTime;
	
	Local_u32RemainTime = MSTK -> VAL ;
	
	return Local_u32RemainTime;
}

void SysTick_Handler(void)
{
	u8 Local_u8Temporary ;
	
	if (remaining_sec!=0)
	{
		//remaiming_sec=0;
		/* Disable Timer */
		CLR_BIT(MSTK->CTRL,0);
		MSTK -> VAL = 0;
		if(remaining_sec<15)
		{
			/* Load ticks to load register */
			MSTK -> LOAD = remaining_sec*1000000;
			remaining_sec=0;
		}
		if(remaining_sec>15)
		{
			/* Load ticks to load register */
			MSTK -> LOAD = 15*1000000;
			remaining_sec = remaining_sec-15;
		}
		/* Start Timer */
		SET_BIT(MSTK->CTRL, 0);
		/* Set Mode to Single */
		MSTK_u8ModeOfInterval = MSTK_SINGLE_INTERVAL;
		/* Enable STK Interrupt */
		SET_BIT(MSTK->CTRL, 1);
	}
	else if ((MSTK_u8ModeOfInterval == MSTK_SINGLE_INTERVAL) && (remaining_sec==0))
	{
		/* Disable STK Interrupt */
		CLR_BIT(MSTK->CTRL, 1);
	
		/* Stop Timer */
		SET_BIT(MSTK->CTRL, 0);
		MSTK -> LOAD = 0;
		MSTK -> VAL  = 0;

		/* Callback notification */
		MSTK_CallBack();
	}

	
	/* Clear interrupt flag */
	Local_u8Temporary = GET_BIT(MSTK->CTRL,16);
}