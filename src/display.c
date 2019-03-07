/*
 * display.c
 *
 *  Created on: Feb 14, 2019
 *      Author: 500022
 */
#include <stdio.h>

#include "r_cg_timer.h"
#include "r_cg_adc.h"
#include "r_cg_userdefine.h"

#include "display.h"
#include "lcd.h"
#include "test.h"
#include "eeprom.h"

char LLS[] = { 0b00001, 0b00001, 0b00001, 0b00001, 0b00001, 0b00001, 0b00001,
		0b00001 };

char RLS[] = { 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000,
		0b10000 };

char TL[] = { 0b11111, 0b00000, 0b11111, 0b00000, 0b00000, 0b00000, 0b00000,
		0b00000 };

char BL[] = { 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b00000,
		0b11111 };

char LL[] = { 0b10100, 0b10100, 0b10100, 0b10100, 0b10100, 0b10100, 0b10100,
		0b10100 };

char RL[] = { 0b00101, 0b00101, 0b00101, 0b00101, 0b00101, 0b00101, 0b00101,
		0b00101 };

char TLC[] = { 0b11111, 0b10000, 0b10111, 0b10100, 0b10100, 0b10100, 0b10100,
		0b10100 };

char TRC[] = { 0b11111, 0b00001, 0b11101, 0b00101, 0b00101, 0b00101, 0b00101,
		0b00101 };

char BLC[] = { 0b10100, 0b10100, 0b10100, 0b10100, 0b10100, 0b10111, 0b10000,
		0b11111 };

char BRC[] = { 0b00101, 0b00101, 0b00101, 0b00101, 0b00101, 0b11101, 0b00001,
		0b11111 };

char OK[] = "-OK  ";
char Fail[] = "-Fail";
char Empty[] = "-    ";
char screenState = 99;

void displayInit(void) {
	lcdInit();
	splashScreen();
//	testScreen();
}

void animTest(int testNo,int testtime) {
	int i = testNo;
	if (i < 4) {
		setCursor(5, i);
	} else {
		setCursor(16, i - 4);
	}

	for (i = 0; i < 4; i++) {
		sendData('.');
		delay(testtime/4);
	}
}

void resTest(int testNo){
	int i = testNo;
	if (i < 4) {
		setCursor(4, i);
	} else {
		setCursor(15, i - 4);
	}

	if (resTests[i] == 1) {
		printLcd(OK);
	} else if (resTests[i] == 0) {
		printLcd(Fail);
	}
}

void testScreen(void) {
	int i;

	screenState = 1;
	lcdInit();
	createChar(0, LLS);
	createChar(1, RLS);

	for (i = 0; i < noTests; i++) {
		if (i < 4) {
			setCursor(0, i);
			printLcd(Tests[i]);
			if (resTests[i] == 1) {
				printLcd(OK);
			} else if (resTests[i] == 0) {
				printLcd(Fail);
			} else if (resTests[i] == 9) {
				printLcd(Empty);
			}
			sendData(0);
		} else {
			setCursor(10, i - 4);
			sendData(1);
			printLcd(Tests[i]);
			if (resTests[i] == 1) {
				printLcd(OK);
			} else if (resTests[i] == 0) {
				printLcd(Fail);
			} else if (resTests[i] == 9) {
				printLcd(Empty);
			}
		}
	}
}

void splashScreen(void) {
	splash_start: screenState = 0;
	lcdInit();
//	loadDoubleLines();
//  drawBorders();
	setCursor(1, 1);
	printLcd(" D135  STATIC KIT ");
	setCursor(1, 3);
	printLcd(" Press Start Btn. ");
	while (1) {
		if (START_BTN == 1) {
			break;
		}
		if (MEMORY_BTN == 1) {
			delay(2000);
			if (MEMORY_BTN == 1) {
				memoryScreen();
				goto splash_start;
			}
		}
	}
}

void resultScreen(void) {
	res_start: screenState = 3;
	lcdInit();
//	loadDoubleLines();
//	drawBorders();
	if (result == 1) {
		setCursor(1, 1);
		printLcd("       PASS       ");
		setCursor(1, 3);
		printLcd(" Press Start Btn. ");
		while (1) {
			if (START_BTN == 1) {
				break;
			}
			if (MEMORY_BTN == 1) {
				delay(2000);
				if (MEMORY_BTN == 1) {
					memoryScreen();
					goto res_start;
				}
			}
		}
	} else {
		setCursor(1, 0);
		printLcd("       FAIL       ");
		setCursor(1, 2);
		printLcd(TestsFull[failedTest]);
		setCursor(1, 3);
		printLcd(" Press Reset Btn. ");
		while (1) {
			if (RESET_BTN == 1) {
				break;
			}
			if (MEMORY_BTN == 1) {
				delay(2000);
				if (MEMORY_BTN == 1) {
					memoryScreen();
					goto res_start;
				}
			}
		}
	}
}

void memoryScreen(void) {
	char str[21];
	char _mem_c=0;
	counterRead();
	mem_start: lcdInit();
	setCursor(0, 0);
	printLcd("Total");
	setCursor(0, 1);
	sprintf(str, "    DUTs tested: %00d", tested);
	printLcd(str);
	setCursor(0, 2);
	sprintf(str, "    DUTs passed: %00d", passed);
	printLcd(str);
	setCursor(0, 3);
	sprintf(str, "    DUTs failed: %00d", failed);
	printLcd(str);
	while (1) {
		if (MEMORY_BTN == 0) {
			delay(100);
			if (MEMORY_BTN == 1) {
				delay(300);
				break;
			}
		}
		if (RESET_BTN == 1) {
			delay(3000);
			if (RESET_BTN == 1) {
				tested = 0;
				passed = 0;
				failed = 0;
				counterWrite();
				_mem_c=1;
				break;
			}
		}
	}
	if(_mem_c==1){
		_mem_c=0;
		goto mem_start;
	}
}

void revertScreenState(void) {
	switch (screenState) {
	case 0:
		splashScreen();
		break;
	case 1:
		testScreen();
		break;
	case 3:
		resultScreen();
	}
}

void drawBorders(void) {
	int i;

	setCursor(0, 0);
	sendData(4);
	setCursor(19, 0);
	sendData(5);
	setCursor(0, 3);
	sendData(6);
	setCursor(19, 3);
	sendData(7);

	for (i = 1; i < 19; i++) {
		setCursor(i, 0);
		sendData(0);
		setCursor(i, 3);
		sendData(1);
	}

	for (i = 1; i < 3; i++) {
		setCursor(0, i);
		sendData(2);
		setCursor(19, i);
		sendData(3);
	}

	setCursor(0, 0);
}

void loadDoubleLines(void) {
	createChar(0, TL);
	createChar(1, BL);
	createChar(2, LL);
	createChar(3, RL);
	createChar(4, TLC);
	createChar(5, TRC);
	createChar(6, BLC);
	createChar(7, BRC);
}
