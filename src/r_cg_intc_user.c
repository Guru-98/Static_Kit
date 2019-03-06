/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2012, 2018 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_intc_user.c
* Version      : CodeGenerator for RL78/F13 V2.03.03.01 [28 Oct 2018]
* Device(s)    : R5F10BGG
* Tool-Chain   : CCRL
* Description  : This file implements device driver for INTC module.
* Creation Date: 6/3/2019
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_intc.h"
/* Start user code for include. Do not edit comment generated here */
#include "r_cg_timer.h"
#include "display.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt r_key_interrupt(vect=INTKR)
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
volatile char _mem_key_f = 0;
volatile char _mem_key_t = 0;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_key_interrupt
* Description  : This function is INTKR interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_key_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
#if 1
	//TODO: Note to self... try smt else.
	DI();
	if (_mem_key_f == 0) {
		_mem_key_t++;
		delay(300);
		if (_mem_key_t == 3) {
			_mem_key_f ^= 1;
			_mem_key_t = 0;
		}
	}
	else{
		_mem_key_f = 0;
	}
	EI();
#else
	DI();
	if(_mem_key_f==0 && START_BTN == 1) {
		_mem_key_f = 1;
	}
	else {
		_mem_key_f = 0;
	}
	EI();
#endif

#if 1
	if (_mem_key_f == 1) {
		memoryScreen();
		while (MEMORY_BTN == 0)
			;
		revertScreenState();
	}
#else
	if (screenState != 1) {
		if (_mem_key_f == 1) {
			memoryScreen();
			while (MEMORY_BTN == 0)
			;
			revertScreenState();
		}
	} else {
		_mem_key_f = 0;
	}
#endif
	_mem_key_t=0;
	/* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
