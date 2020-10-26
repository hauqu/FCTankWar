#pragma once
#include"baseStruct.h"
//游戏的基本类型 矩形物体

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
	//to do 建立构造函数
	Object(int x, int y, int w, int h,objectCate oc);
	bool collision(const Object& o)const;
	Object();
	int ID(void)const;
	//碰撞检测 碰撞返真
};

