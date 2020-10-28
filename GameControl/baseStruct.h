#pragma once
//在此处包含所有必要的头文件
#include<vector>
#include<ctime>
#include<string>
#include<list>
#include<fstream>
#include<deque>
enum class objectCate//物体的几种类型
{
	playerTank=0, enemyTank, playerBullet,
	enemyBullet, space, wall,enemyBase,playerBase,
	falg,water,galss,strongWall
};
enum class cmd
{
	NA = 0,//无效
	Up, Right, Down, Left, Stop,//移动 上 右 下 左
	Attack,//攻击指令
	Explosion,//自爆
};
 const int baseCmdCateNumber = 8;//基础指令的种类个数
enum class Aicmd
{
	random,
};//复杂指令，如寻找，围堵，可被拆分为基础指令