/*
 * Sensor.h
 *
 *  Created on: 2017年2月4日
 *      Author: jiawei
 *      Description:JY901B姿态传感器的驱动以及姿态数据的输出。
 *      				占用串口1
 */
#include "OmniCopter.h"
#include "JY901.h"
#ifndef SENSOR_H
#define SENSOR_H

class Sensor_Raw
{
public:
	Quaternion bodyQuaternion;	//姿态四元数
	Angle bodyAngle;	//姿态角度
	BodyRate bodyRate;	//姿态角速度
	double height;		//高度
};

class Sensor
{
public:
	Sensor_Raw sensorRaw;
	CJY901 JY901;
	void getSensorData();	//获取传感器数据，需要驱动串口
	void getSensorRate();
	void sensorInit();		//传感器初始化，包括参数设定和串口的初始化
};


#endif /* SENSOR_H */
