#pragma once
/*

定义子弹类

*/
#include"Object.h"
/*
在接受到一个attack指令后，
gameControl 会生成一个子弹对象
并且添加到list表中
tank无法通过自己找到自己发射的子弹
只能通过id进行索引，发射后，tank无权操作，访问
读取attack 的cmd发生在gameControl中，
所以子弹的实例化也应该在此，

*/

class bullet:public Object
{
public:
	int attack;//攻击力
	cmd dir;//子弹行进方向
	int TankId;//坦克的id
	bullet();//仅仅声明一个子弹类
	bullet(Object*o,cmd d,int a);
	//根据坐标，指向，攻击力生成

	
};