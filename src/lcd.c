#include "lcd.h"

#include "r_cg_userdefine.h"
#include "r_cg_macrodriver.h"
#include "r_cg_timer.h"

void lcdInit(void) {
	delay1(0xffff);
	EN = 1;
	DB = 0;

	/*  Wakeup call for 4 bit mode*/
//	sendcmd(0x30);
//	delay1(30);
//	sendcmd(0x30);
//	delay1(30);
//	sendcmd(0x30);
//	delay1(30);
	sendCmd(LCD_FUNCTIONSET | LCD_8BITMODE | LCD_2LINE | LCD_5x8DOTS); //0x38
	delay1(4000);

	sendCmd(LCD_DISPLAYCONTROL | LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF); //0x0C
	delay1(4000);

	sendCmd(LCD_CLEARDISPLAY); //0x01
	delay1(4000);

	sendCmd(LCD_RETURNHOME); //0x02
	delay1(4000);

	sendCmd(LCD_ENTRYMODESET | LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT); //0x06
	delay1(4000);
}

void scrollDisplayLeft(void) {
	sendCmd(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void scrollDisplayRight(void) {
	sendCmd(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void createChar(char location, char charmap[]) {
	int i;
	location &= 0x7;
	sendCmd(LCD_SETCGRAMADDR | (location << 3));
	for (i = 0; i < 8; i++) {
		sendData(charmap[i]);
		delay1(30);
	}
	delay1(30);
}

void printLcd(char *x) {
	while (*x != '\0') {
		sendData(*x);
		x++;
		delay1(1000);
	}
	delay1(30);
}

void sendCmd(char x) {
	RS = 0;
	DB = x;
//	DB = x<<4;
	trigger();
	DB = 0x00;
	delay1(30);
}

void sendData(char x) {
	RS = 1;
	DB = x;
//	DB = x<<4;
	trigger();
	DB = 0x00;
	delay1(30);
}

void trigger(void) {
	EN = 1;
	delay1(100);
	EN = 0;
	delay1(100);
	EN = 1;
}

void clearLcd(void){
	sendCmd(LCD_CLEARDISPLAY);
	delay1(30);
	sendCmd(LCD_SETDDRAMADDR);
}

void setCursor(char col, char row) {
	uint8_t row_offsets[] = {0x00,0x40,0x14,0x54};
	sendCmd(LCD_SETDDRAMADDR | (col + row_offsets[row]));
	delay1(30);
}
