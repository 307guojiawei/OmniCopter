/*
 * MathExtend.h
 *
 *  Created on: 2017年2月3日
 *      Author: jiawei
 *      description:拓充数学库，引入四元数以及欧拉角及其运算法则
 */

#include "OmniCopter.h"
#ifndef MATHEXTEND_H
#define MATHEXTEND_H

//数学定义
struct Angle	//角度定义(弧度制)
{
	double roll;	//滚转
	double pitch;	//俯仰
	double yaw;		//偏航
};
struct BodyRate	//角速度定义
{
	double rollRate;	//滚转角速度
	double pitchRate;	//俯仰角速度
	double yawRate;		//偏航角速度
};

class Quaternion	//四元数定义
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
		ans.q[0]=this->q[0]-b.q[0];
		ans.q[1]=this->q[1]-b.q[1];
		ans.q[2]=this->q[2]-b.q[2];
		ans.q[3]=this->q[3]-b.q[3];
		return ans;
	}
	Quaternion operator * (Quaternion &b)	//四元数相乘
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
	Quaternion constantMutiply(double s);	//四元数数乘
	Quaternion reverse();
	Quaternion createFromAngle(struct Angle angle);	//从欧拉角建立四元数
};

#endif
