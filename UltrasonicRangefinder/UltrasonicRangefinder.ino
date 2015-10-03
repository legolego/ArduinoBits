/*
Ultrasonic rangefinder with an 16x2 LCD screen

Parts: Arduino UNO, 16x2 LCD with (Funduino) I2C interface, HC-SR04 Rangefinder

Pins:

UNO				LCD				Rangefinder
A4				SDA
A5				SLC
11									ECHO
12									TRIG

*/
//Libraries



#include <Wire.h>                
#include <LiquidCrystal_I2C.h>   //Display Library
#include <NewPing.h>             //Sensor Library

//Sensor

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

//Display

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address, can be found with I2C Scanner

																
int val1 = 0;
int analog1 = 0;
int val2 = 0;
int analog2 = 0;

//setup

void setup()
{
	Serial.begin(9600);
	Serial.println("\nUltrasonic Rangefinder");

	lcd.begin(16, 2);

	//Welcome

	lcd.setCursor(3, 0);
	lcd.print("Ultrasonic");
	delay(1000);
	lcd.setCursor(2, 1);
	lcd.print("Rangefinder");
	delay(1000);
	lcd.clear();
	lcd.setCursor(1, 1);
	lcd.print("www.olegs.com");
	lcd.setCursor(0, 0);
	delay(1000);
	
}

void loop() 
{
	delay(500);     // Pause(ms) between pings, min 29ms

	unsigned int uS = sonar.ping();  // Send ping, get ping time in microseconds (uS).
	String dist = String(uS / US_ROUNDTRIP_CM);

	lcd.clear();                    

	lcd.setCursor(2, 0);              
	lcd.print("Rangefinder");       

	lcd.setCursor(0, 1);             
	lcd.print("Distance: ");        
	lcd.setCursor(10, 1);             
	lcd.print(dist); 
	lcd.setCursor(13, 1);             
	lcd.print("cm");  
	
	Serial.println("\nDistance: " + dist + "cm");

}

