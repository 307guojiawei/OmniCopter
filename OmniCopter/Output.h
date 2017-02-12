/*
 * Output.h
 *
 *  Created on: 2017年2月6日
 *      Author: jiawei
 *      Description:本库用于解析PropData并驱动电调完成相应操作
 */

#ifndef OUTPUT_H
#define OUTPUT_H
#include <Servo.h>

class EscDriver	//电调驱动类
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
	void escInit();			//电调初始化
	PropData getPropData();	//获取propData
	void setPropData(PropData propData);	//设置propData
	void excute();			//执行propData，驱动电调
	void excute(PropData propData);
};




#endif /* LIBRARIES_OMNICOPTER_OUTPUT_H_ */
