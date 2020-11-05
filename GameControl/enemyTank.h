#pragma once
/*

每次从自身的命令队列读取一个命令并执行，
当队列为空，则从命令生成器中获取一组

*/
#include"Object.h"
using namespace std;
class enemyTank:public Object
{

public:
	int Hp;//血量
	int level;//等级
	int bulletId;//自己的子弹
	cmd dir;
	int attack;
	deque<cmd>action;//即将执行的行动
	enemyTank();
	~enemyTank()
	{

	}

};

