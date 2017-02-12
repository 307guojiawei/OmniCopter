/*
 * Sensor.cpp
 *
 *  Created on: 2017年2月4日
 *      Author: jiawei
 */

#include "Omnicopter.h"

void Sensor::sensorInit()	//传感器初始化
{
	JY901.StartIIC();
}
void Sensor::getSensorData()	//获取传感器数据
{
	Sensor_Raw sensorData;
	JY901.GetGyro();
	JY901.GetAngle();
	JY901.GetQuater();
	sensorData.bodyAngle.roll=(double)JY901.stcAngle.Angle[0]/32768.0*180;
	sensorData.bodyAngle.pitch=(double)JY901.stcAngle.Angle[1]/32768.0*180;
	sensorData.bodyAngle.yaw=(double)JY901.stcAngle.Angle[2]/32768.0*180;
	sensorData.bodyRate.rollRate=(double)JY901.stcGyro.w[0]/32768.0*2000.0;
	sensorData.bodyRate.pitchRate=(double)JY901.stcGyro.w[1]/32768.0*2000.0;
	sensorData.bodyRate.yawRate=(double)JY901.stcGyro.w[2]/32768.0*2000.0;
	sensorData.bodyQuaternion.q[0]=(double)JY901.stcQuater.q0/32768.0;
	sensorData.bodyQuaternion.q[1]=(double)JY901.stcQuater.q1/32768.0;
	sensorData.bodyQuaternion.q[2]=(double)JY901.stcQuater.q2/32768.0;
	sensorData.bodyQuaternion.q[3]=(double)JY901.stcQuater.q3/32768.0;
	this->sensorRaw =sensorData;
}
void Sensor::getSensorRate()
{
	JY901.GetGyro();
	this->sensorRaw.bodyRate.rollRate=(double)JY901.stcGyro.w[0]/32768.0*2000.0;
	this->sensorRaw.bodyRate.pitchRate=(double)JY901.stcGyro.w[1]/32768.0*2000.0;
	this->sensorRaw.bodyRate.yawRate=(double)JY901.stcGyro.w[2]/32768.0*2000.0;

}
