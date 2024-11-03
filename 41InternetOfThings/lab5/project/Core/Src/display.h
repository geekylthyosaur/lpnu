/*
 * display.h
 *
 *  Created on: Sep 30, 2024
 *      Author: dmytro
 */

#ifndef SRC_DISPLAY_H_
#define SRC_DISPLAY_H_

#include "string.h"

#define lcdPort GPIOE
#define rsPin GPIO_PIN_7
#define rwPin GPIO_PIN_10
#define enPin GPIO_PIN_11
#define dh4Pin GPIO_PIN_12
#define dh5Pin GPIO_PIN_13
#define dh6Pin GPIO_PIN_14
#define dh7Pin GPIO_PIN_15

#define RS(X) HAL_GPIO_WritePin(lcdPort, rsPin, (X))
#define RW(X) HAL_GPIO_WritePin(lcdPort, rwPin, (X))
#define EN(X) HAL_GPIO_WritePin(lcdPort, enPin, (X))
#define DH4(X) HAL_GPIO_WritePin(lcdPort, dh4Pin, (X))
#define DH5(X) HAL_GPIO_WritePin(lcdPort, dh5Pin, (X))
#define DH6(X) HAL_GPIO_WritePin(lcdPort, dh6Pin, (X))
#define DH7(X) HAL_GPIO_WritePin(lcdPort, dh7Pin, (X))

void lcdSend(uint8_t isCommand, uint8_t data) {
	RS(isCommand==0);
	HAL_Delay(1);
	DH7(((data >> 7) & 1)==1);
	DH6(((data >> 6) & 1)==1);
	DH5(((data >> 5) & 1)==1);
	DH4(((data >> 4) & 1)==1);
	EN(1);
	HAL_Delay (1);
	EN(0);
	DH7(((data >> 3) & 1)==1);
	DH6(((data >> 2) & 1)==1);
	DH5(((data >> 1) & 1)==1);
	DH4((data & 1)==1);
	EN(1);
	HAL_Delay (1);
	EN(0);
}

void lcdCommand(uint8_t cmd) {
	lcdSend(1, cmd);
}

void lcdChar(const char chr) {
	lcdSend(0, (uint8_t)chr);
}

void setCursor(uint8_t col, uint8_t row)
{
	lcdSend(1,0x80 | (col | row*0x40));
}

void parametrsToggle(uint8_t display,uint8_t cursor,uint8_t blink){
	uint8_t comm = 0x08;
	if(display)comm|=0x04;
	if(cursor)comm|=0x02;
	if(blink)comm|=0x01;
	lcdCommand(comm);
}

void shiftToggle(uint8_t rightShift,uint8_t scrollInc){
	uint8_t comm = 0x04;
	if(rightShift)comm|=0x02;
	if(scrollInc)comm|=0x01;
	lcdCommand(comm);
}

void scrollRight(void){
	lcdCommand(0x10|0x08|0x00);
}
void scrollLeft(void){
	lcdCommand(0x10|0x08|0x04);
}

void clear(void)
{
	lcdCommand(0x01);
	HAL_Delay(2);
}

void home(void)
{
	lcdCommand(0x02);
	HAL_Delay(2);
}

void initLCD(void){
	HAL_Delay(40);
	lcdCommand(0x02);
	HAL_Delay(1);
	lcdCommand(0x28);
	HAL_Delay(1);
	lcdCommand(0x28);
	HAL_Delay(1);
	parametrsToggle(1,0,0);
	HAL_Delay(1);
	clear();
	shiftToggle(1,0);
}

void lcdString(char* str){
	for(uint8_t i=0;str[i]!='\0';i++){
		lcdChar(str[i]);
	}
}

void lcdSrollingString(int strRow, int counter, char * str){
	int strLength = strlen(str);
	int lineColumn = counter % (strLength - 15);
	setCursor(0, strRow);
	HAL_Delay(1);

    for(int i = lineColumn; i < lineColumn + 16; i++){
    	lcdChar(str[i]);
    }
}

#endif /* SRC_DISPLAY_H_ */
