/*
 * FailSafe.h
 *
 *  Created on: 2017年2月13日
 *      Author: jiawei
 *      Description:本库作为TPS层的安全保护机制，监管OmniCopter的运行状况，并提供
 *      		带有阻塞的函数，可以利用这个功能强制关掉输出或者解锁机制
 */
#include <OmniCopter.h>
#ifndef LIBRARIES_OMNICOPTER_FAILSAFE_H_
#define LIBRARIES_OMNICOPTER_FAILSAFE_H_
class FailSafe
{
public:
	void safeToArm(OmniCopter o);				//安全检测函数

};




#endif /* LIBRARIES_OMNICOPTER_FAILSAFE_H_ */
