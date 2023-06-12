/*
 * File:   maincode.c
 * Author: ANTHONY
 *
 * Created on 3 de junio de 2023, 06:34 PM
 */


#include <xc.h>
#define _XTAL_FREQ 4000000UL
unsigned char i;

void main(void) {
    OSCCON = 0X52;
    TRISD = 0X00;
    ANSELD = 0X00;
    while(1){
        i = 0x54;
        i = (i << 2)|(i >> 6); //Rotar la variable i 2 bits a la izquierda
        i = (i << 1)|(i >> 7); //Rotar la variable i 1 bit a la izquierda
//    LATD = 0x8A;
//    LATD = (PORTD << 1)|(PORTD >> 7);
//    LATD = (PORTD << 1)|(PORTD >> 7);
//    LATD = (PORTD << 1)|(PORTD >> 7);
//    LATD = (PORTD << 1)|(PORTD >> 7);
//    
    }
}
