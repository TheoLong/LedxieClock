#include <Arduino.h>

void setup()
{
	Serial.begin(115200);
}

void loop()
{
	Serial.println("123");
	delay(1200);
}
