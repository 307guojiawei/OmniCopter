/*
 * MathExtend.h
 *
 *  Created on: 2017��2��3��
 *      Author: jiawei
 *      description:�س���ѧ�⣬������Ԫ���Լ�ŷ���Ǽ������㷨��
 */

#include "OmniCopter.h"
#ifndef MATHEXTEND_H
#define MATHEXTEND_H

//��ѧ����
struct Angle	//�Ƕȶ���
{
	double roll;	//��ת
	double pitch;	//����
	double yaw;		//ƫ��
};
struct BodyRate	//���ٶȶ���
{
	double rollRate;	//��ת���ٶ�
	double pitchRate;	//�������ٶ�
	double yawRate;		//ƫ�����ٶ�
};

class Quaternion	//��Ԫ������
{
public:
	double q[4];
	Quaternion operator + (Quaternion &b)
	{
		Quaternion ans;
		ans.q[0]=this->q[0]+b.q[0];
		ans.q[1]=this->q[1]+b.q[1];
		ans.q[2]=this->q[2]+b.q[2];
		ans.q[3]=this->q[3]+b.q[3];
		return ans;
	}
	Quaternion operator - (Quaternion &b)
	{
		Quaternion ans;
		ans.q[0]=this->q[0]+b.q[0];
		ans.q[1]=this->q[1]+b.q[1];
		ans.q[2]=this->q[2]+b.q[2];
		ans.q[3]=this->q[3]+b.q[3];
		return ans;
	}
	Quaternion operator * (Quaternion &b)	//��Ԫ�����
	{
		Quaternion ans;
		ans.q[0]=this->q[0]*b.q[0]-(b.q[1]*this->q[1]+b.q[2]*this->q[2]+b.q[3]*this->q[3]);
		double a0=this->q[0];
		double b0=b.q[0];
		double ax=this->q[1];
		double ay=this->q[2];
		double az=this->q[3];
		double bx=b.q[1];
		double by=b.q[2];
		double bz=b.q[3];
		ans.q[1]=ay*bz-az*by+a0*bx+b0*ax;
		ans.q[2]=az*bx-ax*bz+a0*by+b0*ay;
		ans.q[3]=ax*by-ay*bx+a0*bz+b0*az;
		return ans;
	}
	Quaternion constantMutiply(double s);	//��Ԫ������
	Quaternion reverse();
	Quaternion createFromAngle(struct Angle angle);	//��ŷ���ǽ�����Ԫ��
};

#endif
