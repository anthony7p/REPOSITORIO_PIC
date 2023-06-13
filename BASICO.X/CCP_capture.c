/*
 * File:   moduloCCP.c
 * Author: ANTHONY
 *
 * Created on 12 de junio de 2023, 09:43 PM
 */


#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL

unsigned char dec_mil, millar, centena, decena, unidad;
unsigned int cont;

void configuro(void) {
    OSCCON = 0X52;
    TRISD = 0;
    ANSELD = 0;
    // RC2-CPP1 como entrada digital
    TRISCbits.RC2 = 1;
    ANSELCbits.ANSC2 = 0;

    // configuracion d la interrupcion por CCP1
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.CCP1IE = 1;
    PIR1bits.CCP1IF = 0;

    // configuracion del TIMER1
    T1CON = 0X32; // prescaler 8 , disable tmr1, clock source Fosc/4, r/w 16 bits

    // configuracion del CCP1 en modo capture usando TMR1
    CCP1CON = 0x06; // captura cada 4 flanco subida
    CCPTMRSbits.C2TSEL = 0;

    TMR1 = 0;
    T1CONbits.TMR1ON = 1;
}

void convierte(unsigned int numero) {
    dec_mil = numero / 10000;
    millar = (numero % 10000) / 1000;
    centena = (numero % 1000) / 100;
    decena = (numero % 100) / 10;
    unidad = numero % 10;
}

void main(void) {
    configuro();
    LCD_INIT();
    ESCRIBE_MENSAJE2("ESPERANDO...");
    while (1);
}

void __interrupt() INT_CCP1(void) {
    PIR1bits.CCP1IF = 0;
    POS_CURSOR(2, 0);
    convierte(CCPR1);
    ESCRIBE_MENSAJE2("CUENTAS: ");
    ENVIA_CHAR(dec_mil + 0x30);
    ENVIA_CHAR(millar + 0x30);
    ENVIA_CHAR(centena + 0x30);
    ENVIA_CHAR(decena + 0x30);
    ENVIA_CHAR(unidad + 0x30);
}