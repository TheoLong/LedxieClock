#include "NixieDisp.h"
NixieDisp::NixieDisp(int numOfTubes, int pin)
{
	tubeNum = numOfTubes;
	NUMPIXELS = tubeNum * 11;
	tubes = new TUBE[numOfTubes];
	for (int i = 0; i < tubeNum; i++)
	{
		tubes[i].preNum = tubes[i].curNum;
		tubes[i].curNum = 12;
	}
	//initialize pixels
	pixels = Adafruit_NeoPixel(NUMPIXELS, 6, NEO_GRB + NEO_KHZ800);
	//start the pixel;
	pixels.begin();
}

void NixieDisp::roll(int tUp, int tDelay, int color[3])
{
	pixels.setBrightness(255);
	for (int i = 0; i < 11; i++)
	{
		for (int j = LED[i]; j < NUMPIXELS; j = j + 11)
		{
			pixels.setPixelColor(j, pixels.Color(color[0], color[1], color[2])); //orange
		}
		pixels.show();
		delay(tDelay);
		// pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
		if (i == 0)
		{
			for (int j = LED[10]; j < NUMPIXELS; j = j + 11)
			{
				pixels.setPixelColor(j, pixels.Color(0, 0, 0)); //orange
			}
		}
		else
		{
			for (int j = LED[i - 1]; j < NUMPIXELS; j = j + 11)
			{
				pixels.setPixelColor(j, pixels.Color(0, 0, 0));
			}
		}
		pixels.show(); // This sends the updated pixel color to the hardware.

		delay(tUp); // Delay for a period of time (in milliseconds).

	}
}

void NixieDisp::randomLine(int tShuffle, int tLast)
{
	int dim = 255;
	pixels.setBrightness(dim);
	pixels.show();
	updateTubes_NIXIE();
	//shuffle random numbers
	unsigned long tStart;
	tStart = millis();
	unsigned long tEnd = tStart + tShuffle;
	int randomNum;
	//shuffle for time
	while (millis() <= tEnd)
	{
		for (int i = 0; i < tubeNum; i++)
		{
			randomNum = random(10);
			while (tubes[i].curNum == randomNum)
			{
				randomNum = random(10);
			}
			setTube(i, randomNum);
		}
		updateTubes_NIXIE();

	}
	//fix decimal dot
	setTube(6, 10);
	updateTubes_NIXIE();
	//generate random stop number
	int list[tubeNum] = {0,1,2,3,4,5,-1,7};
	for (int a=0; a<tubeNum; a++)
	{
	 int r = random(tubeNum);
	 int temp = list[a];
	 list[a] = list[r];
	 list[r] = temp;
	}
	//stop according to random order

	for(int i = 0; i < tubeNum; i ++)
		{
			tStart = millis();
			tEnd = tStart + 200;
			while(millis() <= tEnd)
			{
				//mark stop shuffle
				list[i] = -1;
				for (int j = 0; j < tubeNum; j++)
				{
					if(list[j] >= 0)
					{
						randomNum = random(10);
										while (tubes[i].curNum == randomNum)
										{
											randomNum = random(10);
										}
										setTube(list[j], randomNum);
					}
				}
				updateTubes_NIXIE();
			}
		}
//	for(int j = dim; j < 255; j ++)
//	{
////		for (int i = 0; i < tubeNum; i++)
////			{
////				if(tubes[i].curNum < 11)
////				pixels.setPixelColor(LED[tubes[i].curNum] + (11 * i), pixels.Color(255, j, 0));
////			}
//			pixels.setBrightness(j);
//			pixels.show();
//		  	delay(10);
//	}
//	for(int j = 255; j > dim; j --)
//		{
////			for (int i = 0; i < tubeNum; i++)
////				{
////					//if(tubes[i].curNum < 11)
////					pixels.setPixelColor(LED[tubes[i].curNum] + (11 * i), pixels.Color(255, j, 0));
////				}
//				pixels.setBrightness(j);
//				pixels.show();
//			  	delay(10);
//		}
	delay(tLast);


}

void NixieDisp::setTube(int tubeNum, int digit)
{
	tubes[tubeNum].preNum = tubes[tubeNum].curNum;
	tubes[tubeNum].curNum = digit;
}

void NixieDisp::debug()
{

}

void NixieDisp::updateTubes_NIXIE()
{
	//turn on new numbers
	for (int i = 0; i < tubeNum; i++)
	{
		if(tubes[i].curNum < 11)
		{
			pixels.setPixelColor(LED[tubes[i].curNum] + (11 * i), pixels.Color(255, 55, 0));
		}
	}
	pixels.show();
	delay(5);
	//turn off old numbers
	for (int i = 0; i < tubeNum; i++)
	{
		if(tubes[i].preNum != tubes[i].curNum)
		pixels.setPixelColor(LED[tubes[i].preNum] + (11 * i), pixels.Color(0, 0, 0));

	}
	pixels.show();
	delay(10);
}

void NixieDisp::tubeOff(int tubeNum)
{
	for (int i = 0; i < 11; i++)
	{
		pixels.setPixelColor(i + (11 * tubeNum), pixels.Color(0, 0, 0));
	}
}

String NixieDisp::getCurrent() const
{

	String output = "";
	for (int i = tubeNum - 1; i >= 0; i--)
	{
		int thisNum = tubes[i].curNum;
		output = output + " | " + String(thisNum);
	}
	return output;
}

void NixieDisp::timmer()
{


	TimerOne Timer1;
	Timer1.initialize(1000000);


	while (true)
	{

	}
}

void NixieDisp::updateTime()
{

}
