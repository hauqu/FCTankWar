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


关键在于在合适的事件检测碰撞
对于子弹来说，先执行移动命令，再检测与坦克，地图的碰撞
对于坦克来说，只需要检测对地图的碰撞

所以
应有如下的执行顺序
1.访问p bullet 执行move
2.访问e bullet 执行move
3.检测bullet 与Tank碰撞
并处理
4.检测bullet 与map碰撞并处理








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
	int run();//每帧游戏需要计算和绘制集合
	int getcmd(char c);//获取控制字符
private:
	void initMap();//完善地图信息，包括分配id 大小
private:
	void bullet_move(Object*o,cmd d);//移动一个对象
	void enemy_act(enemyTank& t);
	void enemy_move(enemyTank& t);
	void clearDieObject();//清理已经失效的物体
};