/*
 * Controller.h
 *
 *  Created on: 2017��2��4��
 *      Author: jiawei
 *      Description:���ڿ��Ʒ�������̬�Լ�λ��
 */
#include "OmniCopter.h"
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <MathExtend.h>


class DesireCondition	//���ڱ����������Ť�غ����������ڴ������Ʒ���ģ��
{
public:
	double fDes[3];	//0-2�ֱ��Ӧx,y,z
	double tDes[3];	//0-2�ֱ��Ӧroll,pitch,yaw
};
class PropData			//���ڱ����������������������
{
public:
	double fProp[8];	//��Ӧ�˸�����������ֵ
};

class AttitudeController		//��������������̬�ǵ��⻷����,�����des���ڻ�������
{
private:
	BodyRate desireCondition;
public:
	BodyRate getDesireBodyRate();
	void process(Input_Converted desireInput,Sensor_Raw sensorData);	//���������ָ��ʹ�������̬���ݸ��²�����DesireCondition�е�����

};

class BodyRateController	//���ٶȿ����������릸des�����tdes����������ģ�ͣ��ڻ����������⻷ѭ����������
{
private:
	DesireCondition desireTorque;
public:
	DesireCondition getDesireTorque();	//���tdes����Ҫ��������λ�ÿ��������λ�ÿ��Ʋ���
	void process(BodyRate desireBodyRate,Sensor_Raw sensorData);	//��������Ľ��ٶȺʹ��������ݽ���tdes
};

class PositionController		//λ�ÿ�������ͨ��ָ��ʹ��������ݽ������ӵ������DesireCondition�к��붯������ģ��
{
private:
	DesireCondition desireCondition;
public:
	DesireCondition getDesireCondition();
	void process(Input_Converted input,Sensor_Raw sensorData,DesireCondition desireInput);
};
class ControlAllocator	//��������ģ�ͣ����ڽ�DesireConditionת��ΪPropData
{
private:
	PropData propData;
public:
	PropData getPropData();
	void process(DesireCondition desireCondition);	//���������DesireCondition���PropData
};




#endif /*CONTROLLER_H_ */
