/*
 * test.h
 *
 *  Created on: Feb 19, 2019
 *      Author: 500022
 */

#ifndef TEST_H_
#define TEST_H_

extern char Tests[][5];
extern char TestsFull[][19];
extern int noTests;
extern char resTests[8];
extern int failedTest;
extern char result;

int test(int testNo);
void runTests(void);

#endif /* TEST_H_ */
