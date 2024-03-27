# 自动和手动遥控光跟踪器的多任务实现

## 问题

步进电机步进方式运行时，接受到一个转动角度（步长）的命令后，在其执行需要时间，不能接受红外遥控命令，在运动中停止

以下2个任务，必须是独立的，同时，能够进行信息通讯：步进电机转动时，能够接受红外命令停止
* 接受红外
* 步进电机转动

## 测试方案

* freeRTOS
* https://github.com/arkhipenko/TaskScheduler

##  代码

* `Lab_Simple_Dual_Axie_Light_Tracking_freeRTOS.ino`

其中：

* 电机转动不使用库，使用直接控制电机运行的代码 