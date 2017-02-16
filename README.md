<<<<<<< HEAD
# OmniCopter Project
## 项目简介
本项目为全向无人机的飞控系统，基于Arduino系列单片机和JY901惯导模块实现六轴姿态与位置稳定。
## 项目索引#
>### 应用层(APP)
 * OmniCopter.ino 项目应用主文件，利用API构件飞控应用

>### 事务处理层(TPS)##
=======
# OmniCopter Project #
#项目简介
本项目为全向无人机的飞控系统，基于Arduino系列单片机和JY901惯导模块实现六轴姿态与位置稳定。
#项目索引#
>##应用层(APP)##
 * OmniCopter.ino 项目应用主文件，利用API构件飞控应用

>##事务处理层(TPS)##
>>>>>>> aedb60c5f835e5907086ffe80714d89d7df2275f
 * OmniCopter.h负责正确初始化和处理各种组件，完成飞控功能模块的处理事务，提供API接口给应用
 * Log.h 作为调试辅助类，输出各种调试参数，可以统一全部关闭输出，设置输出频率等。
 * FailSafe.h 安全机制，提供一个阻塞函数，检测是否失控以及遥控通道7是否解锁
 
<<<<<<< HEAD
>### 数据处理层(DPS)##
=======
>##数据处理层(DPS)##
>>>>>>> aedb60c5f835e5907086ffe80714d89d7df2275f
 * Input.h 遥控器接收机信号输入，保存输入的控制指令  
 * Output.h 电调驱动，解析八个螺旋桨指令并输出PWM波  
 * Sensor.h 初始化并驱动JY901模块读取姿态数据，转换数据格式 
  * JY901.h JY901惯导平台驱动   
 * Controller.h 飞控核心算法部分，包括AttitudeController，BodyRateController，PositionController和ControlAllocator

<<<<<<< HEAD
>### 配置以及数学扩展库##
=======
>##配置以及数学扩展库##
>>>>>>> aedb60c5f835e5907086ffe80714d89d7df2275f
* Config.h   保存飞控各种状态参数  
* MathExtend.h  拓展数学结构体，包括四元数相关运算，姿态角和姿态角速度等
