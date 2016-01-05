#include "ADXL345.h"

ADXL345::ADXL345(int CS)
{
	CSPin = CS; //Chip select pin
	pinMode(CSPin, OUTPUT); //set Chip select as OUTPUT
	
	//SPI configuration
	SPI.begin();
	SPI.setDataMode(SPI_MODE3);
	digitalWrite(CSPin, HIGH);
    	 
	dataForamt(); 	//set it to -+4g range as default
	powerControl(); //set it to measure mode as default
}

void ADXL345::update()
{
	digitalWrite(CSPin, LOW);
	  
	SPI.transfer(dataRegister | TRIGGER_MODE); //start reading from DATAX0 with stream mode(0x40)
	
	//reading and put the value in the right place
	x =  (int)SPI.transfer(0xFF);
	x |= ((int)SPI.transfer(0xFF)<<8);
	y =  (int)SPI.transfer(0xFF);
	y |= ((int)SPI.transfer(0xFF)<<8);
	z =  (int)SPI.transfer(0xFF);
	z |= ((int)SPI.transfer(0xFF)<<8);
	
	digitalWrite(CSPin, HIGH);
}

//to consider create write register function instead of copy write register code each time.

void ADXL345::powerControl(char option) //Change the ADXL345 power control by changing POWER_CTL register
{ 
	digitalWrite(CSPin, LOW); 
	
	SPI.transfer(powerCTL);
	SPI.transfer(option);
	
	digitalWrite(CSPin, HIGH);
}

void ADXL345::dataForamt(char option) //Change the ADXL345 power control by changing POWER_CTL register
{
	
	digitalWrite(CSPin, LOW);
	
	SPI.transfer(dataFormat);
	SPI.transfer(option);
	
	digitalWrite(CSPin, HIGH);	
} 	 

//getters:	
int ADXL345::getX() {return x;}
int ADXL345::getY() {return y;}
int ADXL345::getZ() {return z;}


