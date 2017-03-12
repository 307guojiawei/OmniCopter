/*
 * Config.h
 *
 *  Created on: 2017年2月10日
 *      Author: jiawei
 *      Description:保存各种调试参数
 */
#include <inttypes.h>
#include "Pozyx_definitions.h"
#include "Pozyx.h"
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
#define SERIALNUM	Serial	//串口对象
#define POS_FLITER_NUM 5
#define PPM_INT 1	//ppm閬ユ帶淇″彿杈撳叆,鏈€间负涓柇寮曡剼瀵瑰簲鐨勪腑鏂簭鍙?

#define PPM_SWITCH_PIN 3

#define PROP_1 4	//电机输出端口
#define PROP_2 5
#define PROP_3 6
#define PROP_4 7
#define PROP_5 8
#define PROP_6 9
#define PROP_7 10
#define PROP_8 11


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

//#define PERCISION 1000	//浮点与整型转换精确度
//#define RC_PERCISION 12	//rc读取值的浮动范围
//#define ESC_START_POINT	20	//比电调中点值的绝对值大于多少时开始运动
//#define DESIRE_CONDITION_F_MAX	19.0//设置输出给控制分配模型的力的最大值
//#define DESIRE_CONDITION_TORQUE_MAX 15.0	//设置输出给控制分配模型的力矩的最大值
//#define F_PORP_MIN -8		//运算输出的螺旋桨推力最小值
//#define F_PROP_MAX 8		//运算输出的螺旋桨推力最大值


//控制参数定义
//#define TATT 0.5		//出现在公式19中，外环时间常数，倒数看作p参数
//#define	TRATE 7.0		//出现在公式21中，内环时间常数，倒数看作p参数
//#define J 0.023433			//出现在公式21中，转动惯量
//#define INNER_OUTER_RATIO 10	//控制环中内外环运算比
//#define DESIRE_BODY_RATE_RATIO 15.0	//外环向内环输出的控制量的增益
//#define DESIRE_CONDITION_FORCE_RATIO 2.0	//内环向控制分配输出的力的增益
//#define DESIRE_CONDITION_TORQUE_RATIO 34.0	//内环向控制分配输出的力矩的增益
//#define FEED_FORWARD_RATIO	1.0		//前馈增益

static class Config
{
public:

	int PERCISION=100000;//浮点与整型转换精确度
	int RC_PERCISION= 12;//rc读取值的浮动范围
	int ESC_START_POINT=20;//比电调中点值的绝对值大于多少时开始运动
	double DESIRE_CONDITION_F_MAX=	30.0;//设置输出给控制分配模型的力的最大值
	double DESIRE_CONDITION_TORQUE_MAX= 15.0;//设置输出给控制分配模型的力矩的最大值
	double F_PROP_MIN= -8;		//运算输出的螺旋桨推力最小值
	double F_PROP_MAX= 8;		//运算输出的螺旋桨推力最大值
	double TATT= 1.0;		//出现在公式19中，外环时间常数，倒数看作p参数
	double TRATE= 0.25;		//出现在公式21中，内环时间常数，倒数看作p参数
	double J=0.023;			//出现在公式21中，转动惯量
	int INNER_OUTER_RATIO= 5;	//控制环中内外环运算比
	double DESIRE_BODY_RATE_RATIO= 1.0;	//外环向内环输出的控制量的增益
	double DESIRE_CONDITION_FORCE_RATIO= 1.0;	//内环向控制分配输出的力的增益
	double DESIRE_CONDITION_TORQUE_RATIO= 6.0;	//内环向控制分配输出的力矩的增益
	double FEED_FORWARD_RATIO=	1.0;		//前馈增益
	double P_KP = 0.3; //位置控制P参数
	double P_KI = 0.0; //位置控制I参数
	double P_KD = 0.0; //位置控制D参数
	double g_GRAVITY = 9.8;  //位置控制重力加速度
	double mess=1.4;

	double pos_x_init =0;  //起飞前的初始坐标位置
	double pos_y_init =0;
	double pos_z_init =0;

	/*parameters for Pozyx config*/
	uint16_t remote_id = 0x6000;                            // set this to the ID of the remote device
	bool remote = false;                                    // set this to true to use the remote ID
	boolean use_processing = false;                         // set this to true to output data for the processing sketch
	uint8_t num_anchors = 4;                                    // the number of anchors
	uint16_t anchors[4] = {0x6003, 0x6042, 0x603D, 0x607C};     // the network id of the anchors: change these to the network ids of your anchors.
/*	//Configure 3
	int32_t anchors_x[4] = {2860, -3080, 50, -160};               // anchor x-coorindates in mm
	int32_t anchors_y[4] = {-2020,-2020,1160,3780};                  // anchor y-coordinates in mm
	int32_t heights[4] = {1000, 1000, 2930, 1300};              // anchor z-coordinates in mm
	*/
	//Configure 2
	int32_t anchors_x[4] = {2860, -3080, 50, -240};               // anchor x-coorindates in mm
	int32_t anchors_y[4] = {-2020,-2020,1160,3780};                  // anchor y-coordinates in mm
	int32_t heights[4] = {1000, 1000, 2930, 570};              // anchor z-coordinates in mm

/* //configuration 1
	int32_t anchors_x[4] = {3740, -4060, 50, -240};               // anchor x-coorindates in mm
	int32_t anchors_y[4] = {-2020,-2020,1160,3780};                  // anchor y-coordinates in mm
	int32_t heights[4] = {1000, 1000, 2930, 570};              // anchor z-coordinates in mm
*/
	uint8_t algorithm = POZYX_POS_ALG_UWB_ONLY;             // positioning algorithm to use
	uint8_t dimension = POZYX_3D;                           // positioning dimension
	int32_t height = 1000;                                  // height of device, required in 2.5D positioning


