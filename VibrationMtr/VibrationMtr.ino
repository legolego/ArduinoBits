const int motorPin = 3;
const int ledPin = 13;

void setup()
{
	pinMode(motorPin, OUTPUT);
	pinMode(ledPin, OUTPUT);
}

void loop()
{
	digitalWrite(motorPin, HIGH);
	digitalWrite(ledPin, HIGH);
	delay(2500);
	digitalWrite(motorPin, LOW);
	digitalWrite(ledPin, LOW);
	delay(2500);
}