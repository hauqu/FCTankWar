#pragma once
//在此处包含所有必要的头文件
#include<vector>
#include<ctime>
#include<string>
#include<list>
#include<fstream>
enum class objectCate//物体的几种类型
{
	playerTank=0, enemyTank, playerBullet,
	enemyBullet, space, wall,EnemyBase,playerBase,
	falg,water,galss,StrongWall
};