/*
 * OmniCopter.h
 *
 *  Created on: 2017��2��3��
 *      Author: jiawei
 *      description:��Ϊ��Ŀ��ͨ��ͷ�ļ��������˷ɿ�����ĳ��������Լ������Ľṹ��
 *
 *      OmniCopter�ɿ�ϵͳ�������ģ�ͣ�
 *      	-------------------------------------
 *      		Ӧ�ò㣨Apps)��OmniCopter.ino
 *      			����API�����ɿ�Ӧ��
 *      	-------------------------------------
 *      		������㣨TPS����OmniCopter.h��Log.h
 *      			������ȷ��ʼ���ʹ��������������
 *      			�ɿع���ģ��Ĵ��������ṩAPI�ӿ�
 *      			��Ӧ��
 *      	-------------------------------------
 *      		���ݴ���㣨DPS���������ļ�
 *      			����ײ�Ӳ����ʼ�������ݲɼ����˲���
 *      			���ƺ��������漰���ײ���������İ�
 *      			��Sensor,Input��Output
 *
 *      OmniCopter�ɿ�ϵͳ�˿�ռ�������
 *      	ͨ�Ŷ˿ڣ�
 *      		Serial0:���Ժ�����λ��ͨ��
 *      		SCL��SDA:��Ӧ�ߵ�ϵͳ����
 *      	��������:
 *      		6��pwm����ͨ�����ֱ��Ӧƽ����ת������
 *      	���������
 *      		8��pwm���ͨ�����ֱ��Ӧ�˸����pwm���
 */

#ifndef OMNICOPTER_H
#define OMNICOPTER_H

#include <arduino.h>	//Arduino����
#include "Config.h"		//����������
#include "MathExtend.h"	//��ѧ�࣬������Ԫ������
#include "Input.h"		//ң�������ջ�������
#include "Sensor.h"		//������������
#include "Controller.h"	//��������
#include "Output.h"		//���������



//�����������
class OmniCopter
{
	public:
		Input_Converted convertedInput;
		Input_Raw input;
		Sensor sensor;
		int* RC;

		BodyRate desiredBodyRate;
		DesireCondition desiredCondition;
		PropData propData;

		AttitudeController attitudeController;
		BodyRateController bodyRateController;
		PositionController positionController;
		ControlAllocator controlAllocator;
		EscDriver	escDriver;

		void init();		//��ʼ�����ջ�����Ķ˿�
		void getCompleteInput();		//����������������ݣ�ƽ������̬��ת����),������̬���ݣ�ʵ�ʵ�����ֻ����ô˺���
		void getRcValue(int*);
		void getRawSensorInput();		//��ô����������ԭʼ����
		void attitudeProcess();			//�Ƕ��⻷����
		void bodyRateProcess();			//�������ڻ�����
		void positionProcess();			//λ�ÿ���
		void controlAllocateProcess();	//��������
		void excute();					//ִ�е������
	private:
		void getRawInput(Input_Raw* input,int* RC1);	//��ý��ջ�����ĳ�ʼ����
		void getRcInput(int* RC1);		//���ת������Ԫ���Ľ��ջ���������
};


#endif


