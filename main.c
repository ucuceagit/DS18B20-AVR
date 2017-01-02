/**
LCD Library is based on the AVR-GCC library of Andrei Ostanin
https://github.com/aostanin/avr-hd44780

DS18B20 Routines from Davide Gironi
http://davidegironi.blogspot.com/2014/09/a-ds18b20-1-wire-digital-thermometer.html

Processor: Atmega 328P
Clock: 16MHz
Bootloader: Optiboot 5 (Arduino Uno)
Compiler: AVR-GCC 4.9.2
By: Tiktak
January 3, 2017

LCD RS - PB0
LCD RW - GND
LCD EN - PB1
LCD D4 - PB2
LCD D5 - PB3
LCD D6 - PB4
LCD D7 - PB5

DS18B20 DATA - PD7

**/

#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include "lcd/lcd.h"
#include "ds18b20/ds18b20.h"


int main(void) {
	char printbuff[10];
	char kelvinbuff[10];
	double d = 0;
	double k = 0;

	//init lcd
	lcd_init();
	lcd_clear();
	
	
	lcd_set_cursor(0,0);
	lcd_puts("DS18B20 AVR");
	_delay_ms(1000);
	lcd_clear();
	
	while(1) {
		d = ds18b20_gettemp();
		k = d + 273.15;
		
		dtostrf(d,6, 2, printbuff);
		dtostrf(k,7,2,kelvinbuff);
		
		lcd_set_cursor(0,0);
		lcd_puts("Temp:");
		lcd_puts(printbuff);
		lcd_write((char)223);
		lcd_puts("C");
		lcd_set_cursor(0,1);
		lcd_puts("Temp:");
		lcd_puts(kelvinbuff);
		lcd_write((char)223);
		lcd_puts("K");

		_delay_ms(500);
	}
	
	return 0;
}
