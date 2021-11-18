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
volatile double current = 2.34567;
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
void ftoa(float n, char* res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;
  
    // Extract floating part
    float fpart = n - (float)ipart;
  
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
    int x = 0;
    const char *strings[6];
    strings[0] = "1";
    strings[1] = "2";
    strings[2] = "3";
    strings[3] = "4";
    strings[4] = "5";
    strings[5] = "6";
    strings[6] = "7";
    strings[7] = "8";
    strings[8] = "9";
    strings[9] = "10";
    char output[20];
    
    //sprintf(output, 20,"%f",current - tareOffset);
    float n = (float) (current);
    ftoa(n, output, 6);
    
    while (1)
    {
        // Add your application code
        int input = PORTBbits.RB11;
        if(input){
            delay(50);
            tareOffset = 0.04567;
            float n = (float) (current - tareOffset);
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
        if (overflow >= 2){
            //x++;
        }
        if(x >9 ){
            x = 0;
        }
        //sprintf(output, 8,"%f",current - tareOffset);
        lcd_setCursor(0,0);
        lcd_printStr(output);
        //x++;
        
        //lcd_cmd(0b00011100);
        delay(50);
    }

    return 1;
}
/**
 End of File
*/

