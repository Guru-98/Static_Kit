/*
 * display.c
 *
 *  Created on: Feb 14, 2019
 *      Author: 500022
 */
#include "display.h"
#include "lcd.h"

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

char Tests[][5] = { "N.L.", "R.P.", "S.C.", "O.L.", "O.V.", "16V ", "24V ",
		"32V " };
int noTests = sizeof(Tests) / sizeof(Tests[0]);
int failedTest = 1;

void displayInit(void) {
	int i;
	lcdInit();
	splashScreen();
	testScreen();
	for (i = 0; i < noTests; i++) {
		runTests(i);
	}
	resultScreen(1);
	resultScreen(0);
}

void runTests(int testNo) {
//	TODO: replace Dummy function
	int i = testNo, j;
	if (i < 4) {
		setCursor(5, i);
	} else {
		setCursor(16, i - 4);
	}

	for (i = 0; i < 4; i++) {
		sendData('.');
		for (j = 0; j < 30; j++) {
			delay(0xffff);
		}
	}

	i = testNo;
	if (i < 4) {
		setCursor(4, i);
	} else {
		setCursor(15, i - 4);
	}

	if (i % 2 == 0) {
		printLcd(OK);
	} else {
		printLcd(Fail);
	}
}

void testScreen(void) {
	int i;

	lcdInit();
	createChar(0, LLS);
	createChar(1, RLS);

	for (i = 0; i < noTests; i++) {
		if (i < 4) {
			setCursor(0, i);
			printLcd(Tests[i]);
			printLcd(Empty);
			sendData(0);
		} else {
			setCursor(10, i - 4);
			sendData(1);
			printLcd(Tests[i]);
			printLcd(Empty);
		}
	}
}

void splashScreen(void) {
	lcdInit();
	loadDoubleLines();
	//drawBorders();
	setCursor(1, 1);
	printLcd(" D135  STATIC KIT ");
	setCursor(1, 3);
	printLcd(" Press Start Btn. ");

}

void resultScreen(char result) {
	lcdInit();
	loadDoubleLines();
	drawBorders();
	setCursor(1, 1);
	if (result == 1) {
		printLcd("       PASS       ");
	} else {
		printLcd("       FAIL       ");
		setCursor(8,2);
		printLcd(Tests[failedTest]);
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
