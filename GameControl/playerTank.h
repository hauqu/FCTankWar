#pragma once

#include"Object.h"
/*
tank 类，继承自 object，作为 enemyTank 和 player的基类

*/
class playerTank:public Object
{
public:
	int Hp;//血量
	int level;//等级
	int attack;
	int bulletId;//自己的子弹
	cmd dir;

};