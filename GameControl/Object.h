#pragma once

//游戏的基本类型 矩形物体
enum class objectCate//物体的几种类型
{
	playerTank, enemyTank, playerBullet,
	enemyBullet, space,wall
};
class Object
{
public:
	bool available;//可用
	objectCate cate;
	int id;//id 用于区分识别

	int x;//横坐标
	int y;//纵坐标
	int w;//宽度
	int h;//长度

	bool collision(const Object& o)const;
	int ID(void)const;
	//碰撞检测 碰撞返真
};

