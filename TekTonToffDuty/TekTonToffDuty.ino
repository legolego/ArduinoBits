//____________________________________________________________________
// LEARNING DIGITAL OSCILLOSCOPE USING ARDUINO AS SIGNAL GENERATOR
// 
// Date: 2013-12-01            Written by: Mukesh Soni 
//____________________________________________________________________
// OUTPUT DETAILS
//--------------------------------------------------------------------
// Pin # 7 : Square Wave - 1 kHz 
//____________________________________________________________________


void setup()
{
	// put your setup code here, to run once:
	pinMode(7, OUTPUT);
	//pinMode(8, OUTPUT);
}

void loop()
{
	// put your main code here, to run repeatedly:
	digitalWrite(7, HIGH);
	delayMicroseconds(500);
	//digitalWrite(8, LOW);
	//delayMicroseconds(600);

	digitalWrite(7, LOW);
	delayMicroseconds(500);
	//digitalWrite(8, HIGH);
	//delayMicroseconds(600);
}



