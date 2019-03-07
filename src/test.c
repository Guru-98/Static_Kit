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
#include "r_cg_timer.h"
#include "r_cg_adc.h"

char Tests[][5] = { "N.L.", "R.P.", "S.C.", "O.L.", "O.V.", "16V ", "24V ",
		"32V " };

char TestsFull[][19] = { "     No  Load     ", " Reverse Voltage ",
		"  Short  Circuit  ", "    Over  Load    ", "   Over Voltage   ",
		"  Full Load  16V  ", "  Full Load  24V  ", "  Full Load  32V  " };
int noTests = sizeof(Tests) / sizeof(Tests[0]);
char resTests[8] = { 9, 9, 9, 9, 9, 9, 9, 9 };
int failedTest = -1;
char result = 99;

char tested = 0;
char passed = 0;
char failed = 0;

#define TESTTIME 3000

// TODO: make test cases rigid
#define TEST0COND (4.166 <= DUT_Out_Volt && DUT_Out_Volt <= 4.833)
#define TEST1COND (0 <= DUT_Out_Volt && DUT_Out_Volt <= 1.2)
#define TEST2COND (0 <= DUT_Out_Volt && DUT_Out_Volt <= 1.2)
#define TEST3COND (0 <= DUT_Out_Volt && DUT_Out_Volt <= 1.2)
#define TEST4COND (0 <= DUT_Out_Volt && DUT_Out_Volt <= 1.2)
#define TEST5COND ((4.166 <= DUT_Out_Volt && DUT_Out_Volt <= 4.833) && (1.12 <= DUT_Out_Curr && DUT_Out_Curr <= 1.22))
#define TEST6COND ((4.166 <= DUT_Out_Volt && DUT_Out_Volt <= 4.833) && (1.12 <= DUT_Out_Curr && DUT_Out_Curr <= 1.22))
#define TEST7COND ((4.166 <= DUT_Out_Volt && DUT_Out_Volt <= 4.833) && (1.12 <= DUT_Out_Curr && DUT_Out_Curr <= 1.22))

float DUT_Out_Volt = 0;
float DUT_Out_Curr = 0;

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
	for (i = 0; i < noTests; i++) {
		if (!test(i)) {
			resTest(i);
			break;
		}
		resTest(i);
	}

	delay(3000);

	if (failedTest != -1) {
		result = 0;
		failed++;
		counterWrite();

		RED_LED = 1;
		resultScreen();
		RED_LED = 0;
		splashScreen();
	} else {
		result = 1;
		passed++;
		counterWrite();

		GRN_LED = 1;
		resultScreen();
		GRN_LED = 0;
	}

}

int test(int testNo) {
	int res = 9;
	int i;

	switch (testNo) {
	case 0:
		//No Load
		LOAD = 0;
		SMPS_24V = 1;

		animTest(testNo, TESTTIME);

		DUT_Out_Volt = (float) analogRead(DUT_O_V) / 1023.00 * 5.00;
		DUT_Out_Curr = (float) analogRead(DUT_O_C) / 1023.00 * 5.00;

		LOAD = 0;
		SMPS_24V = 0;

		if (TEST0COND) {
			res = 1;
		} else {
			res = 0;
			failedTest = testNo;
		}

		break;
	case 1:
		// Reverse Voltage
		LOAD = 1;
		DUT_IP_REV = 1;
		SMPS_24V = 1;

		animTest(testNo, TESTTIME);

		DUT_Out_Volt = (float) analogRead(DUT_O_V) / 1023.00 * 5.00;
		DUT_Out_Curr = (float) analogRead(DUT_O_C) / 1023.00 * 5.00;

		LOAD = 0;
		DUT_IP_REV = 0;
		SMPS_24V = 0;

		if (TEST1COND) {
			res = 1;
		} else {
			res = 0;
			failedTest = testNo;
		}

		break;
	case 2:
		// Short Circuit
		LOAD = 1;
		SHORT = 1;
		SMPS_24V = 1;

		animTest(testNo, TESTTIME);

		DUT_Out_Volt = (float) analogRead(DUT_O_V) / 1023.00 * 5.00;
		DUT_Out_Curr = (float) analogRead(DUT_O_C) / 1023.00 * 5.00;

		LOAD = 0;
		SHORT = 0;
		SMPS_24V = 0;

		if (TEST2COND) {
			res = 1;
		} else {
			res = 0;
			failedTest = testNo;
		}

		break;
	case 3:
		// Over Load
		LOAD = 1;
		EXTRA_LOAD = 1;
		SMPS_24V = 1;

		animTest(testNo, TESTTIME);

		DUT_Out_Volt = 0;
		DUT_Out_Curr = 0;

		for (i = 0; i < 10; i++) {
			DUT_Out_Volt += (float) analogRead(DUT_O_V) / 1023.00 * 5.00;
			DUT_Out_Curr += (float) analogRead(DUT_O_C) / 1023.00 * 5.00;
			delay(50);
		}

		DUT_Out_Volt /= 10;
		DUT_Out_Curr /= 10;

		LOAD = 0;
		EXTRA_LOAD = 0;
		SMPS_24V = 0;

		if (TEST3COND) {
			res = 1;
		} else {
			res = 0;
			failedTest = testNo;
		}

		break;
	case 4:
		// Over Voltage
		LOAD = 1;
		SMPS_16V = 1;
		SMPS_24V = 1;

		animTest(testNo, TESTTIME);

		DUT_Out_Volt = (float) analogRead(DUT_O_V) / 1023.00 * 5.00;
		DUT_Out_Curr = (float) analogRead(DUT_O_C) / 1023.00 * 5.00;

		LOAD = 0;
		SMPS_16V = 0;
		SMPS_24V = 0;

		if (TEST4COND) {
			res = 1;
		} else {
			res = 0;
			failedTest = testNo;
		}

		break;
	case 5:
		// 16 V
		LOAD = 1;
		SMPS_16V = 1;

		animTest(testNo, TESTTIME);

		DUT_Out_Volt = (float) analogRead(DUT_O_V) / 1023.00 * 5.00;
		DUT_Out_Curr = (float) analogRead(DUT_O_C) / 1023.00 * 5.00;

		LOAD = 0;
		SMPS_16V = 0;

		if (TEST5COND) {
			res = 1;
		} else {
			res = 0;
			failedTest = testNo;
		}

		break;
	case 6:
		// 24 V
		LOAD = 1;
		SMPS_24V = 1;

		animTest(testNo, TESTTIME);

		DUT_Out_Volt = (float) analogRead(DUT_O_V) / 1023.00 * 5.00;
		DUT_Out_Curr = (float) analogRead(DUT_O_C) / 1023.00 * 5.00;

		LOAD = 0;
		SMPS_24V = 0;

		if (TEST6COND) {
			res = 1;
		} else {
			res = 0;
			failedTest = testNo;
		}

		break;
	case 7:
		// Short Circuit
		LOAD = 1;
		SMPS_32V = 1;

		animTest(testNo, TESTTIME);

		DUT_Out_Volt = (float) analogRead(DUT_O_V) / 1023.00 * 5.00;
		DUT_Out_Curr = (float) analogRead(DUT_O_C) / 1023.00 * 5.00;

		LOAD = 0;
		SMPS_32V = 0;

		if (TEST7COND) {
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
