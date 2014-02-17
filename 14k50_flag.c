/* 
 * File:   14k50_flag.c
 * Author: michaelburr
 *
 * Created on February 14, 2014, 9:40 AM
 */

#include <xc.h>
#include "flag.h"
#include <stdio.h>
#include <stdlib.h>
#define Ready           LATCbits.LC3
#define Trigger         PORTCbits.RC2
#define Tripped         LATCbits.LC6
#define Reset_out       LATCbits.LC0
#define Flag_Release    LATCbits.LC6
#define Flag_Sensor     PORTBbits.RB4
#define DISPLAY         PORTC
#define LED             LATCbits.LC4
#define LED1            LATCbits.LC5
//#define DISPLAY_NIBBLE  LATCbits.LC4 & LATCbits.LC5


#define _XTAL_FREQ      31200

//unsigned char  const SEGMENT_MAP[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
unsigned char const COUNT_MAP[4] = {0x00,0x10,0x20,0x30};

    char digit;


/*
 *
 */
void main(void) {

    ANSEL = 0x00;
    ANSELH = 0x00;
    TRISC = 0x04;
    TRISB = 0x10;
    ADCON1 = 0x06;
    //TRISA = 0x04;
    OSCCONbits.IRCF = 0; //Set up internal oscillator for 31kHz operation
    OSCCONbits.SCS = 0x2;  //Select internal clock source
    OSCCON = 0x86;
    INTCON3bits.INT2F = 0;
    INTCON2bits.INTEDG2 = 0;
    INTCON3bits.INT2IP = 0;
    INTCON3bits.INT2E = 1;
    GIE=1;
    //digit = 0;



    //DISPLAY= 0x30;
    



    for(;;)
    {
        if (Flag_Sensor == 0){
            digit = 0;
            DISPLAY = (COUNT_MAP[digit]);
            //LED = 0;
            //LED1 = 0;
            Tripped = 0;


        while (Flag_Sensor !=0 && digit <= 3)
        {   DISPLAY = (COUNT_MAP[digit]);
        Tripped = 1;
        }}
        else
        {for(int i = 0; i<250;i++);
        {Reset_out = 1;
        }
        Reset_out = 0;
        Tripped = 0;
        }

    }

}

void interrupt Trigger_input(void)
{   if(Flag_Sensor == 0){
        for(int i = 0;i<3000;i++);
        {Flag_Release = 1;
        Tripped = 1;
        digit++;
        DISPLAY = (COUNT_MAP[digit]);
        INT2IF=0;
        }}
    else {
        digit++;
        Tripped = 1;
    INT2IF=0;;
    }
}

