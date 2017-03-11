#include "OmniCopter.h"

void OmniCopter::init()
{
	pinMode(2,INPUT);
	pinMode(PROP_1,OUTPUT);
	pinMode(PROP_2,OUTPUT);
	pinMode(PROP_3,OUTPUT);
	pinMode(PROP_4,OUTPUT);
	pinMode(PROP_5,OUTPUT);
	pinMode(PROP_6,OUTPUT);
	pinMode(PROP_7,OUTPUT);
	pinMode(PROP_8,OUTPUT);
	//config.loadConfig();

	this->sensor.sensorInit();
	this->escDriver.escInit();

}


void OmniCopter::getRawInput(struct Input_Raw* input,int* RC1)
{
	static int lastRC[7];
	int buf[7];
	for(int j=0;j<7;j++)
	{
		if(abs(RC1[j]-lastRC[j])>=config.RC_PERCISION)
		{
			buf[j]=RC1[j];
			lastRC[j]=RC1[j];
		}else
		{
			buf[j]=lastRC[j];
		}
	}
	input->Roll[0]=map(buf[0],RC_MIN,RC_MAX,-input->Roll_Max[0],input->Roll_Max[0]);	//滚转
	input->Roll[1]=map(buf[1],RC_MIN,RC_MAX,-input->Roll_Max[1],input->Roll_Max[1]);	//俯仰
	input->Roll[2]=map(buf[3],RC_MIN,RC_MAX,-input->Roll_Max[2],input->Roll_Max[2]);	//偏航
	input->Move[0]=map(buf[4],RC_MIN,RC_MAX,-input->Move_Max[0],input->Move_Max[0]);	//x轴平动
	input->Move[1]=map(buf[5],RC_MIN,RC_MAX,-input->Move_Max[1],input->Move_Max[1]);	//y轴平动
	input->Move[2]=map(buf[2],RC_MIN,RC_MAX,0,input->Move_Max[2]);	//油门（z轴平动）





}
void OmniCopter::getRcValue(int* Rc)
{
	this->RC=Rc;
}

void OmniCopter::getRcInput(int* RC1)
{
	struct Input_Raw input;
	getRawInput(&input,RC1);
	this->input=input;
	this->convertedInput=convertedInput.getInputConverted(input);

}

void OmniCopter::getRawSensorInput()
{
	this->sensor.getSensorData();
}

void OmniCopter::getCompleteInput(int* RC)
{
	this->getRcValue(RC);
	this->getRawSensorInput();
	this->getRcInput(this->RC);
	this->convertedInput=this->convertedInput.getCompleteInput(this->sensor.sensorRaw);
}

void OmniCopter::attitudeProcess()
{
	this->attitudeController.process(this->convertedInput,this->sensor.sensorRaw);
	this->desiredBodyRate=this->attitudeController.getDesireBodyRate();
}

void OmniCopter::bodyRateProcess()
{
	this->sensor.getSensorRate();
	this->bodyRateController.process(this->desiredBodyRate,this->sensor.sensorRaw);
	this->desiredCondition.tDes[0]=this->bodyRateController.desireTorque.tDes[0];
	this->desiredCondition.tDes[1]=this->bodyRateController.desireTorque.tDes[1];
	this->desiredCondition.tDes[2]=this->bodyRateController.desireTorque.tDes[2];}

void OmniCopter::positionProcess()
{
	this->sensor.getPosition();
	this->positionController.process(this->convertedInput,this->sensor.sensorRaw,this->desiredCondition,this->sensor);

	this->desiredCondition.fDes[0]=this->positionController.desireCondition.fDes[0];
	this->desiredCondition.fDes[1]=this->positionController.desireCondition.fDes[1];
	this->desiredCondition.fDes[2]=this->positionController.desireCondition.fDes[2];
}

void OmniCopter::controlAllocateProcess()
{
	this->controlAllocator.process(this->desiredCondition);
	this->propData=this->controlAllocator.getPropData();

}

void OmniCopter::excute()
{
	this->escDriver.excute(this->propData);
}
