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


	this->sensor.sensorInit();
	this->escDriver.escInit();

}


void OmniCopter::getRawInput(struct Input_Raw* input,int* RC1)
{
	input->Roll[0]=map(RC1[0],RC_MIN,RC_MAX,-input->Roll_Max[0],input->Roll_Max[0]);	//滚转
	input->Roll[1]=map(RC1[1],RC_MIN,RC_MAX,-input->Roll_Max[1],input->Roll_Max[1]);	//俯仰
	input->Roll[2]=map(RC1[3],RC_MIN,RC_MAX,-input->Roll_Max[2],input->Roll_Max[2]);	//偏航
	input->Move[0]=map(RC1[4],RC_MIN,RC_MAX,-input->Move_Max[0],input->Move_Max[0]);	//x轴平动
	input->Move[1]=map(RC1[5],RC_MIN,RC_MAX,-input->Move_Max[1],input->Move_Max[1]);	//y轴平动
	input->Move[2]=map(RC1[2],RC_MIN,RC_MAX,0,input->Move_Max[2]);	//油门（z轴平动）





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
	Input_Converted convertedInput;
	convertedInput=convertedInput.getInputConverted(input);
	this->convertedInput=convertedInput;
}

void OmniCopter::getRawSensorInput()
{
	this->sensor.getSensorData();
}

void OmniCopter::getCompleteInput()
{
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
	this->desiredCondition=this->bodyRateController.getDesireTorque();
}

void OmniCopter::positionProcess()
{
	this->positionController.process(this->convertedInput,this->sensor.sensorRaw,this->desiredCondition);
	this->desiredCondition=this->positionController.getDesireCondition();
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
