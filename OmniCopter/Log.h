/*
 * Log.h
 *
 *  Created on: 2017��2��12��
 *      Author: jiawei
 */

#ifndef LIBRARIES_OMNICOPTER_LOG_H_
#define LIBRARIES_OMNICOPTER_LOG_H_
#include <OmniCopter.h>

class Log
{
public:
	void log(char* message,double value);	//����̨�����Ϣ��������ֵ�ԣ���Ϣ��ֵ��double�ͣ�
	void setDebugMode(bool mode);	//���õ���ģʽ��trueΪ��������ģʽ)
	void setFreq(int freq);					//�������Ƶ��(�����ٴο�ʼ�����
	void showRcInput(OmniCopter omniCopter);				//���rcinput��ֵ
	void showSensor(OmniCopter omniCopter);				//�����������ֵ
	void showEscOutput(OmniCopter omniCopter);			//������Ƶ����pwm����
	void showForce(OmniCopter omniCopter);				//���������������
	void showFreq(OmniCopter omniCopter);				//����⻷����Ƶ��
	void init();
	void oneLoop();					//��¼һ��ѭ����״̬
private:
	bool debugEnable=true;
	bool showEnable=false;
	int showTime=0;
	int showF=10;
	unsigned long int lastTime=0;
};



#endif /* LIBRARIES_OMNICOPTER_LOG_H_ */
