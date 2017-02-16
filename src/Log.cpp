/*
 *  Log.cpp
 *
 *  Created on: 2017年2月12日
 *      Author: jiawei
 */
#include "Log.h"
#include <OmniCopter.h>

/*Only when it is in debug mode can this class work.*/

void Log::init()
{
	Serial.begin(DEBUG_SERIAL_RATE);
	delay(100);
	Serial.println("Init#");
}

void Log::log(char* message,double value)
{
	if(!debugEnable)return;
	if(debugEnable&&showEnable)
	{
		Serial.print(micros());
		Serial.print(message);Serial.print(": ");Serial.print(value);Serial.println("#");
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
		Serial.println("--$");
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
		Serial.print(o.input.Move[2]);Serial.println("#");
	}
}
void Log::showFreq(OmniCopter o)
{
	if(!debugEnable)return;


	if(debugEnable&&showEnable)
	{
		unsigned long int now=micros();
		unsigned long int thisTime=now-this->lastTime;
		Serial.print("OuterLoop:");Serial.print(1000000.0/(thisTime/(double)showF));Serial.println("HZ #");
		Serial.print("InnerLoop:");Serial.print(1000000.0/(thisTime/(double)showF)*(double)INNER_OUTER_RATIO);Serial.println("HZ #");
		this->lastTime=now;

	}
}
void Log::showSensor(OmniCopter o)
{
	if(!debugEnable)return;
	if(debugEnable&&showEnable)
	{
		Serial.print("Angle:");
		Serial.print(o.sensor.sensorRaw.bodyAngle.roll);Serial.print(" ");
		Serial.print(o.sensor.sensorRaw.bodyAngle.pitch);Serial.print(" ");
		Serial.print(o.sensor.sensorRaw.bodyAngle.yaw);Serial.println("# ");
		Serial.print("Quaternion:");
		Serial.print(o.sensor.sensorRaw.bodyQuaternion.q[0]);Serial.print(" ");
		Serial.print(o.sensor.sensorRaw.bodyQuaternion.q[1]);Serial.print(" ");
		Serial.print(o.sensor.sensorRaw.bodyQuaternion.q[2]);Serial.print(" ");
		Serial.print(o.sensor.sensorRaw.bodyQuaternion.q[3]);Serial.println("# ");
	}
}
void Log::showForce(OmniCopter o)
{
	if(!debugEnable)return;
	if(debugEnable&&showEnable)
	{
		Serial.print("DesireBodyRate:");
		Serial.print(o.desiredBodyRate.rollRate);Serial.print(" ");
		Serial.print(o.desiredBodyRate.pitchRate);Serial.print(" ");
		Serial.print(o.desiredBodyRate.yawRate);Serial.println("# ");
		Serial.print("Force&Torque:");
		Serial.print(o.desiredCondition.fDes[0]);Serial.print(" ");
		Serial.print(o.desiredCondition.fDes[1]);Serial.print(" ");
		Serial.print(o.desiredCondition.fDes[2]);Serial.print(" ");
		Serial.print(o.desiredCondition.tDes[0]);Serial.print(" ");
		Serial.print(o.desiredCondition.tDes[1]);Serial.print(" ");
		Serial.print(o.desiredCondition.tDes[2]);Serial.println("# ");

	}
}

void Log::showEscOutput(OmniCopter o)
{
	if(!debugEnable)return;
	if(debugEnable&&showEnable)
	{
		Serial.print("ESC: ");
		Serial.print(o.escDriver.prop[0]);Serial.print(" ");
		Serial.print(o.escDriver.prop[1]);Serial.print(" ");
		Serial.print(o.escDriver.prop[2]);Serial.print(" ");
		Serial.print(o.escDriver.prop[3]);Serial.print(" ");
		Serial.print(o.escDriver.prop[4]);Serial.print(" ");
		Serial.print(o.escDriver.prop[5]);Serial.print(" ");
		Serial.print(o.escDriver.prop[6]);Serial.print(" ");
		Serial.print(o.escDriver.prop[7]);Serial.println("# ");
	}
}
