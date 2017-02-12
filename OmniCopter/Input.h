/*
 * Input.h
 *
 *  Created on: 2017��2��3��
 *      Author: jiawei
 *      description:�ɿشӽ��ջ����ֶ������ָ��
 *      	Input_Raw:����ӽ��ջ������ԭʼ����
 *      	Input_Converted:����ת�����Ŀ������ݣ���Ԫ����ʽ
 */
#include "OmniCopter.h"
#include "Sensor.h"
#ifndef INPUT_H
#define INPUT_H
//�ṹ�嶨��
struct Input_Raw	//���ջ������ԭʼ����
{
	int Roll_Max[3]={180,180,180};	//����ʱת�������Χ-Roll_Max��Roll_Max
	int Move_Max[3]={10,10,10};	//����ʱλ��ת�������Χ
	double Roll[3];
	double Move[3];
};

class Input_Converted	//ת�����Ľ��ջ����ݣ�Ϊ��Ԫ����ʽ
{
	public:

		double Move[3];
		//��̬�ǶȲ��ֵ�ת�����ӽǶ�ת��Ϊ��Ԫ��
		Quaternion Roll;
		Input_Converted getInputConverted(Input_Raw rawInput);//ע�⣬�˴�ֻת���Ƕȣ�ƽ��������Ҫ�����̬���
		Input_Converted getCompleteInput(Sensor_Raw sensorRaw);//��ýǶȺ�ƽ����ת���������ݣ�����������ƻ���
};



#endif
