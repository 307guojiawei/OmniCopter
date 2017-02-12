#include "OmniCopter.h"

Input_Converted Input_Converted::getInputConverted(Input_Raw rawInput)
{
	Input_Converted ans;
	Angle angle;
	Quaternion body;
	angle.roll=rawInput.Roll[0];
	angle.pitch=rawInput.Roll[1];
	angle.yaw=rawInput.Roll[2];
	body=body.createFromAngle(angle);
	ans.Roll=body;
	ans.Move[0]=rawInput.Move[0];
	ans.Move[1]=rawInput.Move[1];
	ans.Move[2]=rawInput.Move[2];
	return ans;
}

Input_Converted Input_Converted::getCompleteInput(Sensor_Raw sensorRaw)
{
	Input_Converted ans;
	ans.Roll=this->Roll;
	//平动的大地坐标->随体坐标转换
	double fx=this->Move[0];
	double fy=this->Move[1];
	double fz=this->Move[2];
	double q0=sensorRaw.bodyQuaternion.q[0];
	double q1=sensorRaw.bodyQuaternion.q[1];
	double q2=sensorRaw.bodyQuaternion.q[2];
	double q3=sensorRaw.bodyQuaternion.q[3];
	ans.Move[0]=(q0*q0+q1*q1-q2*q2-q3*q3)*fx+2*(q1*q2+q0*q3)*fy+2*(q1*q3-q0*q2)*fz;
	ans.Move[1]=2*(q1*q2-q0*q3)*fx+(q0*q0-q1*q1+q2*q2-q3*q3)*fy+2*(q2*q3+q0*q1)*fz;
	ans.Move[2]=2*(q1*q3+q0*q2)*fx+2*(q2*q3-q0*q1)*fy+(q0*q0-q1*q1-q2*q2+q3*q3)*fz;
	return ans;
}
