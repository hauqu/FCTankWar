#pragma once
#include"Object.h"
#include"baseStruct.h"
using namespace std;
//to do 设计map 的date的数据结构
/*
包含地图信息，包括地图文件读取
检测碰撞时只需要检测物体附近的物体
以空间换时间，采用二维数组

*/
class Map
{
private:
	 int MaxW;//可用长度
	 int MaxH;//可用宽度
	//最大宽度
	 const int startW = 1;//起始长度
	 const int startH = 1;//起始宽度
	//可用范围 为行列数-1 用于简化边界处理
	
public:
	Map(int level);//从文件中加载必要信息
	vector<vector<Object>>data;
	
};

/*





*/
