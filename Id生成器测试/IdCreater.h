#pragma once
#include<list>
#include<ctime>
using namespace std;
enum class objectCate//物体的几种类型
{
	playerTank = 0, enemyTank, playerBullet,
	enemyBullet, space, wall
};
class IdCreater
{
public:
	list<int>data;
	IdCreater(int nc);
	int out();
private:
	bool able(int id);
	int numberCate;
};