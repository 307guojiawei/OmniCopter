/*
 * Log.cpp
 *
 *  Created on: 2017年2月12日
 *      Author: jiawei
 */
#include "Log.h"
#include <OmniCopter.h>

void Log::init()
{
	Serial.begin(115200);
	delay(100);
	Serial.println("Init");
}

void Log::log(char* message,double value)
{
	if(!debugEnable)return;
	if(debugEnable&&showEnable)
	{
		Serial.print(micros());
		Serial.print(message);Serial.print(": ");Serial.println(value);
	}
}

void Log::setDebugMode(bool mode)
{
	this->debugEnable=mode;
}

void Log::oneLoop()
{
	this->showTime++;
	if(showTime==showF)
	{
		showEnable=true;
		showTime=0;
	}else
	{
		showEnable=false;
	}
}
void Log::setFreq(int freq)
{
	this->showF=freq;
}
void Log::showRcInput(OmniCopter o)
{
	if(!debugEnable)return;
	if(debugEnable&&showEnable)
	{
		Serial.print("RC:");
		Serial.print(o.input.Roll[0]);Serial.print(" ");
		Serial.print(o.input.Roll[1]);Serial.print(" ");
		Serial.print(o.input.Roll[2]);Serial.print(" ");
		Serial.print(o.input.Move[0]);Serial.print(" ");
		Serial.print(o.input.Move[1]);Serial.print(" ");
		Serial.print(o.input.Move[2]);Serial.println(" ");
	}
}
void Log::showFreq(OmniCopter o)
{
	if(!debugEnable)return;


	if(debugEnable&&showEnable)
	{
		unsigned long int now=micros();
		unsigned long int thisTime=now-this->lastTime;
		Serial.print("OuterLoop:");Serial.print(1000000.0/(thisTime/(double)showF));Serial.println("HZ");
		Serial.print("InnerLoop:");Serial.print(1000000.0/(thisTime/(double)showF)*(double)INNER_OUTER_RATIO);Serial.println("HZ");
		this->lastTime=now;

	}
}


