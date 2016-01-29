/*
 Name:		LCDKeypadShield.ino
 Created:	10/17/2015 9:26:36 PM
 Author:	nikolsky
*/

#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int readkey;
void setup() {
	lcd.begin(16, 2);
	lcd.print("LCD + Keypad");
}
void loop() {
	lcd.setCursor(0, 1);
	lcd.print("Shield");
	readkey = analogRead(0);
	
	String key = String(readkey);

	

	Serial.println("\nKey: " + key);

	if (readkey<50) { //0
		lcd.clear();
		lcd.print("Btn Right: " + key);
	}
	else if (readkey<150) { //99
		lcd.clear();
		lcd.print("Btn Up: " + key);
	}
	else if (readkey<300) { //
		lcd.clear();
		lcd.print("Btn Down: " + key);
	}
	else if (readkey<500) {
		lcd.clear();
		lcd.print("Btn Left: " + key);
	}
	else if (readkey<750) {
		lcd.clear();
		lcd.print("Btn Select: " + key);
	}
	else if (readkey>=750) {
		lcd.clear();
		lcd.print("Btn None: " + key);
	}

	else {
		lcd.clear();
		lcd.print("Btn ???: " + key);
	}

	delay(500);
}