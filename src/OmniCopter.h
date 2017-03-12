/*
 * OmniCopter.h
 *
 *  Created on: 2017年2月3日
 *      Author: jiawei
 *      description:作为项目的通用头文件，定义了飞控所需的常量变量以及基本的结构体
 *
 *      OmniCopter飞控系统三层控制模型：
 *      	-------------------------------------
 *      		应用层（Apps)：OmniCopter.ino
 *      			利用API构件飞控应用
 *      	-------------------------------------
 *      		事务处理层（TPS）：OmniCopter.h和Log.h
 *      			负责正确初始化和处理各种组件，完成
 *      			飞控功能模块的处理事务，提供API接口
 *      			给应用
 *      	-------------------------------------
 *      		数据处理层（DPS）：其余文件
 *      			负责底层硬件初始化，数据采集、滤波、
 *      			控制和驱动，涉及到底层输入输出的包
 *      			括Sensor,Input和Output
 *
 *      OmniCopter飞控系统端口占用情况：
 *      	通信端口：
 *      		Serial0:调试和与上位机通信
 *      		SCL和SDA:响应惯导系统数据
 *      	数字输入:
 *      		6个pwm输入通道，分别对应平动和转动三轴
 *      	数字输出：
 *      		8个pwm输出通道，分别对应八个电机pwm输出
 */

#ifndef OMNICOPTER_H
#define OMNICOPTER_H

#include <arduino.h>	//Arduino驱动
#include "Config.h"		//参数保存类
#include "MathExtend.h"	//数学类，包括四元数运算
#include "Input.h"		//遥控器接收机输入类
#include "Sensor.h"		//传感器输入类
#include "Controller.h"	//控制器类
#include "Output.h"		//电调驱动类



//事务处理层主类
class OmniCopter
{
	public:
		Input_Converted convertedInput;
		Input_Raw input;
    Input_Raw rawInput;
		Sensor sensor;
		int* RC;

		BodyRate desiredBodyRate;
    Angle angleErrorCollection, nowAngle, lastAngle;
		DesireCondition desiredCondition;
		PropData propData;

		AttitudeController attitudeController;
		BodyRateController bodyRateController;
		PositionController positionController;
		ControlAllocator controlAllocator;
		EscDriver	escDriver;

		void init();		//初始化接收机输入的端口
		void getCompleteInput(int*);		//获得完整的输入数据（平动和姿态均转换过),包括姿态数据，实际调用中只需调用此函数

		void getRawSensorInput();		//获得传感器输出的原始数据
		void attitudeProcess();			//角度外环控制
		void bodyRateProcess();			//角速率内环控制
		void positionProcess();			//位置控制
		void controlAllocateProcess();	//动力分配
		void excute();					//执行电调驱动
	private:
		void getRawInput(Input_Raw* input,int* RC1);	//获得接收机输入的初始数据
		void getRcInput(int* RC1);		//获得转换成四元数的接收机输入数据
		void getRcValue(int*);

    void getAngle(Angle angle);
    void collectAngleError();
    void cleanAngleErrorcollection();
};


#endif
