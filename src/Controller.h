/*
 * Controller.h
 *
 *  Created on: 2017年2月4日
 *      Author: jiawei
 *      Description:用于控制飞行器姿态以及位置
 */
#include "OmniCopter.h"
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <MathExtend.h>

class DesireCondition	//用于保存控制量（扭矩和力），用于传给控制分配模型
{
public:
	double fDes[3];	//0-2分别对应x,y,z
	double tDes[3];	//0-2分别对应roll,pitch,yaw
};
class PropData			//用于保存输出的螺旋桨动力数据
{
public:
	double fProp[8];	//对应八个电机输出动力值
};

class AttitudeController		//控制器，包括姿态角的外环控制,输出Ωdes给内环控制器
{
private:
	//BodyRate desireCondition;
public:
	BodyRate desireCondition;
	BodyRate getDesireBodyRate();
	void process(Input_Converted desireInput,Sensor_Raw sensorData, Angle angleErrorCollection);	//根据输入的指令和传感器姿态数据更新并控制DesireCondition中的数据

};

class BodyRateController	//角速度控制器，输入Ωdes，输出tdes给动力分配模型，内环控制器比外环循环次数更多
{
private:
	//DesireCondition desireTorque;
public:
	DesireCondition desireTorque;
	DesireCondition getDesireTorque();	//获得tdes，需要继续传入位置控制器完成位置控制操作
	void process(BodyRate desireBodyRate,Sensor_Raw sensorData);	//根据输入的角速度和传感器数据解算tdes
};

class PositionController		//位置控制器，通过指令和传感器数据将结果添加到传入的DesireCondition中后传入动力分配模型
{
private:
	//DesireCondition desireCondition;
public:
	DesireCondition desireCondition;
	DesireCondition getDesireCondition();
	void process(Input_Converted input,Sensor_Raw sensorData,DesireCondition desireInput,Sensor);
};

class ControlAllocator	//动力分配模型，用于将DesireCondition转换为PropData
{
private:
	PropData propData;
public:
	PropData getPropData();
	void process(DesireCondition desireCondition);	//根据输入的DesireCondition输出PropData
};




#endif /*CONTROLLER_H_ */
