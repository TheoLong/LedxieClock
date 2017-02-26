#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Adafruit_NeoPixel.h"
#include "NixieDisp.h"
#define CLOCK_PRESCALER_1   (0x0)
NixieDisp *nixie;
void setup()
{
	nixie = new NixieDisp(8,6);
	Serial.begin(115200);
	Serial.println("--- Start Serial Monitor SEND_RCVE ---");
}

void loop()
{
	nixie->randomLine(2000,1000*10);
	//Serial.println(nixie->getCurrent());

	//nixie->debug();
}
