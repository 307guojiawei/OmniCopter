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
	SERIALNUM.begin(DEBUG_SERIAL_RATE);
	delay(100);
	SERIALNUM.println("Init#");
}

void Log::log(char* message,double value)
{
	if(!debugEnable)return;
	if(debugEnable&&showEnable)
	{
		SERIALNUM.print(micros());
		SERIALNUM.print(message);SERIALNUM.print(": ");SERIALNUM.print(value);SERIALNUM.println("#");
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
		SERIALNUM.println("--$");
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
		SERIALNUM.print("RC:");
		SERIALNUM.print(o.input.Roll[0]);SERIALNUM.print(" ");
		SERIALNUM.print(o.input.Roll[1]);SERIALNUM.print(" ");
		SERIALNUM.print(o.input.Roll[2]);SERIALNUM.print(" ");
		SERIALNUM.print(o.input.Move[0]);SERIALNUM.print(" ");
		SERIALNUM.print(o.input.Move[1]);SERIALNUM.print(" ");
		SERIALNUM.print(o.input.Move[2]);SERIALNUM.println("#");
	}
}
void Log::showFreq(OmniCopter o)
{
	if(!debugEnable)return;


	if(debugEnable&&showEnable)
	{
		unsigned long int now=micros();
		unsigned long int thisTime=now-this->lastTime;
		SERIALNUM.print("OuterLoop:");SERIALNUM.print(1000000.0/(thisTime/(double)showF));SERIALNUM.println("HZ #");
		SERIALNUM.print("InnerLoop:");SERIALNUM.print(1000000.0/(thisTime/(double)showF)*(double)config.INNER_OUTER_RATIO);SERIALNUM.println("HZ #");
		this->lastTime=now;

	}
}
void Log::showSensor(OmniCopter o)
{
	if(!debugEnable)return;
	if(debugEnable&&showEnable)
	{
		SERIALNUM.print("Angle:");
		SERIALNUM.print(o.sensor.sensorRaw.bodyAngle.roll);SERIALNUM.print(" ");
		SERIALNUM.print(o.sensor.sensorRaw.bodyAngle.pitch);SERIALNUM.print(" ");
		SERIALNUM.print(o.sensor.sensorRaw.bodyAngle.yaw);SERIALNUM.println("# ");
		SERIALNUM.print("Quaternion:");
		SERIALNUM.print(o.sensor.sensorRaw.bodyQuaternion.q[0]);SERIALNUM.print(" ");
		SERIALNUM.print(o.sensor.sensorRaw.bodyQuaternion.q[1]);SERIALNUM.print(" ");
		SERIALNUM.print(o.sensor.sensorRaw.bodyQuaternion.q[2]);SERIALNUM.print(" ");
		SERIALNUM.print(o.sensor.sensorRaw.bodyQuaternion.q[3]);SERIALNUM.println("# ");
	}
}
void Log::showForce(OmniCopter o)
{
	if(!debugEnable)return;
	if(debugEnable&&showEnable)
	{
		SERIALNUM.print("DesireBodyRate:");
		SERIALNUM.print(o.desiredBodyRate.rollRate);SERIALNUM.print(" ");
		SERIALNUM.print(o.desiredBodyRate.pitchRate);SERIALNUM.print(" ");
		SERIALNUM.print(o.desiredBodyRate.yawRate);SERIALNUM.println("# ");
		SERIALNUM.print("Force&Torque:");
		SERIALNUM.print(o.desiredCondition.fDes[0]);SERIALNUM.print(" ");
		SERIALNUM.print(o.desiredCondition.fDes[1]);SERIALNUM.print(" ");
		SERIALNUM.print(o.desiredCondition.fDes[2]);SERIALNUM.print(" ");
		SERIALNUM.print(o.desiredCondition.tDes[0]);SERIALNUM.print(" ");
		SERIALNUM.print(o.desiredCondition.tDes[1]);SERIALNUM.print(" ");
		SERIALNUM.print(o.desiredCondition.tDes[2]);SERIALNUM.println("# ");

	}
}

void Log::showEscOutput(OmniCopter o)
{
	if(!debugEnable)return;
	if(debugEnable&&showEnable)
	{
		SERIALNUM.print("ESC: ");
		SERIALNUM.print(o.escDriver.prop[0]);SERIALNUM.print(" ");
		SERIALNUM.print(o.escDriver.prop[1]);SERIALNUM.print(" ");
		SERIALNUM.print(o.escDriver.prop[2]);SERIALNUM.print(" ");
		SERIALNUM.print(o.escDriver.prop[3]);SERIALNUM.print(" ");
		SERIALNUM.print(o.escDriver.prop[4]);SERIALNUM.print(" ");
		SERIALNUM.print(o.escDriver.prop[5]);SERIALNUM.print(" ");
		SERIALNUM.print(o.escDriver.prop[6]);SERIALNUM.print(" ");
		SERIALNUM.print(o.escDriver.prop[7]);SERIALNUM.println("# ");
	}
}
