/*
 * display.h
 *
 *  Created on: Feb 14, 2019
 *      Author: 500022
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

extern char Tests[][5];
extern int noTests;
extern int failedTest;
extern char OK[];
extern char Fail[];
extern char screenState;

void displayInit(void);

void testScreen(void);
void splashScreen(void);
void resultScreen(void);
void memoryScreen(void);

void revertScreenState(void);

void loadDoubleLines(void);
void drawBorders(void);
void animTest(int testNo);
#endif /* DISPLAY_H_ */
