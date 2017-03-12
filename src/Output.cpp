/*
 * Output.cpp
 *
 *  Created on: 2017年2月6日
 *      Author: jiawei
 */
#include "OmniCopter.h"
#include "Config.h"
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
	prop[0]=map((long )ceil(propData.fProp[0]*config.PERCISION),config.F_PROP_MIN*config.PERCISION,config.F_PROP_MAX*config.PERCISION,ESC_MIN,ESC_MAX);
	prop[1]=map((long )ceil(propData.fProp[1]*config.PERCISION),config.F_PROP_MIN*config.PERCISION,config.F_PROP_MAX*config.PERCISION,ESC_MIN,ESC_MAX);
	prop[2]=map((long )ceil(propData.fProp[2]*config.PERCISION),config.F_PROP_MIN*config.PERCISION,config.F_PROP_MAX*config.PERCISION,ESC_MIN,ESC_MAX);
	prop[3]=map((long )ceil(propData.fProp[3]*config.PERCISION),config.F_PROP_MIN*config.PERCISION,config.F_PROP_MAX*config.PERCISION,ESC_MIN,ESC_MAX);
	prop[4]=map((long )ceil(propData.fProp[4]*config.PERCISION),config.F_PROP_MIN*config.PERCISION,config.F_PROP_MAX*config.PERCISION,ESC_MIN,ESC_MAX);
	prop[5]=map((long )ceil(propData.fProp[5]*config.PERCISION),config.F_PROP_MIN*config.PERCISION,config.F_PROP_MAX*config.PERCISION,ESC_MIN,ESC_MAX);
	prop[6]=map((long )ceil(propData.fProp[6]*config.PERCISION),config.F_PROP_MIN*config.PERCISION,config.F_PROP_MAX*config.PERCISION,ESC_MIN,ESC_MAX);
	prop[7]=map((long )ceil(propData.fProp[7]*config.PERCISION),config.F_PROP_MIN*config.PERCISION,config.F_PROP_MAX*config.PERCISION,ESC_MIN,ESC_MAX);
	for(int i=0;i<8;i++)
	{
		if(prop[i]<ESC_MID+config.ESC_START_POINT&&prop[i]>ESC_MID-config.ESC_START_POINT)
		{
			prop[i]=ESC_MID;
		}
	}
	prop[0]+=ESC_OFFSET_1;
	prop[1]+=ESC_OFFSET_2;
	prop[2]+=ESC_OFFSET_3;
	prop[3]+=ESC_OFFSET_4;
	prop[4]+=ESC_OFFSET_5;
	prop[5]+=ESC_OFFSET_6;
	prop[6]+=ESC_OFFSET_7;
	prop[7]+=ESC_OFFSET_8;
	for(int i=0;i<8;i++)
	{
		if(prop[i]<ESC_MIN)
		{
			prop[i]=ESC_MIN;
		}else if(prop[i]>ESC_MAX)
		{
			prop[i]=ESC_MAX;
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
