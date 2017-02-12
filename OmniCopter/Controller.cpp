/*
 * Controller.cpp
 *
 *  Created on: 2017年2月6日
 *      Author: jiawei
 */
#include "OmniCopter.h"
#include "Controller.h"
BodyRate AttitudeController::getDesireBodyRate()
{
	return this->desireCondition;
}

void AttitudeController::process(Input_Converted desireInput,Sensor_Raw sensorData)
{
	Quaternion qErr=sensorData.bodyQuaternion.reverse()*desireInput.Roll;	//18
	BodyRate desireBodyRate,ff;	//19，ff为20
	Quaternion qX;
	qX.q[0]=0;
	qX.q[1]=sensorData.bodyRate.rollRate;
	qX.q[2]=sensorData.bodyRate.pitchRate;
	qX.q[3]=sensorData.bodyRate.yawRate;
	Quaternion qdot=desireInput.Roll.constantMutiply(0.5)*qX;
	Quaternion qBuff=qErr.constantMutiply(2);
	Quaternion qBuff2=desireInput.Roll.reverse();
	qBuff=qBuff*qBuff2;
	qBuff=qBuff*qdot;
	qBuff2=qErr.reverse();
	qBuff=qBuff*qBuff2;
	ff.rollRate=qBuff.q[1];
	ff.pitchRate=qBuff.q[2];
	ff.yawRate=qBuff.q[3];
	desireBodyRate.rollRate=(2/TATT)*(qErr.q[0]>0?1:-1)*qErr.q[1]+ff.rollRate;
	desireBodyRate.pitchRate=(2/TATT)*(qErr.q[0]>0?1:-1)*qErr.q[2]+ff.pitchRate;
	desireBodyRate.yawRate=(2/TATT)*(qErr.q[0]>0?1:-1)*qErr.q[3]+ff.yawRate;
	this->desireCondition=desireBodyRate;
}

DesireCondition BodyRateController::getDesireTorque()
{
	return this->desireTorque;
}

void BodyRateController::process(BodyRate desireBodyRate,Sensor_Raw sensorData)
{
	this->desireTorque.tDes[0]=(1/TRATE)*J*(desireBodyRate.rollRate-sensorData.bodyRate.rollRate)+(sensorData.bodyRate.pitchRate*J*sensorData.bodyRate.yawRate-sensorData.bodyRate.yawRate*J*sensorData.bodyRate.pitchRate);
	this->desireTorque.tDes[1]=(1/TRATE)*J*(desireBodyRate.pitchRate-sensorData.bodyRate.pitchRate)+(sensorData.bodyRate.yawRate*J*sensorData.bodyRate.rollRate-sensorData.bodyRate.rollRate*J*sensorData.bodyRate.yawRate);
	this->desireTorque.tDes[2]=(1/TRATE)*J*(desireBodyRate.yawRate-sensorData.bodyRate.yawRate)+(sensorData.bodyRate.rollRate*J*sensorData.bodyRate.pitchRate-sensorData.bodyRate.pitchRate*J*sensorData.bodyRate.rollRate);
}

DesireCondition PositionController::getDesireCondition()
{
	return this->desireCondition;
}

void PositionController::process(Input_Converted input,Sensor_Raw sensorData,DesireCondition desireInput)
{
	this->desireCondition=desireInput;
	this->desireCondition.fDes[0]=input.Move[0];
	this->desireCondition.fDes[1]=input.Move[1];
	this->desireCondition.fDes[2]=input.Move[2];
}

PropData ControlAllocator::getPropData()
{
	return this->propData;
}

void ControlAllocator::process(DesireCondition d)
{
	this->propData.fProp[0]=-0.295753175473055*d.fDes[0]+0.079246824526945*d.fDes[1]+0.216506350946110*d.fDes[2]+0.045753175473055*d.tDes[0]-0.170753175473055*d.tDes[1]+0.125*d.tDes[2];
	this->propData.fProp[1]=0.079246824526945*d.fDes[0]+0.295753175473055*d.fDes[1]-0.216506350946110*d.fDes[2]-0.170753175473055*d.tDes[0]-0.045753175473055*d.tDes[1]-0.125*d.tDes[2];
	this->propData.fProp[2]=-0.079246824526945*d.fDes[0]-0.295753175473055*d.fDes[1]-0.216506350946110*d.fDes[2]+0.170753175473055*d.tDes[0]+0.045753175473055*d.tDes[1]-0.125*d.tDes[2];
	this->propData.fProp[3]=0.295753175473055*d.fDes[0]-0.079246824526945*d.fDes[1]+0.216506350946110*d.fDes[2]-0.045753175473055*d.tDes[0]+0.170753175473055*d.tDes[1]+0.125*d.tDes[2];
	this->propData.fProp[4]=0.295753175473055*d.fDes[0]-0.079246824526945*d.fDes[1]+0.216506350946110*d.fDes[2]+0.045753175473055*d.tDes[0]-0.170753175473055*d.tDes[1]-0.125*d.tDes[2];
	this->propData.fProp[5]=-0.079246824526945*d.fDes[0]-0.295753175473055*d.fDes[1]-0.216506350946110*d.fDes[2]-0.170753175473055*d.tDes[0]-0.045753175473055*d.tDes[1]+0.125*d.tDes[2];
	this->propData.fProp[6]=0.079246824526945*d.fDes[0]+0.295753175473055*d.fDes[1]-0.216506350946110*d.fDes[2]+0.170753175473055*d.tDes[0]+0.045753175473055*d.tDes[1]+0.125*d.tDes[2];
	this->propData.fProp[7]=-0.295753175473055*d.fDes[0]+0.079246824526945*d.fDes[1]+0.216506350946110*d.fDes[2]-0.045753175473055*d.tDes[0]+0.170753175473055*d.tDes[1]-0.125*d.tDes[2];
}


