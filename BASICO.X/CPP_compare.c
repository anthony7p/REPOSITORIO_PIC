/*
 * File:   CPP_compare.c
 * Author: ANTHONY
 *
 * Created on June 13, 2023, 1:48 PM
 */


#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL

unsigned char dec_mil, millar, centena, decena, unidad;
unsigned int count;
 
void configuro (void){
    OSCCON = 0X52;
    TRISD = 0;
    ANSELD = 0;
    
    // configuration pin CCP2
    TRISCbits.RC1 = 0;
    
    // configurar TIMER3
    T3CON = 0X32; // clock source fosc/4, presc 8, r/w 16 bits,Timer3 off
    
    // configurar modulo CCP en modo compare
    CCP2CON = 0X02; // toggle pin CCP2 on match
    CCPTMRSbits.C2TSEL = 1; // modulo CCP usara timer3
    CCPR2 = 0XFF;
    
    // configurar interrupcion
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE2bits.CCP2IE = 1;
    
    TMR3 = 0;
    
    
    T3CONbits.TMR3ON = 1;
   
    LCD_INIT();
}

void convierte (unsigned int numero){
    dec_mil = numero / 10000;
    millar = (numero % 10000)/1000;
    centena = (numero % 1000)/100;
    decena = (numero % 100)/10;
    unidad = numero % 10;
}

void main(void) {
    configuro();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("ESPERA...");
    while(1){
        POS_CURSOR(2,0);
        convierte(TMR3);
        ESCRIBE_MENSAJE2("CUENTA: ");
        ENVIA_CHAR(dec_mil + 0x30);
        ENVIA_CHAR(millar + 0x30);
        ENVIA_CHAR(centena + 0x30);
        ENVIA_CHAR(decena + 0x30);
        ENVIA_CHAR(unidad + 0x30);
    
    }
         
}

void __interrupt() INT_CCP2(void){
    PIR2bits.CCP2IF = 0;
    
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("YA HAY MATCH");
    
}








