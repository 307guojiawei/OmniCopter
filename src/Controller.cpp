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
	static Quaternion qLast;
	static bool isFirst=true;
	if(isFirst)
	{
		qLast=desireInput.Roll;
		isFirst=false;
	}

	Quaternion qErr=sensorData.bodyQuaternion.reverse()*desireInput.Roll;	//18
	BodyRate desireBodyRate,ff;	//19，ff为20
	/*
	Quaternion qX;
	qX.q[0]=0;
	qX.q[1]=sensorData.bodyRate.rollRate;
	qX.q[2]=sensorData.bodyRate.pitchRate;
	qX.q[3]=sensorData.bodyRate.yawRate;
	Quaternion qdot=desireInput.Roll.constantMutiply(0.5)*qX;*/
	Quaternion qdot=desireInput.Roll-qLast;
	Quaternion qBuff=qErr.constantMutiply(2);
	Quaternion qBuff2=desireInput.Roll.reverse();
	qBuff=qBuff*qBuff2;
	qBuff=qBuff*qdot;
	qBuff2=qErr.reverse();
	qBuff=qBuff*qBuff2;
	ff.rollRate=qBuff.q[1];
	ff.pitchRate=qBuff.q[2];
	ff.yawRate=qBuff.q[3];
	desireBodyRate.rollRate=(2/config.TATT)*(qErr.q[0]>0?1:-1)*qErr.q[1]+ff.rollRate*config.FEED_FORWARD_RATIO;
	desireBodyRate.pitchRate=(2/config.TATT)*(qErr.q[0]>0?1:-1)*qErr.q[2]+ff.pitchRate*config.FEED_FORWARD_RATIO;
	desireBodyRate.yawRate=(2/config.TATT)*(qErr.q[0]>0?1:-1)*qErr.q[3]+ff.yawRate*config.FEED_FORWARD_RATIO;

	desireBodyRate.rollRate*=config.DESIRE_BODY_RATE_RATIO;
	desireBodyRate.pitchRate*=config.DESIRE_BODY_RATE_RATIO;
	desireBodyRate.yawRate*=config.DESIRE_BODY_RATE_RATIO;
	this->desireCondition=desireBodyRate;
	qLast=desireInput.Roll;
}

DesireCondition BodyRateController::getDesireTorque()
{
	return this->desireTorque;
}

void BodyRateController::process(BodyRate desireBodyRate,Sensor_Raw sensorData)
{
	this->desireTorque.tDes[0]=(1/config.TRATE)*config.J*(desireBodyRate.rollRate-sensorData.bodyRate.rollRate);
	this->desireTorque.tDes[1]=(1/config.TRATE)*config.J*(desireBodyRate.pitchRate-sensorData.bodyRate.pitchRate);
	this->desireTorque.tDes[2]=(1/config.TRATE)*config.J*(desireBodyRate.yawRate-sensorData.bodyRate.yawRate);
	this->desireTorque.tDes[0]*=config.DESIRE_CONDITION_TORQUE_RATIO;
	this->desireTorque.tDes[1]*=config.DESIRE_CONDITION_TORQUE_RATIO;
	this->desireTorque.tDes[2]*=config.DESIRE_CONDITION_TORQUE_RATIO;
}

DesireCondition PositionController::getDesireCondition()
{
	return this->desireCondition;
}

