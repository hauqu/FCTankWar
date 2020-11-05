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

*/

int TANK_W = 32; int TANK_H = 32;
int BULLET_W = 16; int BULLET_H = 16;
int MAP_W = 10; int MAP_H = 10;
int MAPOBJECT_W = TANK_W;
int MAPOBJECT_H = TANK_H;
int WIN_W = TANK_W * MAP_W;
int WIN_H = TANK_H * MAP_H;
int TANK_STEP = TANK_H;//移动步长
int BULLET_STEP = BULLET_H;

int MAX_PLAYER_BULLET = 1;
class GameControl
{
public:
	Map mapDate;//地图加载器
	IdCreater idMaker;//id生成器，生成不重复的id
	cmdCreater cmdMaker;//指令生成器
	list<enemyTank>enemys;//所有敌人
	list<bullet>enemybullets;//所有敌人子弹
	list<bullet>playerbullets;//所有玩家子弹
	playerTank p;//玩家，1
	bool live;//场上是否有玩家
	int MaxEnemys;//最大敌人数量 低于则生成
public:
	GameControl();//所有都是默认的，无参
	~GameControl()
	{
	}
	
public:
	int run();//每帧游戏需要计算改变的量
	int start(int level);//控制游戏开始
	int getcmd(char c);//接受外部字符参数以控制p（玩家）
	
private:
	void initMap();//完善地图信息，包括分配id 大小
	void bullet_move(bullet &b);//强制移动，不检测碰撞
	int act_enemy(enemyTank& e);//执行 自身的cmd
	bool collision(Object* o1, Object* o2);//矩形碰撞检测
	cmd c_to_cmd(char c);//将字符转换为cmd
	void clearDieObject();//清理已经失效的物体
	bool CreatEnemy(enemyTank e);//在基地中生成一个敌人

};