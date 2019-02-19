/*
 * test.c
 *
 *  Created on: Feb 19, 2019
 *      Author: 500022
 */
#include <stdlib.h>
#include "test.h"
#include "r_cg_adc.h"

char Tests[][5] = { "N.L.", "R.P.", "S.C.", "O.L.", "O.V.", "16V ", "24V ",
		"32V " };

char TestsFull[][19] = { "     No  Load     ", " Reverse Voltage ",
		"  Short  Circuit  ", "    Over  Load    ", "   Over Voltage   ",
		"  Full Load  16V  ", "  Full Load  24V  ", "  Full Load  32V  " };
int noTests = sizeof(Tests) / sizeof(Tests[0]);
char resTests[8] = { 9, 9, 9, 9, 9, 9, 9, 9 };
int failedTest = -1;

#define TEST0COND (4.166 <= DUT_O_V && DUT_O_V <= 4.833)
#define TEST1COND (0 <= DUT_O_V && DUT_O_V <= 0.5)
#define TEST2COND (0 <= DUT_O_V && DUT_O_V <= 0.5)

float DUT_O_V = 0;

int test(int testNo) {
	int res = 9;

	switch (testNo) {
	case 0:
		DUT_O_V = (float) analogRead(1) / 1023.00 * 5.00;

		if (TEST0COND) {
			res = 1;
		} else {
			res = 0;
			failedTest = testNo;
		}

		break;
	case 1:
		DUT_O_V = (float) analogRead(1) / 1023.00 * 5.00;

		if (TEST1COND) {
			res = 1;
		} else {
			res = 0;
			failedTest = testNo;
		}
		break;
	case 2:
		DUT_O_V = (float) analogRead(1) / 1023.00 * 5.00;

		if (TEST2COND) {
			res = 1;
		} else {
			res = 0;
			failedTest = testNo;
		}
		break;
	default:
		res = 9;
	}

	resTests[testNo] = res;
	return res;
}
