#pragma once
#include"Object.h"
#include"baseStruct.h"
using namespace std;
// 设计map 的date的数据结构
/*
包含地图信息，包括地图文件读取
检测碰撞时只需要检测物体附近的物体
以空间换时间，采用二维数组

*/
class Map
{
private:
	 int MaxW;
	 int MaxH;
	//最大宽度
	 
	
public:
	Map(string name);//从文件中加载必要信息
	Map();//从文件中加载必要信息
	vector<vector<Object>>data;
	bool loadMap(unsigned int level);//加载某一关卡地图
	objectCate c_to_objectCate(char c);
	list<Object>enemybases;//敌人出生点
	Object playerbase;//玩家基地
private:
	const string mapName;
	
};

/*





*/
