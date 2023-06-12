/*
 * File:   manejoLCD.c
 * Author: ANTHONY
 *
 * Created on 5 de junio de 2023, 11:38 AM
 */


#include <xc.h>
#include "LCD.h"
#include "cabecera.h"
#define _XTAL_FREQ 4000000UL

void main(void) {
    OSCCON = 0X52;
    TRISD = 0X00;
    ANSELD = 0X00;
    
    LCD_INIT();
    ESCRIBE_MENSAJE2("HOLA MUNDO PERFECTO");
//    CURSOR_SHIFTRIGHT();
//    CURSOR_SHIFTRIGHT();
//    ENVIA_CHAR('A');
    __delay_ms(1000);
    DISPLAY_SHIFTLEFT(); //desplaza 1 posicion el contenido del lcd
    __delay_ms(1000);
    DISPLAY_SHIFTLEFT();
    __delay_ms(1000);
    DISPLAY_SHIFTLEFT();
    __delay_ms(1000);
    DISPLAY_SHIFTLEFT();
    __delay_ms(1000);
    DISPLAY_SHIFTLEFT();
    __delay_ms(1000);
    
}
