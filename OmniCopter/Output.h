/*
 * Output.h
 *
 *  Created on: 2017��2��6��
 *      Author: jiawei
 *      Description:�������ڽ���PropData��������������Ӧ����
 */

#ifndef OUTPUT_H
#define OUTPUT_H
#include <Servo.h>

class EscDriver	//���������
{
private:
	PropData propData;
	Servo prop1;
	Servo prop2;
	Servo prop3;
	Servo prop4;
	Servo prop5;
	Servo prop6;
	Servo prop7;
	Servo prop8;
public:
	void escInit();			//�����ʼ��
	PropData getPropData();	//��ȡpropData
	void setPropData(PropData propData);	//����propData
	void excute();			//ִ��propData���������
	void excute(PropData propData);
};




#endif /* LIBRARIES_OMNICOPTER_OUTPUT_H_ */
