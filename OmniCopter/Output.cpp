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
	int prop1=map((long )ceil(propData.fProp[0]*PERCISION),F_PORP_MIN*PERCISION,F_PROP_MAX*PERCISION,0,180);
	int prop2=map((long )ceil(propData.fProp[1]*PERCISION),F_PORP_MIN*PERCISION,F_PROP_MAX*PERCISION,0,180);
	int prop3=map((long )ceil(propData.fProp[2]*PERCISION),F_PORP_MIN*PERCISION,F_PROP_MAX*PERCISION,0,180);
	int prop4=map((long )ceil(propData.fProp[3]*PERCISION),F_PORP_MIN*PERCISION,F_PROP_MAX*PERCISION,0,180);
	int prop5=map((long )ceil(propData.fProp[4]*PERCISION),F_PORP_MIN*PERCISION,F_PROP_MAX*PERCISION,0,180);
	int prop6=map((long )ceil(propData.fProp[5]*PERCISION),F_PORP_MIN*PERCISION,F_PROP_MAX*PERCISION,0,180);
	int prop7=map((long )ceil(propData.fProp[6]*PERCISION),F_PORP_MIN*PERCISION,F_PROP_MAX*PERCISION,0,180);
	int prop8=map((long )ceil(propData.fProp[7]*PERCISION),F_PORP_MIN*PERCISION,F_PROP_MAX*PERCISION,0,180);
	this->prop1.write(prop1);
	this->prop2.write(prop2);
	this->prop3.write(prop3);
	this->prop4.write(prop4);
	this->prop5.write(prop5);
	this->prop6.write(prop6);
	this->prop7.write(prop7);
	this->prop8.write(prop8);
}

void EscDriver::excute(PropData propData)
{
	this->setPropData(propData);
	this->excute();
}
