#pragma once
#include "Map.h"
//遍历该二维数组的时候 下标从start - Max
/*
//test 1
文件的格式与读取方法是相互绑定的
前两行为 行数，列数
然后跟二维数组 表示类型



*/
Map::Map(string name):mapName(name)
{
	MaxW = 0;
	MaxH = 0;
	playerbase = Object();
	
}

Map::Map():mapName("map_")
{
	MaxW = 0;
	MaxH = 0;
	playerbase = Object();
}


bool Map::loadMap(unsigned int level)
{

	string s = to_string(level);
	string fileName = mapName;
	fileName += s;
	fileName += ".txt";
	//确定文件名称，例如map_1.txt

	ifstream file(fileName, ios::in);//只读
	if (file.fail())//打开失败
	{
		file.open("map.txt");
	}
	
	string sw = "";
	string sh = "";
	while (true)
	{
		char c = file.get();

		if (c == '\n')
		{
			break;
		}
		sw += c;

	}

	while (true)
	{

		char c = file.get();
		
		if (c == '\n')
		{
			break;
		}
		sh += c;

	}
	MaxW = stoi(sw);
	MaxH= stoi(sh);
	
	data.resize(MaxW);
	for (int i = 0; i < MaxW; i++)
	{
		data[i].resize(MaxH);
	}

	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data[i].size(); j++)
		{
			
			char c = file.get();
			if (c == '\n')
			{
				j--;
				continue;
			}
			data[i][j].cate = c_to_objectCate(c);
			if (data[i][j].cate == objectCate::enemyBase)
				enemybases.push_back(Object(i,j,0,0,objectCate::enemyBase));
			if (data[i][j].cate == objectCate::playerBase)
				playerbase = Object(i, j, 0, 0, objectCate::playerBase);
			/*
			map 类只能决定自己的类型
			不能决定自己的大小，坐标 id 和是否可用
			具体的需要在GameControl实现
			详情见 其 initMap()方法
			*/
			
		}
	}


	return true;
}


inline objectCate Map::c_to_objectCate(char c)
{
	switch (c)
	{
	case '0':
		return objectCate::space;
	case '1':
		return objectCate::wall;
	case '2':
		return objectCate::strongWall;
	case '3':
		return objectCate::water;
	case '4':
		return objectCate::enemyBase;
	case '5':
		return objectCate::falg;
	case '6':
		return objectCate::galss;
	case '7':
		return objectCate::playerBase;
	case '8':
		return objectCate::space;

	default:
		return objectCate::space;
		break;
	}
}
