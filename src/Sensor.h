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
#include "Pozyx.h"
#include "Pozyx_definitions.h"

#ifndef SENSOR_H
#define SENSOR_H

class Sensor_Raw
{
public:
	Quaternion bodyQuaternion;	//姿态四元数
	Angle bodyAngle;	//姿态角度
	BodyRate bodyRate;	//姿态角速度
	double height;		//高度
	coordinates_t position;
};

class Sensor
{
public:
	Sensor_Raw sensorRaw;
	CJY901 JY901;
	bool calledPositioning=0;
	int positionupdate=0;
	void getSensorData();	//获取传感器数据，需要驱动串口
	void getSensorRate();
	int callPositioning();  //开始Positioning
	int readPositioning(coordinates_t *position);  //读取Positioning数据
	int getPosition(); //获取Pozyx位置数据
	void sensorInit();		//传感器初始化，包括参数设定和串口的初始化
};

void setAnchorsManual();

#endif /* SENSOR_H */
