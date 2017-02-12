/*
 * Config.h
 *
 *  Created on: 2017年2月10日
 *      Author: jiawei
 *      Description:保存各种调试参数
 */

#ifndef LIBRARIES_OMNICOPTER_CONFIG_H_
#define LIBRARIES_OMNICOPTER_CONFIG_H_
/*
 * RC接线定义
 * 1	升降
 * 2	副翼
 * 3	油门
 * 4	方向
 * 5	aux1
 * 6	aux2
 */
//常量定义
//#define MEGA_2560	//目标单片机
#define DEBUG_MODE	//调试模式

#define ROLL_X 2	//x轴旋转输入量
#define ROLL_Y 3	//y轴旋转输入量
#define ROLL_Z 4	//z轴旋转输入量
#define MOVE_X 5	//x轴平动输入量
#define MOVE_Y 6	//y轴平动输入量
#define MOVE_Z 7	//z轴平动输入量
#define PPM_IN 0	//ppm遥控信号输入,本值为中断引脚对应的中断序号
#define PROP_1 10	//电机输出端口
#define PROP_2 11
#define PROP_3 12
#define PROP_4 13
#define PROP_5 14
#define PROP_6 15
#define PROP_7 16
#define PROP_8 17
#define PERCISION 1000	//浮点与整型转换精确度

//变量定义
#define RC_MIN 1088	//接收机输入的脉宽最低值
#define RC_MAX 1888	//接收机输入的脉宽最高值
#define ESC_MIN 1088	//电调输出的最低值
#define ESC_MAX 1888	//电调输出的最高值
#define ESC_MID (ESC_MIN+ESC_MAX)/2	//电调输出的中点值
#define F_PORP_MIN -10		//运算输出的扭矩最小值
#define F_PROP_MAX 10		//运算输出的扭矩最大值

//控制参数定义
#define TATT 1		//出现在公式19中，外环时间常数，倒数看作p参数
#define	TRATE 1		//出现在公式21中，内环时间常数，倒数看作p参数
#define J 1			//出现在公式21中，转动惯量
#define INNER_OUTER_RATIO 10	//控制环中内外环运算比




#endif /* LIBRARIES_OMNICOPTER_CONFIG_H_ */
