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
* File Name    : r_cg_userdefine.h
* Version      : CodeGenerator for RL78/F13 V2.03.03.01 [28 Oct 2018]
* Device(s)    : R5F10BGG
* Tool-Chain   : CCRL
* Description  : This file includes user definition.
* Creation Date: 3/6/2019
***********************************************************************************************************************/

#ifndef _USER_DEF_H
#define _USER_DEF_H

/***********************************************************************************************************************
User definitions
***********************************************************************************************************************/

/* Start user code for function. Do not edit comment generated here */
#include "r_cg_macrodriver.h"

/* SCH DEF */
#if 1
#define MC_in01 (P12_bit.no0)
#define MC_in02 (P4_bit.no1)
#define MC_in03 (P13_bit.no0) //TODO: Pin cannot be used as IP
#define MC_in04 (P7_bit.no3)
#define MC_in05 (P7_bit.no2)
#define MC_in06 (P14_bit.no0)
#define MC_in07 (P12_bit.no4)
#define MC_in08 (P12_bit.no3)
#define MC_in09 (P12_bit.no2)
#define MC_in10 (P12_bit.no1)
#define MC_in11 (P6_bit.no3)
#define MC_in12 (P6_bit.no0)

#define MC_out01 (P7_bit.no1)
#define MC_out02 (P7_bit.no0)
#define MC_out03 (P3_bit.no2)
#define MC_out04 (P8_bit.no5)
#define MC_out05 (P8_bit.no6)
#define MC_out06 (P8_bit.no7)
#define MC_out07 (P9_bit.no0)
#define MC_out08 (P9_bit.no1)
#define MC_out09 (P9_bit.no2)
#define MC_out10 (P12_bit.no5)

#define Dif_out_1 (P8_bit.no3)
#define Dif_out_2 (P8_bit.no4)
#define Buf_out_3 (P8_bit.no0)
#define Buf_out_4 (P8_bit.no1)
#define Buf_out_5 (P8_bit.no2)

#define ZCD_in1 (P13_bit.no7)
#define ZCD_in2 (P0_bit.no0)

#endif

/* LCD DEF */
#define DB P1

#define EN (P3_bit.no1)
#define RS (P3_bit.no0)

/* DUT DEF */

#define DUT_I_V 0
#define DUT_I_C 0

#if 0
#define DUT_O_V Buf_out_3
#define DUT_O_C Dif_out_2
#else
#define DUT_O_V 3
#define DUT_O_C 6
#endif

/* SMPS DEF */
#define SMPS_16V MC_out03
#define SMPS_24V MC_out01
#define SMPS_N24V MC_out05
#define SMPS_32V MC_out04
#define SMPS_42V MC_out02

/* Load DEF */
#define LOAD MC_out07
#define SHORT MC_out06
#define EXTRA_LOAD MC_out08

/* Buttons */
#define START_BTN MC_in01
#define RESET_BTN MC_in02
#define MEMORY_BTN MC_in05

/* LEDS */
#define GRN_LED MC_out10
#define RED_LED MC_out09

/* End user code. Do not edit comment generated here */
#endif
