#include "r_cg_userdefine.h"
#include "lcd.h"
#include "r_cg_macrodriver.h"

void lcdinit(void){
	EN = 1;
	DB = 0;

/*  Wakeup call for 4 bit mode*/
//	sendcmd(0x30);
//	delay(30);
//	sendcmd(0x30);
//	delay(30);
//	sendcmd(0x30);
//	delay(30);

	sendcmd(LCD_FUNCTIONSET | LCD_8BITMODE|LCD_2LINE|LCD_5x8DOTS); //0x38
	delay(4000);

	sendcmd(LCD_DISPLAYCONTROL | LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF); //0x0C
	delay(4000);

	sendcmd(LCD_CLEARDISPLAY); //0x01
	delay(4000);

	sendcmd(LCD_RETURNHOME); //0x02
	delay(4000);

	sendcmd(LCD_ENTRYMODESET | LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT); //0x06
	delay(4000);
}

void scrollDisplayLeft(void) {
  sendcmd(LCD_CURSORSHIFT| LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void scrollDisplayRight(void) {
  sendcmd(LCD_CURSORSHIFT| LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void printlcd(char* x){
	while (*x != '\0'){
		senddata(*x);
		x++;
		delay(1000);
	}
}

void sendcmd(char x){
	RS = 0;
	DB = x;
//	DB = x<<4;
	trigger();
	DB = 0x00;
}

void senddata(char x){
	RS = 1;
	DB = x;
//	DB = x<<4;
	trigger();
	DB= 0x00;
}

void trigger(void){
	EN = 1;
	delay(100);
	EN = 0;
	delay(100);
	EN = 1;
}

void delay(uint16_t msec){
	while(msec--);
}
