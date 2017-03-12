/*
 * Log.h
 *
 *  Created on: 2017年2月12日
 *      Author: jiawei
 */

#ifndef LIBRARIES_OMNICOPTER_LOG_H_
#define LIBRARIES_OMNICOPTER_LOG_H_
#include <OmniCopter.h>

class Log
{
public:
	void log(char* message,double value);	//控制台输出信息，包括键值对：信息和值（double型）
	void setDebugMode(bool mode);	//设置调试模式（true为开启调试模式)
	void setFreq(int freq);					//设置输出频率(隔多少次开始输出）
	void showRcInput(OmniCopter omniCopter);				//输出rcinput的值
	void showSensor(OmniCopter omniCopter);				//输出传感器的值
	void showEscOutput(OmniCopter omniCopter);			//输出控制电调的pwm脉宽
	void showForce(OmniCopter omniCopter);				//输出控制力和力矩
	void showFreq(OmniCopter omniCopter);				//输出外环控制频率
	void showPosition(OmniCopter omniCopter);
	void init();
	void oneLoop();					//记录一次循环的状态
private:
	bool debugEnable=false;
	bool showEnable=false;
	int showTime=0;
	int showF=10;
	unsigned long int lastTime=0;
};



#endif /* LIBRARIES_OMNICOPTER_LOG_H_ */
