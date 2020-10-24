#pragma once
#include"Map.h"
#include"IdCreater.h"
/*
该类包含所有可控制和访问的数据
作为数据总线，控制总线判定和操作

*/
class GameControl
{
public:
	Map mapDate;//地图信息
	IdCreater idCreater;//id生成器
	// palyerTank,bullet list
	//enemyTank,bullet list
	//碰撞检测处理
	//bullet 移动，检测毁灭
	
};