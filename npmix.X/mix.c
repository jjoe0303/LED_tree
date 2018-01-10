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

int red2;
int green2;
int blue2;

int white;


double distance;
int cc;

void init()
{
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 0;
    
    TRISC=0; //RGB init
    TRISD=0;
    LATCbits.LATC0=1; //r  
        LATCbits.LATC1=1; //g
        LATCbits.LATC2=1; //b
        LATCbits.LATC3=1;
        LATDbits.LATD0=1;
        LATDbits.LATD1=1;
        LATCbits.LATC7=0; //r  
        LATCbits.LATC6=0; //g
        LATCbits.LATC5=0; //b
        LATCbits.LATC4=0;
        LATDbits.LATD3=0;
        LATDbits.LATD2=0;
    
    TRISBbits.TRISB0=1;
    red=0;
    green=0;
    blue=0;
    red2=0;
    green2=0;
    blue2=0;
    
    RCONbits.IPEN=1;
    INTCONbits.GIEH=1;
    INTCONbits.INT0IF=0;
    INTCONbits.INT0IE=1;//enable interrupt 0
    INTCON2bits.INTEDG0=1;//high edge trigger
    LATBbits.LATB0=0;
    PORTBbits.RB0=0;
    
    TRISBbits.TRISB4=0; //acivate next pic
    TRISBbits.TRISB5=1; //IR module port
    LATBbits.LATB5=0;
    
    white=0;
    cc=10;
}

void rgbshowone(int rval,int gval ,int bval,int flag){
    if(flag==0){   
        LATCbits.LATC0=0; //r  
        LATCbits.LATC1=0; //g
        LATCbits.LATC2=0; //b
        LATCbits.LATC3=1;
        LATDbits.LATD0=1;
        LATDbits.LATD1=1;
        
        for(int i=0;i<140;i++){
            if((rval--)==0) LATCbits.LATC0=1; //r  
            if((gval--)==0) LATCbits.LATC1=1; //g  
            if((bval--)==0) LATCbits.LATC2=1; //b 
        }
    }
    
    else if(flag==1){   
        LATCbits.LATC0=1; //r  
        LATCbits.LATC1=1; //g
        LATCbits.LATC2=1; //b
        LATCbits.LATC3=0;
        LATDbits.LATD0=0;
        LATDbits.LATD1=0;
        
        for(int i=0;i<140;i++){
            if((rval--)==0) LATCbits.LATC3=1; //r  
            if((gval--)==0) LATDbits.LATD0=1; //g  
            if((bval--)==0) LATDbits.LATD1=1; //b 
        }
    }
    else if(flag==2){
        LATCbits.LATC7=1; //r  
        LATCbits.LATC6=1; //g
        LATCbits.LATC5=1; //b
        LATCbits.LATC4=0;
        LATDbits.LATD3=0;
        LATDbits.LATD2=0;
        for(int i=0;i<140;i++){
            if((rval--)==0) LATCbits.LATC7=0; //r  
            if((gval--)==0) LATCbits.LATC6=0; //g  
            if((bval--)==0) LATCbits.LATC5=0; //b 
        }
    }
    
     else if(flag==3){
        LATCbits.LATC7=0; //r  
        LATCbits.LATC6=0; //g
        LATCbits.LATC5=0; //b
        LATCbits.LATC4=1;
        LATDbits.LATD3=1;
        LATDbits.LATD2=1;
       
        for(int i=0;i<140;i++){
            if((rval--)==0) LATCbits.LATC4=0; //r  
            if((gval--)==0) LATDbits.LATD3=0; //g  
            if((bval--)==0) LATDbits.LATD2=0; //b 
        }
    }
}
void rgbshowsix(int rval,int gval ,int bval,int rval2,int gval2 ,int bval2,int flag)
{
    if(flag==4){   
        LATCbits.LATC0=0; //r  
        LATCbits.LATC1=0; //g
        LATCbits.LATC2=0; //b
        LATCbits.LATC3=1;
        LATDbits.LATD0=1;
        LATDbits.LATD1=1;
        LATCbits.LATC7=1; //r  
        LATCbits.LATC6=1; //g
        LATCbits.LATC5=1; //b
        LATCbits.LATC4=0;
        LATDbits.LATD3=0;
        LATDbits.LATD2=0;
        
        for(int i=0;i<140;i++){
            if((rval--)==0) LATCbits.LATC0=1; //r  
            if((gval--)==0) LATCbits.LATC1=1; //g  
            if((bval--)==0) LATCbits.LATC2=1; //b 
            if((rval2--)==0) LATCbits.LATC7=0; //r  
            if((gval2--)==0) LATCbits.LATC6=0; //g  
            if((bval2--)==0) LATCbits.LATC5=0; //b 
        }
    }
    
    else if(flag==5){  
        LATCbits.LATC0=1; //r  
        LATCbits.LATC1=1; //g
        LATCbits.LATC2=1; //b
        LATCbits.LATC3=0;
        LATDbits.LATD0=0;
        LATDbits.LATD1=0;
        LATCbits.LATC7=0; //r  
        LATCbits.LATC6=0; //g
        LATCbits.LATC5=0; //b
        LATCbits.LATC4=1;
        LATDbits.LATD3=1;
        LATDbits.LATD2=1;
       
        for(int i=0;i<140;i++){
            if((rval--)==0) LATCbits.LATC3=1; //r  
            if((gval--)==0) LATDbits.LATD0=1; //g  
            if((bval--)==0) LATDbits.LATD1=1; //b 
            if((rval2--)==0) LATCbits.LATC4=0; //r  
            if((gval2--)==0) LATDbits.LATD3=0; //g  
            if((bval2--)==0) LATDbits.LATD2=0; //b 
        }
    }
}
void rgbshow(int rval,int gval ,int bval,int rval2,int gval2 ,int bval2,int flag)
{
  int i=60;
  if(flag<4){  
    while(i--){
        rgbshowone(rval,gval,bval,flag);
    }
  }
  else{
    while(i--){
        rgbshowsix(rval,gval,bval,rval2,gval2,bval2,flag);
    }
  }
}

