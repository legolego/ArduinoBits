#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define NeoPixPin 6


// Uses a PIR sensor to detect movement, buzzes a buzzer
// more info here: http://blog.makezine.com/projects/pir-sensor-arduino-alarm/
// email me, John Park, at jp@jpixl.net
// based upon:
// PIR sensor tester by Limor Fried of Adafruit
// tone code by michael@thegrebs.com


const int ledPin = 13;                // choose the pin for the LED
const int inputPin = 2;               // choose the input pin (for PIR sensor)
const int motorPin = 3;
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
//int pinSpeaker = 10;           //Set up a speaker on a PWM pin (digital 9, 10, or 11)

const int redpin = 10; //select the pin for the red LED

const int bluepin = 11; // select the pin for the blue LED

const int greenpin = 9;// select the pin for the green LED

Adafruit_NeoPixel strip = Adafruit_NeoPixel(7, NeoPixPin, NEO_GRB + NEO_KHZ800);


void setup() {
	pinMode(ledPin, OUTPUT);      // declare LED as output
	pinMode(inputPin, INPUT);     // declare sensor as input
	
	pinMode(redpin, OUTPUT);

	pinMode(bluepin, OUTPUT);

	pinMode(greenpin, OUTPUT);
	pinMode(motorPin, OUTPUT);

	Serial.begin(9600);

	strip.begin();
	strip.show(); // Initialize all pixels to 'off'
}

void loop() {
	val = digitalRead(inputPin);  // read input value
	if (val == HIGH) {            // check if the input is HIGH
		digitalWrite(ledPin, HIGH);  // turn LED ON
		//playTone(300, 160);
		digitalWrite(motorPin, HIGH);
		//rgbLED();
		rainbow(20);
		
		if (pirState == LOW) {
			// we have just turned on
			Serial.println("Motion detected!");
			// We only want to print on the output change, not state
			pirState = HIGH;
		}
		delay(1000);
	}
	else {
		digitalWrite(ledPin, LOW); // turn LED OFF
		//playTone(0, 0);
		//rgbLEDOff();
		strip.begin();
		strip.show(); // Initialize all pixels to 'off'
		strip.clear();
		digitalWrite(motorPin, LOW);
		delay(1000);
		if (pirState == HIGH) {
			// we have just turned off
			Serial.println("Motion ended!");
			// We only want to print on the output change, not state
			pirState = LOW;
		}
	}
}

void rgbLEDOff()
{
	analogWrite(redpin, 0);
	analogWrite(bluepin, 0);
	analogWrite(greenpin, 0);}

void rgbLED()
{
	ledRedSlowDown(3);
	ledRedSlowUp(3);
	ledGreenSlowDown(3);
	ledGreenSlowUp(3);
}

void ledRedSlowDown(int delayInterval)
{
	int valLED;
	for (valLED = 255; valLED>0; valLED--)
	{
		analogWrite(redpin, valLED);
		analogWrite(bluepin, 0);
		analogWrite(greenpin, 0);
		delay(delayInterval);
	}
}

void ledRedSlowUp(int delayInterval)
{
	int valLED;
	for (valLED = 0; valLED<=255; valLED++)
	{
		analogWrite(redpin, valLED);
		analogWrite(bluepin, 0);
		analogWrite(greenpin, 0);
		delay(delayInterval);
	}
}

void ledGreenSlowDown(int delayInterval)
{
	int valLED;
	for (valLED = 255; valLED>0; valLED--)
	{
		analogWrite(redpin, 0);
		analogWrite(bluepin, 0);
		analogWrite(greenpin, valLED);
		delay(delayInterval);
	}
}

void ledGreenSlowUp(int delayInterval)
{
	int valLED;
	for (valLED = 0; valLED <= 255; valLED++)
	{
		analogWrite(redpin, 0);
		analogWrite(bluepin, 0);
		analogWrite(greenpin, valLED);
		delay(delayInterval);
	}
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
	for (uint16_t i = 0; i<strip.numPixels(); i++) {
		strip.setPixelColor(i, c);
		strip.show();
		delay(wait);
	}
}

void rainbow(uint8_t wait) {
	uint16_t i, j;

	for (j = 0; j<256; j++) {
		for (i = 0; i<strip.numPixels(); i++) {
			strip.setPixelColor(i, Wheel((i + j) & 255));
		}
		strip.show();
		delay(wait);
	}
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
	uint16_t i, j;

	for (j = 0; j<256 * 5; j++) { // 5 cycles of all colors on wheel
		for (i = 0; i< strip.numPixels(); i++) {
			strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
		}
		strip.show();
		delay(wait);
	}
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
	for (int j = 0; j<10; j++) {  //do 10 cycles of chasing
		for (int q = 0; q < 3; q++) {
			for (int i = 0; i < strip.numPixels(); i = i + 3) {
				strip.setPixelColor(i + q, c);    //turn every third pixel on
			}
			strip.show();

			delay(wait);

			for (int i = 0; i < strip.numPixels(); i = i + 3) {
				strip.setPixelColor(i + q, 0);        //turn every third pixel off
			}
		}
	}
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
	for (int j = 0; j < 256; j++) {     // cycle all 256 colors in the wheel
		for (int q = 0; q < 3; q++) {
			for (int i = 0; i < strip.numPixels(); i = i + 3) {
				strip.setPixelColor(i + q, Wheel((i + j) % 255));    //turn every third pixel on
			}
			strip.show();

			delay(wait);

			for (int i = 0; i < strip.numPixels(); i = i + 3) {
				strip.setPixelColor(i + q, 0);        //turn every third pixel off
			}
		}
	}
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
	WheelPos = 255 - WheelPos;
	if (WheelPos < 85) {
		return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	}
	if (WheelPos < 170) {
		WheelPos -= 85;
		return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
	WheelPos -= 170;
	return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}