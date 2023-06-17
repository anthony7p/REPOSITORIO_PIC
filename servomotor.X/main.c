/*
 * File:   main.c
 * Author: Alumnos
 *
 * Created on 15 de junio de 2023, 02:11 PM
 */


#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL

void configuro(void){
    OSCCON = 0X52;
    TRISAbits.TRISA0 = 0;
    ANSELAbits.ANSA0 = 1;
    
    TRISBbits.RB0 = 1;
    ANSELBbits.ANSB0 = 0;
    TRISBbits.RB1 = 1;
    ANSELBbits.ANSB1 = 0;
    
    INTCON2bits.RBPU = 0;
    WPUBbits.WPUB0 = 1;
    WPUBbits.WPUB1 = 1;
    
    
    TRISCbits.TRISC6 = 0;
    ANSELCbits.ANSC6 = 0;
    TRISCbits.TRISC7 = 1;
    ANSELCbits.ANSC7 = 0;
    
    TRISD = 0X0F;
    ANSELD = 0X0F;
    
    TRISE = 0XF8;
    ANSELE = 0XF8;
    
    SPBRGH1 = 0;
    SPBRG1 = 25;
    TXSTAbits.BRGH = 1;
    RCSTAbits.SPEN = 1;
    TXSTAbits.TXEN = 1;
    
    
    LCD_INIT();

}
void pantallazo_inicial(void){
    POS_CURSOR(1,0);
    ESCRIBE_MENSAJE2("MICRO semana 13");
    POS_CURSOR(2,0);
    ESCRIBE_MENSAJE2("rendirse jamas");
    __delay_ms(3000);
    BORRAR_LCD();
}

void EUSART_Datasend(unsigned char dato){
    TXREG1 = dato;
    while(TXSTAbits.TRMT == 0);
}
void main(void) {
    configuro();
    pantallazo_inicial();
    while(1){
        if(PORTBbits.RB0 == 0){
            POS_CURSOR(1,0);
            ESCRIBE_MENSAJE2("Enviando hola");
            EUSART_Datasend('H');
            EUSART_Datasend('O');
            EUSART_Datasend('L');
            EUSART_Datasend('A');
            __delay_ms(1000);
            BORRAR_LCD();
        }
        
    }
}
