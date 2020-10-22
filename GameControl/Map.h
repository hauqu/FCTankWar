#pragma once

/*
包含地图信息，包括地图文件读取
检测碰撞时只需要检测物体附近的物体
以空间换时间，采用二维数组

*/
class Map
{
public:
	const int MaxW;//可用长度
	const int MaxH;//可用宽度
	//最大宽度
	const int startW = 1;//起始长度
	const int startH = 1;//起始宽度
	//可用范围 为行列数-1 用于简化边界处理
	Map(int w, int h);

};

/*





*/
