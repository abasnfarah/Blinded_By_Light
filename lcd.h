/* 
 * File:   lcd.h
 * Author: abasfarah
 *
 * Created on November 18, 2021, 10:40 AM
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

#endif	/* LCD_H */

