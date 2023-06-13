/*
 * File:   caracteres.c
 * Author: ANTHONY
 *
 * Created on 12 de junio de 2023, 08:07 PM
 */


#include <xc.h>
#include "cabecera.h"
#include "LCD.h"
#define _XTAL_FREQ 4000000UL
#define ROMBO 0
char rombo []= {0x00,0x04,0x0A,0x11,0x11,0x0A,0x04,0x00};


void configuro (void){
    OSCCON = 0X52;
    TRISD = 0;
    ANSELD = 0;
    LCD_INIT();
    
}
void main(void) {
    unsigned char i;
    configuro();
    GENERACARACTER(rombo, ROMBO);
    for (i=0; i<6 ; i++){
        ENVIA_CHAR(ROMBO);
        ENVIA_CHAR(' ');
        
    }
    ENVIA_CHAR(ROMBO);
    
    while(1);
}
