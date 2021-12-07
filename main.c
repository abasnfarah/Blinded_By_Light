/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  PIC24FJ64GA002
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB 	          :  MPLAB X v5.45
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include "mcc_generated_files/system.h"
#include "lcd.h"
#include <string.h>
#include "asmlib.h"
#include <stdlib.h>
#include <math.h>

volatile unsigned int overflow = 0;
volatile double current = 0.0;
volatile double tareOffset = 0.0;
void __attribute__ ( ( interrupt, no_auto_psv ) ) _T2Interrupt (  )
{
    overflow++;
    _T2IF = 0;
}

void reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }
  
    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';
  
    reverse(str, i);
    str[i] = '\0';
    return i;
}
  
// Converts a floating-point/double number to a string.
void ftoa(double n, char* res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;
  
    // Extract floating part
    double fpart = n - (double)ipart;
  
    // convert integer part to string
    int i = intToStr(ipart, res, 0);
  
    // check for display option after point
    if (afterpoint != 0) {
        res[i] = '.'; // add dot
  
        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter 
        // is needed to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);
  
        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}
/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    lcd_init();
    unsigned int time;
    char output[20];
    PORTBbits.RB15 = 0;
    //sprintf(output, 20,"%f",current - tareOffset);
    //ftoa(n, output, 6);
    
    while (1)
    {
        // Add your application code
        int input = PORTBbits.RB11;
        
        // Capture SPI value from ADC
       
        uint16_t data1 = 0x38FF;
        uint16_t data2 = 0xFFFF;
        data1 = SPI1_Exchange16bit(data1);
        data2 = SPI1_Exchange16bit(data2);
        long int raw = (data1 & 0x00FF) << 16;
        raw += data2;
        long int data = (data1 & 0x0001) << 16;
        data += data2;
        // Convert HEX value to doubland binary using lookup table
        double n;
        current = (double) data;
        n = current - tareOffset;
        // test button input for tare.
        // send UART
        int i;
        for(i = 23; i >= 0; i--){
            if ((data2 >> i) % 2){
                UART1_Write('1');
            }else{
                UART1_Write('0');
            }
        }
        
        UART1_Write('\n');
        UART1_Write('\r');

        // send to display
        if(input){
            
            delay(50);
            tareOffset = current;
            n = current - tareOffset;
            n = (double) data2;
            ftoa(n, output, 6);
            //char output[50];
            //sprintf(output, 50, "%f", num);
            
            //time = (overflow * PR2) + TMR2;
            //TMR2 = 0;
            //overflow = 0;
            
            // Prescaler = 256, for 0.25 sec time must be 15625
            //if ( time < 15625){
            //    x++;
            //}
        }
       
        //sprintf(output, 8,"%f",current - tareOffset);
        lcd_setCursor(0,0);
        if(n<0){
            lcd_printStr("OL");
        } else{
            lcd_printStr(output);
        }
        //x++;
        
        //lcd_cmd(0b00011100);
        //delay(1000);
    }

    return 1;
}
/**
 End of File
*/

