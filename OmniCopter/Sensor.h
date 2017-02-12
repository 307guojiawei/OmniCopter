/*
 * Sensor.h
 *
 *  Created on: 2017��2��4��
 *      Author: jiawei
 *      Description:JY901B��̬�������������Լ���̬���ݵ������
 *      				ռ�ô���1
 */
#include "OmniCopter.h"
#include "JY901.h"
#ifndef SENSOR_H
#define SENSOR_H

class Sensor_Raw
{
public:
	Quaternion bodyQuaternion;	//��̬��Ԫ��
	Angle bodyAngle;	//��̬�Ƕ�
	BodyRate bodyRate;	//��̬���ٶ�
	double height;		//�߶�
};

class Sensor
{
public:
	Sensor_Raw sensorRaw;
	CJY901 JY901;
	void getSensorData();	//��ȡ���������ݣ���Ҫ��������
	void getSensorRate();
	void sensorInit();		//��������ʼ�������������趨�ʹ��ڵĳ�ʼ��
};


#endif /* SENSOR_H */
