#include "Global.h"

#define SERVO_MIN_POS	20
#define SERVO_MAX_POS	150
#define THRESHOLD		200

//average data variables 
int averageX = 0, averageY = 0, averageZ = 0;

void setup() 
{
	Serial.begin(9600);
	servo.attach(SERVO_SIGNAL_PIN);
	servo.write(SERVO_MIN_POS);
	Serial.println("start");
  
	//sum 10 samples:
	Serial.println("get average data:");
	for(int i=0; i<10;i++)
	{
		accelerometer.update(); //update current accelerometer values
		averageX += accelerometer.getX();
		averageY += accelerometer.getY();
		averageZ += accelerometer.getZ();
		delay(2); //wait for accelerometer to update;
	}
	//calc average:
	averageX /= 10;
	averageY /= 10;
	averageZ /= 10;

	//print average data
	Serial.print("x:");  Serial.print(averageX); 
	Serial.print(",y: ");  Serial.print(averageY); 
	Serial.print(",z: ");  Serial.print(averageZ); 
	Serial.println("");
	Serial.println("start running");
}

void loop() 
{	
	//read data from ADXL345
	accelerometer.update();
	
	//print results:
	Serial.print("x:");  	Serial.print(accelerometer.getX()); 
	Serial.print(",y: ");  	Serial.print(accelerometer.getY()); 
	Serial.print(",z: ");  	Serial.print(accelerometer.getZ()); 
	
	//calc difference from average: 
	int diff = abs(accelerometer.getX() - averageX);
	diff += abs(accelerometer.getY() - averageY);
	diff += abs(accelerometer.getZ() - averageZ);
	
	//print the difference
	Serial.print(", difference from average:");  Serial.println(diff);
	
	//above threshold move servo:
	if(diff > THRESHOLD)
	{
		servo.write(SERVO_MAX_POS);
		Serial.println("major changed happened");
		delay(1000);
    
		servo.write(SERVO_MIN_POS);
	}
	
	delay(10);
}
