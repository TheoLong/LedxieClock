#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Adafruit_NeoPixel.h"
#include <string.h>
#include <stdlib.h>

struct TUBE
{
	int preNum;
	int curNum;
};
class NixieDisp
{
public:
	NixieDisp(int numOfTubes, int pin);
	void roll(int tUp, int tDelay, int color[3]);
	void randomLine(int tShuffle, int tLast);
	void debug();
	String getCurrent() const ;

private:
	//variables
	int NUMPIXELS;
	int tubeNum;
	int LED[11] = {2, 3, 4, 9, 1, 6, 0, 7, 5, 10, 8};//LED mapping
	Adafruit_NeoPixel pixels;
	TUBE* tubes;

	//functions
	void setTube(int tubeNum, int digit);
	void updateTubes_NIXIE();
	void tubeOff(int tubeNum);



};
