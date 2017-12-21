/*
 * File:   mainproject.c
 * Author: knu
 *
 * Created on 2017年12月21日, 下午 5:38
 */
#define _XTAL_FREQ 8000000	/* Define freq */

#include <xc.h>
#include <pic18f4520.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <pic18.h>

// BEGIN CONFIG
#pragma config OSC = INTIO67   // Oscillator Selection bits (HS oscillator)
#pragma config WDT = OFF  // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRT = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON  // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF   // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF   // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config PBADEN = OFF
#pragma config MCLRE = ON
//END CONFIG

int red;
int green;
int blue;
int white;


int effect=0;
int flag=0;

double distance;

void init()
{
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 0;
    
    TRISC=0; //RGB init
    TRISD=0;
    LATC=0;
    LATD=0;
    
    TRISBbits.TRISB0=1;
    red=0;
    green=0;
    blue=0;
    effect=0;
    
    RCONbits.IPEN=1;
    INTCONbits.GIEH=1;
    INTCONbits.INT0IE=1;//enable interrupt 0
    INTCONbits.INT0IF=0;
    INTCON2bits.INTEDG0=1;//high edge trigger
    PORTBbits.RB0=0;
    
    TRISBbits.TRISB4=0; //acivate next pic
    TRISBbits.TRISB5=1; //IR module port
    
    white=0;
}

void rgbshow(int rval,int gval ,int bval){
    if(flag==0){   
        LATCbits.LATC0=1; //r  
        LATCbits.LATC1=1; //g
        LATCbits.LATC2=1; //b
        LATCbits.LATC3=1;
        LATDbits.LATD0=1;
        LATDbits.LATD1=1;
        LATDbits.LATD2=1;
        LATDbits.LATD3=1;
        LATCbits.LATC4=1;
        LATCbits.LATC5=1;
        LATCbits.LATC6=1;
        LATCbits.LATC7=1;
        
        for(int i=0;i<130;i++){
            if((rval--)==0) LATCbits.LATC0=0; //r  
            if((gval--)==0) LATCbits.LATC1=0; //g  
            if((bval--)==0) LATCbits.LATC2=0; //b 
        }
    }
}

void rgbstart()
{
    
    while( red!= 130 ){ //001
    red++;
    rgbshow(red,green,blue);
    __delay_ms(1);
    }
    LATBbits.LATB4=1;
    __delay_ms(10);
    LATBbits.LATB4=0;
    __delay_ms(100);
  
    while( green!= 130 ){ //011
    green++;
    rgbshow(red,green,blue);
    __delay_ms(1);
    }
 
    while( red!= 0 ){ //010
    red--;
    rgbshow(red,green,blue);
    __delay_ms(1);
    }
  
    while( blue!= 130 ){ //110
    blue++;
    rgbshow(red,green,blue);
    __delay_ms(1);
    }
   
    while( red!= 130 ){ //111
    red++;
    rgbshow(red,green,blue);
    __delay_ms(1);
    }
   
    while(green!= 0 ){ //101
    green--;
    rgbshow(red,green,blue);
    __delay_ms(1);
    }
 
    while( red!= 0 ){ //100
    red--;
    rgbshow(red,green,blue);
    __delay_ms(1);
    }
    
    while( blue!= 0 ){ //000
    blue--;
    rgbshow(red,green,blue);
    __delay_ms(1);
    }
}

void wshow(int wval)
{
    LATDbits.LATD4=1; //white
    for(int i=0;i<200;i++){
         if((wval--)==0) LATDbits.LATD4=0; //r  
    }
}

void wstart(){
    while(white!=200){
        white++;
        wshow(white);
    }    
    while(white!=0){
        white--;
        wshow(white);
    }   
}

void interrupt Hi()
{
    if(INTCONbits.INT0IF == 1) {
        PORTBbits.RB0=0;
        INTCONbits.INT0IF = 0; //clear interrupt
        rgbstart();
        rgbstart(); 
       
    } 
    
}

void main(void) {
    init();
    while(1) {
        wstart();
        int k = 10 , l = 255;
        while( k > 0 ) {
            l = 255;
            while( l > 0) {
                l--;
            }
            k--;
        }
        
        if(RB5){
            PORTBbits.RB0=1;
            INTCONbits.INT0IF = 1;
        }
    } 
}
