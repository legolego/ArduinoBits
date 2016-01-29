/*
 Name:		SimpleVoltmeter.ino
 Created:	10/31/2015 4:55:02 PM
 Author:	nikolsky
*/

//Libraries
#include <Wire.h>                
#include <LiquidCrystal_I2C.h>   //Display Library


//Display
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address, can be found with I2C Scanner


float vPow = 4.7;
float r1 = 100000;
float r2 = 10000;

void setup() {
	Serial.begin(9600);

	// Send ANSI terminal codes
	//Serial.print("\x1B");
	//Serial.print("[2J");
	//Serial.print("\x1B");
	//Serial.println("[H");
	// End ANSI terminal codes

	Serial.println("--------------------");
	Serial.println("DC VOLTMETER");
	Serial.print("Maximum Voltage: ");
	Serial.print((int)(vPow / (r2 / (r1 + r2))));
	Serial.println("V");
	Serial.println("--------------------");
	Serial.println("");


	lcd.begin(16, 2);

	//Welcome

	lcd.setCursor(4, 0);
	lcd.print("Simple");
	delay(1000);
	lcd.setCursor(3, 1);
	lcd.print("Voltmeter");
	delay(1000);
	lcd.clear();

	lcd.setCursor(0, 0);
	lcd.print("Max volts: ");
	lcd.print((int)(vPow / (r2 / (r1 + r2))));


	lcd.setCursor(1, 1);
	lcd.print("www.olegs.com");
	lcd.setCursor(0, 0);

	delay(2000);
}

void loop() {
	float v = (analogRead(0) * vPow) / 1024.0;
	float v2 = v / (r2 / (r1 + r2));

	// Send ANSI terminal codes
	//Serial.print("\x1B");
	//Serial.print("[1A");
	// End ANSI terminal codes

	Serial.println(v2);

	String volts = String(v2);

	lcd.clear();
	lcd.setCursor(0, 1);
	lcd.print("Volts: " + volts);
	delay(500);
}