	void setDesireBodyRateRatio(double desireBodyRateRatio = 15.0) {
		DESIRE_BODY_RATE_RATIO = desireBodyRateRatio;
	}

	void setDesireConditionFMax(double desireConditionFMax = 30.0) {
		DESIRE_CONDITION_F_MAX = desireConditionFMax;
		saveConfig();
	}

	void setDesireConditionForceRatio(double desireConditionForceRatio = 1.0) {
		DESIRE_CONDITION_FORCE_RATIO = desireConditionForceRatio;saveConfig();
	}

	void setDesireConditionTorqueMax(double desireConditionTorqueMax = 15.0) {
		DESIRE_CONDITION_TORQUE_MAX = desireConditionTorqueMax;saveConfig();
	}

	void setDesireConditionTorqueRatio(
			double desireConditionTorqueRatio = 34.0) {
		DESIRE_CONDITION_TORQUE_RATIO = desireConditionTorqueRatio;saveConfig();
	}

	void setEscStartPoint(int escStartPoint = 20) {
		ESC_START_POINT = escStartPoint;saveConfig();
	}

	void setPropMax(double propMax = 8) {
		F_PROP_MAX = propMax;saveConfig();
	}

	void setPropMin(double propMin = -8) {
		F_PROP_MIN = propMin;saveConfig();
	}

	void setFeedForwardRatio(double feedForwardRatio = 1.0) {
		FEED_FORWARD_RATIO = feedForwardRatio;saveConfig();
	}

	void setInnerOuterRatio(int innerOuterRatio = 10) {
		INNER_OUTER_RATIO = innerOuterRatio;saveConfig();
	}

	void setJ(double j = 0.023433) {
		J = j;saveConfig();
	}

	void setPercision(int percision = 1000) {
		PERCISION = percision;saveConfig();
	}

	void setRcPercision(int rcPercision = 12) {
		RC_PERCISION = rcPercision;saveConfig();
	}

	void setTatt(double tatt = 0.5) {
		TATT = tatt;saveConfig();
	}

	void setTrate(double trate = 7.0) {
		TRATE = trate;saveConfig();
	}

	void saveConfig();//保存参数到eeprom里
	void loadConfig();//从eeprom中加载参数
	void decode(unsigned char);	//接收解码
	void encode();	//发送编码
private:
	static const int percision=0;
	static const int rcPercicion=1;
	static const int escStartPoint=2;
	static const int desireConditionFMax=3;
	static const int desireConditionTorqueMax=4;
	static const int fPropMin=5;
	static const int fPropMax= 6;		//运算输出的螺旋桨推力最大值
	static const int tAtt= 7;		//出现在公式19中，外环时间常数，倒数看作p参数
	static const int tRate= 8;		//出现在公式21中，内环时间常数，倒数看作p参数
	static const int j=9;			//出现在公式21中，转动惯量
	static const int innerOuterRatio= 10;	//控制环中内外环运算比
	static const int desireBodyRateRatio= 11;	//外环向内环输出的控制量的增益
	static const int desireConditionForceRatio= 12;	//内环向控制分配输出的力的增益
	static const int desireConditionTorqueRatio= 13;	//内环向控制分配输出的力矩的增益
	static const int feedForwardRatio=14;		//前馈增益
	static const int eepromValid=50;	//eeprom数据有效位，50*4地址处为0x51，51*4地址处为0x15则有效
	bool dataValid();	//验证eeprom数据是否有效
	void setDataValid(bool status);//设置eeprom是否有效
	/*
	 * 说明：接收采用实际数值*1000表示，接收到数据后除以1000即为有效值！需要串口有效！！
	 * 通信时序：参数设置和传递：
	 * 				0x51	0x15	数据名称位byte	数据1byte	数据2byte
	 * 			获取所有参数：
	 * 				0x51	0x15	0x51			0x01		0x01
	 * 			获取参数：
	 * 				参数代号	“,”		参数名称			“,”			类型d/i			“,”			参数数值		";"
	 */
}config;


#endif /* LIBRARIES_OMNICOPTER_CONFIG_H_ */
