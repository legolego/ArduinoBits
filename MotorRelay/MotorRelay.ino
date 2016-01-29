//Programa : Controle 2 motores DC usando Ponte H L298N
//Autor : FILIPEFLOP
//http://tronixlabs.com/news/tutorial-l298n-dual-motor-controller-module-2a-and-arduino/
//http://blog.whatgeek.com.pt/arduino/l298-dual-h-bridge-motor-driver/

// connect motor controller pins to Arduino digital pins
// motor one
int enB = 3;
int IN3 = 5;
int IN4 = 4;



void setup()
{

	Serial.begin(9600);
	Serial.print("Hello World\n");

	pinMode(enB, OUTPUT);
	pinMode(IN3, OUTPUT);
	pinMode(IN4, OUTPUT);

	
}

void demoOne()
{
	// this function will run the motors in both directions at a fixed speed

	// turn on motor A
	digitalWrite(IN3, HIGH);
	digitalWrite(IN4, LOW);
	
	// set speed to 200 out of possible range 0~255
	analogWrite(enB, 200);

	delay(2000);
	// now change motor directions
	digitalWrite(IN3, LOW);
	digitalWrite(IN4, HIGH);
	
	delay(2000);
	// now turn off motors
	digitalWrite(IN3, LOW);
	digitalWrite(IN4, LOW);
	
}
void demoTwo()
{
	// this function will run the motors across the range of possible speeds
	// note that maximum speed is determined by the motor itself and the operating voltage
	// the PWM values sent by analogWrite() are fractions of the maximum speed possible 
	// by your hardware
	// turn on motors
	digitalWrite(IN3, LOW);
	digitalWrite(IN4, HIGH);
	
	// accelerate from zero to maximum speed
	for (int i = 0; i < 256; i++)
	{
		analogWrite(enB, i);
		
		delay(20);
	}
	// decelerate from maximum speed to zero
	for (int i = 255; i >= 0; --i)
	{
		analogWrite(enB, i);
		
		delay(20);
	}
	// now turn off motors
	digitalWrite(IN3, LOW);
	digitalWrite(IN4, LOW);
	
}
void loop()
{
	demoOne();
	delay(1000);
	demoTwo();
	delay(1000);	
	Serial.print("Loop\n");
}