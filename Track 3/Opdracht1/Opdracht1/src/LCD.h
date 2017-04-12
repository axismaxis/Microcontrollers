/*
 * LCD.h
 *
 * Created: 16/02/2017 11:55:53
 *  Author: Timon
 */ 
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef LCD_H_
#define LCD_H_
 
void lcd_command(unsigned char dat);
void lcd_writeChar(unsigned char dat);
void lcd_writeLine(unsigned char* ptrArray);
void lcd_init(void);
void lcd_clear(void);
void lcd_set_cursor(void);

#endif /* LCD_H_ */