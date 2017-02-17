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
 * 1	副翼
 * 2	升降
 * 3	油门
 * 4	方向
 * 5	aux1
 * 6	aux2
 * 7	安全锁
 */
//常量定义
//#define MEGA_2560	//目标单片机
#define DEBUG_MODE	//调试模式
#define DEBUG_SERIAL_RATE 115200

#define PPM_INT 0	//ppm閬ユ帶淇″彿杈撳叆,鏈€间负涓柇寮曡剼瀵瑰簲鐨勪腑鏂簭鍙?

#define PPM_SWITCH_PIN 2

#define PROP_1 3	//电机输出端口
#define PROP_2 4
#define PROP_3 5
#define PROP_4 6
#define PROP_5 7
#define PROP_6 8
#define PROP_7 9
#define PROP_8 10
#define PERCISION 1000	//浮点与整型转换精确度
#define RC_PERCISION 12	//rc读取值的浮动范围

//变量定义
#define RC_MIN 1008	//接收机输入的脉宽最低值
#define RC_MAX 2004	//接收机输入的脉宽最高值
#define ESC_MIN 1008	//电调输出的最低值
#define ESC_MAX 2004	//电调输出的最高值
#define ESC_MID ((ESC_MIN+ESC_MAX)>>1)	//电调输出的中点值
#define ESC_OFFSET_1 -30	//电调1中点值修正
#define ESC_OFFSET_2 -16	//电调1中点值修正
#define ESC_OFFSET_3 -16//电调1中点值修正
#define ESC_OFFSET_4 -30	//电调1中点值修正
#define ESC_OFFSET_5 -25	//电调1中点值修正
#define ESC_OFFSET_6 -16	//电调1中点值修正
#define ESC_OFFSET_7 -16	//电调1中点值修正
#define ESC_OFFSET_8 -30	//电调1中点值修正
#define ESC_START_POINT	20	//比电调中点值的绝对值大于多少时开始运动
#define DESIRE_CONDITION_F_MAX	19.0//设置输出给控制分配模型的力的最大值
#define DESIRE_CONDITION_TORQUE_MAX 15.0	//设置输出给控制分配模型的力矩的最大值
#define F_PORP_MIN -8		//运算输出的螺旋桨推力最小值
#define F_PROP_MAX 8		//运算输出的螺旋桨推力最大值


//控制参数定义
#define TATT 0.5		//出现在公式19中，外环时间常数，倒数看作p参数
#define	TRATE 7.0		//出现在公式21中，内环时间常数，倒数看作p参数
#define J 0.023433			//出现在公式21中，转动惯量
#define INNER_OUTER_RATIO 10	//控制环中内外环运算比
#define DESIRE_BODY_RATE_RATIO 15.0	//外环向内环输出的控制量的增益
#define DESIRE_CONDITION_FORCE_RATIO 2.0	//内环向控制分配输出的力的增益
#define DESIRE_CONDITION_TORQUE_RATIO 34.0	//内环向控制分配输出的力矩的增益
#define FEED_FORWARD_RATIO	1.0		//前馈增益




#endif /* LIBRARIES_OMNICOPTER_CONFIG_H_ */
