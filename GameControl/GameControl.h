#pragma once
#include"Map.h"
#include"IdCreater.h"
#include"cmdCreater.h"
#include"enemyTank.h"
#include"playerTank.h"
#include"bullet.h"
/*
该类包含所有可控制和访问的数据
作为数据总线，控制总线判定和操作

*/
class GameControl
{
public:
	Map mapDate;//地图加载器
	IdCreater idMaker;//id生成器
	cmdCreater cmdMaker;//指令生成器
	list<enemyTank>enemys;//所有敌人
	list<bullet>bullets;//所有子弹
	playerTank p;//玩家，1个
public:
	int getcmd(char c);//获取控制字符
	
};