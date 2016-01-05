#ifndef RGBLED_H
#define RGBLED_H

#include "arduino.h"
#include <SPI.h>

#define MEASURE_MODE 0x08 
#define TRIGGER_MODE 0xC0

class ADXL345
{
	public:
		ADXL345(int CS);
		void update();   
		void powerControl(char option=MEASURE_MODE);	
		void dataForamt(char option=0x01); //0x00 = +_2g range, 0x01 = +-4g range, 0X02 = +-8g range, 0x03 = +-16g range
		int getX();
		int getY();
		int getZ();
	private:
		int x,y,z;
		int CSPin;
				
		const char powerCTL = 0x2D;    //Power Control Register
		const char dataFormat = 0x31;
		const char dataRegister = 0x32;   //the first data register


};
#endif //__RGBLED_H