void zerorgb(){
     LATCbits.LATC0=1; //r  
     LATCbits.LATC1=1; //g
     LATCbits.LATC2=1; //b
     LATCbits.LATC3=1;
     LATDbits.LATD0=1;
     LATDbits.LATD1=1;
     LATCbits.LATC7=0; //r  
     LATCbits.LATC6=0; //g
     LATCbits.LATC5=0; //b
     LATCbits.LATC4=0;
     LATDbits.LATD3=0;
     LATDbits.LATD2=0;
    red=0;
    green=0;
    blue=0;
    red2=0;
    green2=0;
    blue2=0;
}
void rgbstart()
{
    while( red <= 70 ){ //001
        red=red+10;
        rgbshow(red,green,blue,red2,green2,blue2,0);

        rgbshow(red,green,blue,red2,green2,blue2,1);

    }
    
    while( red <= 140 ){ //001
        red=red+10;
        red2=red2+10;
        rgbshow(red,green,blue,red2,green2,blue2,4);

        rgbshow(red,green,blue,red2,green2,blue2,5);
   
    }
     LATBbits.LATB4=0;
  //  __delay_ms(10);
    LATBbits.LATB4=1;
  //  __delay_ms(100);
    LATBbits.LATB4=0;
  //  __delay_ms(1);
  
   while( green <= 70 ){ //011
        green=green+10;
        red2=red2+10;
        rgbshow(red,green,blue,red2,green2,blue2,4);

        rgbshow(red,green,blue,red2,green2,blue2,5);

    }
    
    while( green <= 140 ){ //011
        green=green+10;
        green2=green2+10;
        rgbshow(red,green,blue,red2,green2,blue2,4);

        rgbshow(red,green,blue,red2,green2,blue2,5); 
    }
 
    while(red>=70){//010
        red=red-10;
        green2=green2+10;
        rgbshow(red,green,blue,red2,green2,blue2,4);

        rgbshow(red,green,blue,red2,green2,blue2,5); 
    }
    while( red>= 0 ){ //010
        //red--;
        red=red-10;
        red2=red2-10;
        rgbshow(red,green,blue,red2,green2,blue2,4);

        rgbshow(red,green,blue,red2,green2,blue2,5); 
    }
    
   
   while( blue <= 70 ){ //110
        blue=blue+10;
        red2=red2-10;
        rgbshow(red,green,blue,red2,green2,blue2,4);

        rgbshow(red,green,blue,red2,green2,blue2,5);

    }
    
    while( blue <= 140 ){ //110
        blue=blue+10;
        blue2=blue2+10;
        rgbshow(red,green,blue,red2,green2,blue2,4);

        rgbshow(red,green,blue,red2,green2,blue2,5); 
    }
   
  
    while( red <= 70 ){ //111
        red=red+10;
        blue2=blue2+10;
        rgbshow(red,green,blue,red2,green2,blue2,4);

        rgbshow(red,green,blue,red2,green2,blue2,5);
    }
    
    while( red <= 140 ){ //111
        red=red+10;
        red2=red2+10;
        rgbshow(red,green,blue,red2,green2,blue2,4);

        rgbshow(red,green,blue,red2,green2,blue2,5); 
    }
    
   while(green>=70){//101
        green=green-10;
        red2=red2+10;
        rgbshow(red,green,blue,red2,green2,blue2,4);

        rgbshow(red,green,blue,red2,green2,blue2,5); 
    }
    while(green>= 0 ){ //101
        //red--;
        green=green-10;
        green2=green2-10;
        rgbshow(red,green,blue,red2,green2,blue2,4);

        rgbshow(red,green,blue,red2,green2,blue2,5); 
    }
 
    while(red>=70){//100
        red=red-10;
        green2=green2-10;
        rgbshow(red,green,blue,red2,green2,blue2,4);

        rgbshow(red,green,blue,red2,green2,blue2,5); 
    }
    while( red>= 0 ){ //100
        //red--;
        red=red-10;
        red2=red2-10;
        rgbshow(red,green,blue,red2,green2,blue2,4);

        rgbshow(red,green,blue,red2,green2,blue2,5); 
    }
   
    while(blue>=70){//000
        blue=blue-10;
        red2=red2-10;
        rgbshow(red,green,blue,red2,green2,blue2,4);

        rgbshow(red,green,blue,red2,green2,blue2,5); 
    }
    while( blue>= 0 ){ //000
        blue=blue-10;
        blue2=blue2-10;
        rgbshow(red,green,blue,red2,green2,blue2,4);

        rgbshow(red,green,blue,red2,green2,blue2,5); 
    }
    
    while( blue2 >= 0 ){ //000(ex)
        LATCbits.LATC0=1; //r  
        LATCbits.LATC1=1; //g
        LATCbits.LATC2=1; //b
        LATCbits.LATC3=1;
        LATDbits.LATD0=1;
        LATDbits.LATD1=1;
        blue2=blue2-10;
        rgbshow(red,green,blue,red2,green2,blue2,2);

        rgbshow(red,green,blue,red2,green2,blue2,3); 
    }
    zerorgb();
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
        LATDbits.LATD4=0;
        rgbstart();
        PORTBbits.RB0=0;
        LATBbits.LATB0=0;
        INTCONbits.INT0IF = 0; //clear interrupt     
    } 
    
}

void main(void) {
    init();
    while(1) {
       while(cc>0){ 
        wstart();
        int k = 10 , l = 255;
        while( k > 0 ) {
            l = 255;
            while( l > 0) {
                l--;
            }
            k--;
        }
        cc--;
       }
        rgbstart();
        cc=20;
    } 
}
