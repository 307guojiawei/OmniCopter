/*
 * Output.cpp
 *
 *  Created on: 2017年2月6日
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
	prop[0]=map((long )ceil(propData.fProp[0]*PERCISION),F_PORP_MIN*PERCISION,F_PROP_MAX*PERCISION,ESC_MIN+ESC_OFFSET_1,ESC_MAX+ESC_OFFSET_1);
	prop[1]=map((long )ceil(propData.fProp[1]*PERCISION),F_PORP_MIN*PERCISION,F_PROP_MAX*PERCISION,ESC_MIN+ESC_OFFSET_2,ESC_MAX+ESC_OFFSET_2);
	prop[2]=map((long )ceil(propData.fProp[2]*PERCISION),F_PORP_MIN*PERCISION,F_PROP_MAX*PERCISION,ESC_MIN+ESC_OFFSET_3,ESC_MAX+ESC_OFFSET_3);
	prop[3]=map((long )ceil(propData.fProp[3]*PERCISION),F_PORP_MIN*PERCISION,F_PROP_MAX*PERCISION,ESC_MIN+ESC_OFFSET_4,ESC_MAX+ESC_OFFSET_4);
	prop[4]=map((long )ceil(propData.fProp[4]*PERCISION),F_PORP_MIN*PERCISION,F_PROP_MAX*PERCISION,ESC_MIN+ESC_OFFSET_5,ESC_MAX+ESC_OFFSET_5);
	prop[5]=map((long )ceil(propData.fProp[5]*PERCISION),F_PORP_MIN*PERCISION,F_PROP_MAX*PERCISION,ESC_MIN+ESC_OFFSET_6,ESC_MAX+ESC_OFFSET_6);
	prop[6]=map((long )ceil(propData.fProp[6]*PERCISION),F_PORP_MIN*PERCISION,F_PROP_MAX*PERCISION,ESC_MIN+ESC_OFFSET_7,ESC_MAX+ESC_OFFSET_7);
	prop[7]=map((long )ceil(propData.fProp[7]*PERCISION),F_PORP_MIN*PERCISION,F_PROP_MAX*PERCISION,ESC_MIN+ESC_OFFSET_8,ESC_MAX+ESC_OFFSET_8);
	for(int i=0;i<8;i++)
	{
		if(prop[i]<ESC_MID+ESC_START_POINT&&prop[i]>ESC_MID-ESC_START_POINT)
		{
			prop[i]=ESC_MID;
		}
	}
	this->prop1.writeMicroseconds(prop[0]);
	this->prop2.writeMicroseconds(prop[1]);
	this->prop3.writeMicroseconds(prop[2]);
	this->prop4.writeMicroseconds(prop[3]);
	this->prop5.writeMicroseconds(prop[4]);
	this->prop6.writeMicroseconds(prop[5]);
	this->prop7.writeMicroseconds(prop[6]);
	this->prop8.writeMicroseconds(prop[7]);
}

void EscDriver::excute(PropData propData)
{
	this->setPropData(propData);
	this->excute();
}
