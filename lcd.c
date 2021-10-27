
/*
 * File:   lcd.c
 * Author: abasfarah
 *
 * Created on April 22, 2020, 5:45 PM
 */


#include "xc.h"
#include "asmlib.h"



void lcd_cmd(char Package) {
    I2C2CONbits.SEN = 1;	//Initiate Start condition
    while (I2C2CONbits.SEN == 1);//Wait for SEN == 0  // SEN will clear when Start Bit is complete
    IFS3bits.MI2C2IF=0; //Clear IFS3bits.MI2C2IF
    I2C2TRN = 0b01111100; // 8-bits consisting of the slave address and the R/nW bit
    while(IFS3bits.MI2C2IF != 1);//Wait for IFS3bits.MI2C2IF == 1 // *Refer to NOTE below*
    IFS3bits.MI2C2IF = 0;//Clear IFS3bits.MI2C2IF
    I2C2TRN = 0b00000000; // 8-bits consisting of control byte
    while(IFS3bits.MI2C2IF != 1);//Wait for IFS3bits.MI2C2IF == 1
    IFS3bits.MI2C2IF = 0;//Clear IFS3bits.MI2C2IF
    I2C2TRN = Package; // 8-bits consisting of the data byte
    while(IFS3bits.MI2C2IF != 1);//Wait for IFS3bits.MI2C2IF == 1
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN == 1);//Wait for PEN==0 // PEN will clear when Stop bit is complete
}
void lcd_init(){
    delay(50);//wait 50ms;
    lcd_cmd(0b00111000); // function set, normal instruction mode
    lcd_cmd(0b00111001); // function set, extended instruction mode
    lcd_cmd(0b00010100); // interval osc
    lcd_cmd(0b01110000); // contrast C3-C0
    lcd_cmd(0b01011110); // Ion, Bon, C5-C4
    lcd_cmd(0b01101100); // follower control
    delay(200);//wait 200ms;
    lcd_cmd(0b00111000); // function set, normal instruction mode
    lcd_cmd(0b00001100); // Display On
    lcd_cmd(0b00000001); // Clear Display
    delay(2);//wait 2ms;

}
void lcd_setCursor(char x, char y) {
    char mask = 0x40*(x) + (y);
    mask = (1 << 7) + mask;
    lcd_cmd(mask);
}

void lcd_printChar(char Package) {
    I2C2CONbits.SEN = 1;	//Initiate Start condition
    while(I2C2CONbits.SEN);//Wait for SEN == 0  // SEN will clear when Start Bit is complete
    IFS3bits.MI2C2IF=0; //Clear IFS3bits.MI2C2IF
    I2C2TRN = 0b01111100; // 8-bits consisting of the slave address and the R/nW bit
    while(IFS3bits.MI2C2IF != 1);//Wait for IFS3bits.MI2C2IF == 1 
    IFS3bits.MI2C2IF=0; //Clear IFS3bits.MI2C2IF
    I2C2TRN = 0b01000000; // 8-bits consisting of control byte /w RS=1
    while(IFS3bits.MI2C2IF != 1);//Wait for IFS3bits.MI2C2IF == 1
    IFS3bits.MI2C2IF=0;//Clear IFS3bits.MI2C2IF
    I2C2TRN = Package; // 8-bits consisting of the data byte
    while(IFS3bits.MI2C2IF != 1);//Wait for IFS3bits.MI2C2IF == 1
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN);//Wait for PEN==0 // PEN will clear when Stop bit is complete

}

void lcd_printStr( const char c[]) {
    int l = strlen(c);
    I2C2CONbits.SEN = 1; //Initiate Start condition
    while (I2C2CONbits.SEN);//Wait for SEN == 0  // SEN will clear when Start Bit is complete
    IFS3bits.MI2C2IF = 0;//Clear IFS3bits.MI2C2IF
    I2C2TRN = 0b01111100; // 8-bits consisting of the slave address and the R/nW bit
    while(IFS3bits.MI2C2IF != 1);//Wait for IFS3bits.MI2C2IF == 1
    IFS3bits.MI2C2IF = 0;//Clear IFS3bits.MI2C2IF
    int i;
    for (i = 0; i < l ; i++) {
        I2C2TRN = 0b11000000; // 8-bits consisting of control byte /w RS=1
        while(IFS3bits.MI2C2IF != 1);//Wait for IFS3bits.MI2C2IF == 1
        IFS3bits.MI2C2IF = 0;//Clear IFS3bits.MI2C2IF
        I2C2TRN = c[i]; // 8-bits consisting of the data byte
        while(IFS3bits.MI2C2IF != 1);//Wait for IFS3bits.MI2C2IF == 1
        IFS3bits.MI2C2IF = 0;//Clear IFS3bits.MI2C2IF
    }
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN);//Wait for PEN==0 // PEN will clear when Stop bit is complete

}


void delay(int time) {
    while(time){
        wait_1ms();
        time--;
    }
}
