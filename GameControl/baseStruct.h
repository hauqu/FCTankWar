#pragma once
//在此处包含所有必要的头文件
#include<vector>//map 类 存储信息使用
#include<ctime>//随机数种子
#include<string>//map类文件处理
#include<list>//gameControl 管理 tank相关对象
#include<fstream>//map类文件处理
#include<deque>//存储指令序列

//声明一些常量
int TANK_W=32; int TANK_H = 32;
int BULLET_W = 16; int BULLET_H = 16;
int MAP_W=10; int MAP_H = 10;
int MAPOBJECT_W = TANK_W;
int MAPOBJECT_H = TANK_H;
int WIN_W = TANK_W * MAP_W;
int WIN_H = TANK_H * MAP_H;
//上述常量主要用于绘图参数
enum class objectCate//物体的几种类型
{
	playerTank=0, enemyTank, Bullet,
	space, wall,enemyBase,playerBase,
	falg,water,galss,strongWall
};//该类型能够被GameControl分类处理
enum class cmd//基础指令
{
	NA = 0,//无效
	Up, Right, Down, Left, Stop,//移动 上 右 下 左
	Attack,//攻击指令
	Explosion,//自爆
};//GameControl 会读取enemyTank的指令队列并执行相关操作

 const int baseCmdCateNumber = 8;//基础指令的种类个数
enum class Aicmd
{
	random,//随机
};//复杂指令，如寻找，围堵，可被拆分为基础指令
//具体的指令由指令生成器生成