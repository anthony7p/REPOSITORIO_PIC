/*
 * File:   main.c
 * Author: Alumnos
 *
 * Created on 1 de junio de 2023, 02:58 PM
 */


#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL


unsigned int resultado_ADC;
unsigned char nivel;
unsigned char millar, centena, decena, unidad;
void configuro (void){
    OSCCON = 0x52;
    TRISAbits.RA0 = 1;
    ANSELAbits.ANSA0 = 1;
    TRISAbits.RA3 = 1;
    ANSELAbits.ANSA3 = 0;
    TRISBbits.RB0 = 1;
    ANSELBbits.ANSB0 = 0;
    INTCON2bits.RBPU = 0;
    WPUBbits.WPUB0 = 0;
    TRISD = 0x08;
    ANSELD = 0x00;
    LCD_INIT();
    PR2 = 62;
    CCPR1L = 31;                //duty cycle inicial 50%
    T2CON = 0x06;               //TMR2 on, 1:16 psc
    CCP1CON = 0x0C;
    
    INTCONbits.GIE = 1;
    INTCONbits.INT0IE =1;
    INTCON2bits.INTEDG0 = 0; 
}
void convierte (unsigned int numero){
    millar = numero / 1000;
    centena = (numero % 1000) / 100;
    decena = ( numero % 100) / 10;
    unidad = numero % 10;
}
unsigned int tomamuestra_ADC(void){
    ADCON0bits.GO = 1;
    while ( ADCON0bits.GO == 1);
    return((ADRESH << 8) + ADRESL);
}


void __interrupt() INT0_ISR(void){
    INTCONbits.INT0IF = 0;
    switch (nivel){
        case 0:
            CCPR1L = 5;
            nivel = 1;
            break;
        case 1:
            CCPR1L = 15;
            nivel = 2;
            break;
        case 2:
            CCPR1L = 25;
            nivel = 3;
            break;
        case 3:
            CCPR1L = 35;
            nivel = 4;
            break;
        case 4:
            CCPR1L = 45;
            nivel = 5;
            break;
        case 5:
            CCPR1L = 55;
            nivel = 6;
            break;
        case 6:
            CCPR1L = 65;
            nivel = 7;
            break;
    }
}

void main(void) {
    configuro();
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("primer ejemplo");
    while(1){
        convierte(tomamuestra_ADC()/10);
        POS_CURSOR(2,0);
        ESCRIBE_MENSAJE2("LM35:");
        ENVIA_CHAR(centena+0x30);
        ENVIA_CHAR(decena+0x30);
        ENVIA_CHAR(unidad+0x30);
        ENVIA_CHAR(0xDF);
        ENVIA_CHAR('C');
    }
    

}
