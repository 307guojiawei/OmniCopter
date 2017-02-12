/*
 * Config.h
 *
 *  Created on: 2017��2��10��
 *      Author: jiawei
 *      Description:������ֵ��Բ���
 */

#ifndef LIBRARIES_OMNICOPTER_CONFIG_H_
#define LIBRARIES_OMNICOPTER_CONFIG_H_

//��������
//#define MEGA_2560	//Ŀ�굥Ƭ��
#define DEBUG_MODE	//����ģʽ

#define ROLL_X 2	//x����ת������
#define ROLL_Y 3	//y����ת������
#define ROLL_Z 4	//z����ת������
#define MOVE_X 5	//x��ƽ��������
#define MOVE_Y 6	//y��ƽ��������
#define MOVE_Z 7	//z��ƽ��������
#define PROP_1 10	//�������˿�
#define PROP_2 11
#define PROP_3 12
#define PROP_4 13
#define PROP_5 14
#define PROP_6 15
#define PROP_7 16
#define PROP_8 17
#define PERCISION 1000	//����������ת����ȷ��

//��������
#define RC_MIN 1010	//���ջ�������������ֵ
#define RC_MAX 2007	//���ջ�������������ֵ
#define ESC_MIN 1100	//�����������ֵ
#define ESC_MAX 1900	//�����������ֵ
#define ESC_MID (ESC_MIN+ESC_MAX)/2	//���������е�ֵ
#define F_PORP_MIN -10		//���������Ť����Сֵ
#define F_PROP_MAX 10		//���������Ť�����ֵ

//���Ʋ�������
#define TATT 1		//�����ڹ�ʽ19�У��⻷ʱ�䳣������������p����
#define	TRATE 1		//�����ڹ�ʽ21�У��ڻ�ʱ�䳣������������p����
#define J 1			//�����ڹ�ʽ21�У�ת������
#define INNER_OUTER_RATIO 10	//���ƻ������⻷�����




#endif /* LIBRARIES_OMNICOPTER_CONFIG_H_ */
