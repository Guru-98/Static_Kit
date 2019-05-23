/*
 * test.c
 *
 *  Created on: Feb 19, 2019
 *      Author: 500022
 */

#include "test.h"
#include "display.h"
#include "eeprom.h"

#include "r_cg_userdefine.h"
#include "r_cg_intc.h"
#include "r_cg_timer.h"
#include "r_cg_adc.h"

char Tests[][5] = { "N.L.", "S.C.", "24V ", "R.P.", "16V ", "O.V.", "32V ",
		"O.L." };

char TestsFull[][19] = { "High/ Low/ No - OP", "  Short  Circuit  ",
		"  Full Load  24V  ", " Reverse Voltage ", "  Full Load  16V  ",
		"   Over Voltage   ", "  Full Load  32V ", "    Over  Load    ",
		"    OL/NL/24 V    " };
int noTests = sizeof(Tests) / sizeof(Tests[0]);
char resTests[9] = { 9, 9, 9, 9, 9, 9, 9, 9, 9 };
int failedTest = -1;
char result = 99;
int i,f;

unsigned long int tested = 0;
unsigned long int passed = 0;
unsigned long int failed = 0;

#define TESTTIME 3000

// TODO: make test cases rigid
#define NLCOND (2.167 <= DUT_Out_Volt && DUT_Out_Volt <= 2.417)
#define RPCOND (0 <= DUT_Out_Volt && DUT_Out_Volt <= 1.2)
#define SCCOND (0 <= DUT_Out_Volt && DUT_Out_Volt <= 1.2)
#define OLCOND (DUT_Out_Volt <= 1.667)
#define OVCOND (0 <= DUT_Out_Volt && DUT_Out_Volt <= 1.2)
#define V16COND ((2.167 <= DUT_Out_Volt && DUT_Out_Volt <= 2.3) && (1.3 <= DUT_Out_Curr && DUT_Out_Curr <= 1.8))
#define V24COND ((2.167 <= DUT_Out_Volt && DUT_Out_Volt <= 2.3) && (1.3 <= DUT_Out_Curr && DUT_Out_Curr <= 1.8))
#define V32COND ((2.167 <= DUT_Out_Volt && DUT_Out_Volt <= 2.3) && (1.3 <= DUT_Out_Curr && DUT_Out_Curr <= 1.8))

float DUT_Out_Volt = 0;
float DUT_Out_Curr = 0;

char checkOL(int testNo);

void runTests(void) {
	int i;
	//	noTests = 2;
	failedTest = -1;
	result = 99;
	tested++;
	for (i = 0; i < sizeof(resTests) / sizeof(resTests[0]); i++) {
		resTests[i] = 9;
	}

	testScreen();
	for (i = 0; i <= noTests; i++) {
		if (!test(i)) {
			resTest(i);
			break;
		}
		resTest(i);
	}

	SMPS_16V = 0;
	SMPS_24V = 0;
	SMPS_32V = 0;
	SMPS_42V = 0;

	SMPS_N24V = 0;
	LOAD = 0;
	SHORT = 0;
	EXTRA_LOAD = 0;
	changes =0;

	delay(1000);

	if (failedTest != -1) {
		result = 0;
		failed++;
		counterWrite();
		resultScreen();
		splashScreen();
	} else {
		result = 1;
		passed++;
		counterWrite();
		resultScreen();
	}

}

