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
	list<bullet>enemybullets;//所有敌人子弹
	list<bullet>playerbullets;//所有玩家子弹
	playerTank p;//玩家，1个
	bool live;//玩家是否生存
	void die(Object*o);//死亡处理
public:
	bool run();//每帧游戏需要计算和绘制集合
	int getcmd(char c);//获取控制字符
	
};