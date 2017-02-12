#include "OmniCopter.h"

void OmniCopter::init()
{
	pinMode(ROLL_X,INPUT);
	pinMode(ROLL_Y,INPUT);
	pinMode(ROLL_Z,INPUT);
	pinMode(MOVE_X,INPUT);
	pinMode(MOVE_Y,INPUT);
	pinMode(MOVE_Z,INPUT);
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

void OmniCopter::getRawInput(struct Input_Raw* input)
{


#ifdef MEGA_2560
	unsigned char ucsr1b=UCSR1B;
	UCSR1B&=0x7f;
#endif
#ifndef DEBUG_MODE
	input->Roll[0]=(double)map(pulseIn(ROLL_X,1),RC_MIN,RC_MAX,-input->Roll_Max[0],input->Roll_Max[0]);
	input->Roll[1]=(double)map(pulseIn(ROLL_Y,1),RC_MIN,RC_MAX,-input->Roll_Max[1],input->Roll_Max[1]);
	input->Roll[2]=(double)map(pulseIn(ROLL_Z,1),RC_MIN,RC_MAX,-input->Roll_Max[2],input->Roll_Max[2]);

	input->Move[0]=(double)map(pulseIn(MOVE_X,1),RC_MIN,RC_MAX,-input->Move_Max[0],input->Move_Max[0]);
	input->Move[1]=(double)map(pulseIn(MOVE_Y,1),RC_MIN,RC_MAX,-input->Move_Max[1],input->Move_Max[1]);
	input->Move[2]=(double)map(pulseIn(MOVE_Z,1),RC_MIN,RC_MAX,-input->Move_Max[2],input->Move_Max[2]);
#endif
#ifdef MEGA_2560
	UCSR1B=ucsr1b;
#endif


}

void OmniCopter::getRcInput()
{
	struct Input_Raw input;
	getRawInput(&input);
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
	this->getRcInput();
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
