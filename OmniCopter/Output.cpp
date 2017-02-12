/*
 * Output.cpp
 *
 *  Created on: 2017Äê2ÔÂ6ÈÕ
 *      Author: jiawei
 */
#include "OmniCopter.h"

PropData EscDriver::getPropData()
{
	return this->propData;
}

void EscDriver::setPropData(PropData propData)
{
	this->propData=propData;
}

void EscDriver::escInit()
{
	prop1.attach(PROP_1,ESC_MIN,ESC_MAX);
	prop2.attach(PROP_2,ESC_MIN,ESC_MAX);
	prop3.attach(PROP_3,ESC_MIN,ESC_MAX);
	prop4.attach(PROP_4,ESC_MIN,ESC_MAX);
	prop5.attach(PROP_5,ESC_MIN,ESC_MAX);
	prop6.attach(PROP_6,ESC_MIN,ESC_MAX);
	prop7.attach(PROP_7,ESC_MIN,ESC_MAX);
	prop8.attach(PROP_8,ESC_MIN,ESC_MAX);
}
void EscDriver::excute()
{
	int prop1=map((long )ceil(propData.fProp[0]*PERCISION),F_PORP_MIN*PERCISION,F_PROP_MAX*PERCISION,ESC_MIN,ESC_MAX);
	int prop2=map((long )ceil(propData.fProp[1]*PERCISION),F_PORP_MIN*PERCISION,F_PROP_MAX*PERCISION,ESC_MIN,ESC_MAX);
	int prop3=map((long )ceil(propData.fProp[2]*PERCISION),F_PORP_MIN*PERCISION,F_PROP_MAX*PERCISION,ESC_MIN,ESC_MAX);
	int prop4=map((long )ceil(propData.fProp[3]*PERCISION),F_PORP_MIN*PERCISION,F_PROP_MAX*PERCISION,ESC_MIN,ESC_MAX);
	int prop5=map((long )ceil(propData.fProp[4]*PERCISION),F_PORP_MIN*PERCISION,F_PROP_MAX*PERCISION,ESC_MIN,ESC_MAX);
	int prop6=map((long )ceil(propData.fProp[5]*PERCISION),F_PORP_MIN*PERCISION,F_PROP_MAX*PERCISION,ESC_MIN,ESC_MAX);
	int prop7=map((long )ceil(propData.fProp[6]*PERCISION),F_PORP_MIN*PERCISION,F_PROP_MAX*PERCISION,ESC_MIN,ESC_MAX);
	int prop8=map((long )ceil(propData.fProp[7]*PERCISION),F_PORP_MIN*PERCISION,F_PROP_MAX*PERCISION,ESC_MIN,ESC_MAX);

	this->prop1.writeMicroseconds(prop1);
	this->prop2.writeMicroseconds(prop2);
	this->prop3.writeMicroseconds(prop3);
	this->prop4.writeMicroseconds(prop4);
	this->prop5.writeMicroseconds(prop5);
	this->prop6.writeMicroseconds(prop6);
	this->prop7.writeMicroseconds(prop7);
	this->prop8.writeMicroseconds(prop8);
}

void EscDriver::excute(PropData propData)
{
	this->setPropData(propData);
	this->excute();
}
