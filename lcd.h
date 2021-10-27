/* 
 * File:   lab5_lcd.h
 * Author: abasfarah
 *
 * Created on April 22, 2020, 5:43 PM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

void delay(int);
void lcd_cmd(char);
void lcd_init(void);
void lcd_setCursor(char x, char y);
void lcd_printChar(char);
void lcd_printStr(const char s[]);

#ifdef	__cplusplus
}
#endif

#endif	/* LAB5_LCD_H */

