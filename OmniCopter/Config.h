/*
 * Config.h
 *
 *  Created on: 2017��2��10��
 *      Author: jiawei
 *      Description:������ֵ��Բ���
 */

#ifndef LIBRARIES_OMNICOPTER_CONFIG_H_
#define LIBRARIES_OMNICOPTER_CONFIG_H_
/*
 * RC���߶���
 * 1	����
 * 2	����
 * 3	����
 * 4	����
 * 5	aux1
 * 6	aux2
 */
//��������
//#define MEGA_2560	//Ŀ�굥Ƭ��
#define DEBUG_MODE	//����ģʽ

#define ROLL_X 2	//x����ת������
#define ROLL_Y 3	//y����ת������
#define ROLL_Z 4	//z����ת������
#define MOVE_X 5	//x��ƽ��������
#define MOVE_Y 6	//y��ƽ��������
#define MOVE_Z 7	//z��ƽ��������
#define PPM_IN 0	//ppmң���ź�����,��ֵΪ�ж����Ŷ�Ӧ���ж����
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
#define RC_MIN 1088	//���ջ�������������ֵ
#define RC_MAX 1888	//���ջ�������������ֵ
#define ESC_MIN 1088	//�����������ֵ
#define ESC_MAX 1888	//�����������ֵ
#define ESC_MID (ESC_MIN+ESC_MAX)/2	//���������е�ֵ
#define F_PORP_MIN -10		//���������Ť����Сֵ
#define F_PROP_MAX 10		//���������Ť�����ֵ

//���Ʋ�������
#define TATT 1		//�����ڹ�ʽ19�У��⻷ʱ�䳣������������p����
#define	TRATE 1		//�����ڹ�ʽ21�У��ڻ�ʱ�䳣������������p����
#define J 1			//�����ڹ�ʽ21�У�ת������
#define INNER_OUTER_RATIO 10	//���ƻ������⻷�����




#endif /* LIBRARIES_OMNICOPTER_CONFIG_H_ */