void PositionController::process(Input_Converted input,Sensor_Raw sensorData,DesireCondition desireInput,Sensor sensor)
{
	this->desireCondition=desireInput;
	double q0=sensorData.bodyQuaternion.q[0];
	double q1=sensorData.bodyQuaternion.q[1];
	double q2=sensorData.bodyQuaternion.q[2];
	double q3=sensorData.bodyQuaternion.q[3];
	static double px_inte=0;
	static double py_inte=0;
	static double pz_inte=0;
	static double px_err_last=0;
	static double py_err_last=0;
	static double pz_err_last=0;
	double px_err=input.Move[0]-(sensorData.position.x-sensor.pos_init[0]);
	double py_err=input.Move[1]-(sensorData.position.y-sensor.pos_init[1]);
	double pz_err=input.Move[2]-(sensorData.position.z-sensor.pos_init[2]);

	double fx =config.mess*( config.P_KP*px_err + config.P_KI*px_inte + config.P_KD*(px_err-px_err_last) )/100.0;
	double fy =config.mess*( config.P_KP*py_err + config.P_KI*py_inte + config.P_KD*(py_err-py_err_last) )/100.0;

	//double fz =config.mess*( config.g_GRAVITY+(config.P_KP*pz_err + config.P_KI*pz_inte + config.P_KD*(pz_err-pz_err_last))/100.0);
	double fz =input.Move[2]*3/100.0;
	px_err_last=px_err;
	py_err_last=py_err;
	pz_err_last=pz_err;
	px_inte+=px_err;
	py_inte+=py_err;
	pz_inte+=pz_err;

	this->desireCondition.fDes[0]=(q0*q0+q1*q1-q2*q2-q3*q3)*fx+2*(q1*q2+q0*q3)*fy+2*(q1*q3-q0*q2)*fz;
	this->desireCondition.fDes[1]=2*(q1*q2-q0*q3)*fx+(q0*q0-q1*q1+q2*q2-q3*q3)*fy+2*(q2*q3+q0*q1)*fz;
	this->desireCondition.fDes[2]=2*(q1*q3+q0*q2)*fx+2*(q2*q3-q0*q1)*fy+(q0*q0-q1*q1-q2*q2+q3*q3)*fz;

	this->desireCondition.fDes[0]*=config.DESIRE_CONDITION_FORCE_RATIO;
	this->desireCondition.fDes[1]*=config.DESIRE_CONDITION_FORCE_RATIO;
	this->desireCondition.fDes[2]*=config.DESIRE_CONDITION_FORCE_RATIO;
}

PropData ControlAllocator::getPropData()
{
	return this->propData;
}

void ControlAllocator::process(DesireCondition d)
{

	for(int i=0;i<3;i++)
	{
		if(abs(d.fDes[i])>config.DESIRE_CONDITION_F_MAX)
		{
			d.fDes[i]=d.fDes[i]>0?config.DESIRE_CONDITION_F_MAX:-config.DESIRE_CONDITION_F_MAX;
		}
		if(abs(d.tDes[i])>config.DESIRE_CONDITION_TORQUE_MAX)
		{
			d.tDes[i]=d.tDes[i]>0?config.DESIRE_CONDITION_TORQUE_MAX:-config.DESIRE_CONDITION_TORQUE_MAX;
		}
	}


	this->propData.fProp[0]=-0.295753*d.fDes[0]+0.079246*d.fDes[1]+0.216506*d.fDes[2]+0.430689*d.tDes[0]-1.607354*d.tDes[1]+1.176664*d.tDes[2];
	this->propData.fProp[1]=0.079246*d.fDes[0]+0.29575317*d.fDes[1]-0.216506*d.fDes[2]-1.607354*d.tDes[0]-0.4306892*d.tDes[1]-1.176664*d.tDes[2];
	this->propData.fProp[2]=-0.079246*d.fDes[0]-0.295753*d.fDes[1]-0.216506*d.fDes[2]+1.607354*d.tDes[0]+0.430689*d.tDes[1]-1.176664*d.tDes[2];
	this->propData.fProp[3]=0.295753*d.fDes[0]-0.0792468*d.fDes[1]+0.216506*d.fDes[2]-0.430689*d.tDes[0]+1.607354*d.tDes[1]+1.176664*d.tDes[2];
	this->propData.fProp[4]=0.295753*d.fDes[0]-0.0792468*d.fDes[1]+0.216506*d.fDes[2]+0.430689*d.tDes[0]-1.607354*d.tDes[1]-1.176664*d.tDes[2];
	this->propData.fProp[5]=-0.079246*d.fDes[0]-0.2957531*d.fDes[1]-0.216506*d.fDes[2]-1.607354*d.tDes[0]-0.430689*d.tDes[1]+1.176664*d.tDes[2];
	this->propData.fProp[6]=0.079246*d.fDes[0]+0.2957531*d.fDes[1]-0.2165063*d.fDes[2]+1.607354*d.tDes[0]+0.430689*d.tDes[1]+1.176664*d.tDes[2];
	this->propData.fProp[7]=-0.295753*d.fDes[0]+0.0792468*d.fDes[1]+0.216506*d.fDes[2]-0.430689*d.tDes[0]+1.607354*d.tDes[1]-1.176664*d.tDes[2];
}
