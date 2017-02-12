/*
 * Input.h
 *
 *  Created on: 2017年2月3日
 *      Author: jiawei
 *      description:飞控从接收机部分读入控制指令
 *      	Input_Raw:保存从接收机读入的原始数据
 *      	Input_Converted:保存转换过的控制数据，四元数格式
 */
#include "OmniCopter.h"
#include "Sensor.h"
#ifndef INPUT_H
#define INPUT_H
//结构体定义
struct Input_Raw	//接收机输入的原始数据
{
	int Roll_Max[3]={180,180,180};	//测量时转换的最大范围-Roll_Max至Roll_Max
	int Move_Max[3]={10,10,10};	//测量时位移转换的最大范围
	double Roll[3];
	double Move[3];
};

class Input_Converted	//转换过的接收机数据，为四元数格式
{
	public:

		double Move[3];
		//姿态角度部分的转换，从角度转换为四元数
		Quaternion Roll;
		Input_Converted getInputConverted(Input_Raw rawInput);//注意，此处只转换角度，平动数据需要结合姿态求解
		Input_Converted getCompleteInput(Sensor_Raw sensorRaw);//获得角度和平动都转换过的数据，可以送入控制环。
};



#endif