int test(int testNo) {
	int res = 9;

	switch (testNo) {
	case 0:
	case 8:
		//No Load
		f=0;
		LOAD = 0;
		SMPS_24V = 1;

		if (testNo == 0) {
			animTest(testNo, TESTTIME+1000);
		} else {
			delay(2000);
		}

		NLSTART:
		LOAD = 0;
		SMPS_24V = 1;
		DUT_Out_Volt = 0;
		DUT_Out_Curr = 0;
		for (i = 0; i < 10; i++) {
			DUT_Out_Volt += (float) analogRead(DUT_O_V) / 1023.00 * 5.00;
			DUT_Out_Curr += (float) analogRead(DUT_O_C) / 1023.00 * 5.00;
		}
		DUT_Out_Volt /= 10;
		DUT_Out_Curr /= 10;

		LOAD = 0;
		SMPS_24V = 0;

		if (NLCOND) {
			res = 1;
		} else {
			if (f == 0) {
				f=1;
				goto NLSTART;
			}
			res = 0;
			failedTest = testNo;
		}

		break;
	case 3:
		// Reverse Voltage
		SMPS_N24V = 1;

		animTest(testNo, TESTTIME);

		DUT_Out_Volt = 0;
		DUT_Out_Curr = 0;
		for (i = 0; i < 5; i++) {
			DUT_Out_Volt += (float) analogRead(DUT_O_V) / 1023.00 * 5.00;
			DUT_Out_Curr += (float) analogRead(DUT_O_C) / 1023.00 * 5.00;
		}
		DUT_Out_Volt /= 5;
		DUT_Out_Curr /= 5;

		SMPS_N24V = 0;

		if (RPCOND) {
			res = 1;
		} else {
			res = 0;
			failedTest = testNo;
		}

		break;
	case 1:
		// Short Circuit
		SMPS_24V = 1;
		SHORT = 1;

		animTest(testNo, TESTTIME);

		DUT_Out_Volt = 0;
		DUT_Out_Curr = 0;
		for (i = 0; i < 5; i++) {
			DUT_Out_Volt += (float) analogRead(DUT_O_V) / 1023.00 * 5.00;
			DUT_Out_Curr += (float) analogRead(DUT_O_C) / 1023.00 * 5.00;
		}
		DUT_Out_Volt /= 5;
		DUT_Out_Curr /= 5;

		SHORT = 0;
		SMPS_24V = 1;

		if (SCCOND) {
			res = 1;
		} else {
			res = 0;
			failedTest = testNo;
		}

		break;
	case 7:
		// Over Load
		LOAD = 1;
		EXTRA_LOAD = 1;
		SMPS_24V = 1;

//		delay(780);
//
//		DUT_Out_Volt = 0;
//		DUT_Out_Curr = 0;
//		for (i = 0; i < 5; i++) {
//			DUT_Out_Volt += (float) analogRead(DUT_O_V) / 1023.00 * 5.00;
//			DUT_Out_Curr += (float) analogRead(DUT_O_C) / 1023.00 * 5.00;
//			delay(3);
//		}
//		DUT_Out_Volt /= 5;
//		DUT_Out_Curr /= 5;

		if (checkOL(testNo)) {
			res = 1;
		} else {
			res = 0;
			failedTest = testNo;
		}

		LOAD = 0;
		EXTRA_LOAD = 0;
		SMPS_24V = 0;

		break;
	case 5:
		// Over Voltage
		LOAD = 1;
		SMPS_42V = 1;

		animTest(testNo, TESTTIME);

		DUT_Out_Volt = 0;
		DUT_Out_Curr = 0;
		for (i = 0; i < 5; i++) {
			DUT_Out_Volt += (float) analogRead(DUT_O_V) / 1023.00 * 5.00;
			DUT_Out_Curr += (float) analogRead(DUT_O_C) / 1023.00 * 5.00;
		}
		DUT_Out_Volt /= 5;
		DUT_Out_Curr /= 5;

		LOAD = 0;
		SMPS_42V = 0;

		if (OVCOND) {
			res = 1;
		} else {
			res = 0;
			failedTest = testNo;
		}

		break;
	case 4:
		// 16 V
		LOAD = 1;
		SMPS_16V = 1;

		animTest(testNo, TESTTIME);

		DUT_Out_Volt = 0;
		DUT_Out_Curr = 0;
		for (i = 0; i < 5; i++) {
			DUT_Out_Volt += (float) analogRead(DUT_O_V) / 1023.00 * 5.00;
			DUT_Out_Curr += (float) analogRead(DUT_O_C) / 1023.00 * 5.00;
		}
		DUT_Out_Volt /= 5;
		DUT_Out_Curr /= 5;

		LOAD = 0;
		SMPS_16V = 0;

		if (V16COND) {
			res = 1;
		} else {
			res = 0;
			failedTest = testNo;
		}

		break;
	case 2:
		// 24 V
		LOAD = 1;
		SMPS_24V = 1;

		animTest(testNo, TESTTIME);

		DUT_Out_Volt = 0;
		DUT_Out_Curr = 0;
		for (i = 0; i < 5; i++) {
			DUT_Out_Volt += (float) analogRead(DUT_O_V) / 1023.00 * 5.00;
			DUT_Out_Curr += (float) analogRead(DUT_O_C) / 1023.00 * 5.00;
		}
		DUT_Out_Volt /= 5;
		DUT_Out_Curr /= 5;

		LOAD = 0;
		SMPS_24V = 0;

		if (V24COND) {
			res = 1;
		} else {
			res = 0;
			failedTest = testNo;
		}

		break;
	case 6:
		// 32 V
		LOAD = 1;
		SMPS_32V = 1;

		animTest(testNo, TESTTIME);

		DUT_Out_Volt = 0;
		DUT_Out_Curr = 0;
		for (i = 0; i < 5; i++) {
			DUT_Out_Volt += (float) analogRead(DUT_O_V) / 1023.00 * 5.00;
			DUT_Out_Curr += (float) analogRead(DUT_O_C) / 1023.00 * 5.00;
		}
		DUT_Out_Volt /= 5;
		DUT_Out_Curr /= 5;

		LOAD = 0;
		SMPS_32V = 0;

		if (V32COND) {
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

char checkOL(int testNo) {
	changes = 0;
	R_KEY_Start();
	animTest(testNo, TESTTIME);
	R_KEY_Stop();

	if (changes > 60) {
		return 1;
	} else {
		return 0;
	}
}
