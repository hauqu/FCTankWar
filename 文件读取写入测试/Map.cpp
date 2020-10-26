#include "Map.h"
#include<Windows.h>
Map::Map(int level)
{
	string s =to_string(level) ;
	string fileName ="map_";
	fileName += s;
	fileName += ".txt";
	//确定文件名称，例如map_1.txt

	ifstream file(fileName,ios::in);//只读
	if(file.fail())//打开失败
	{
		file.open("map_1.txt");
		cout << "打开失败" << endl;
	}
	int w = 10; int h = 10;
	string sw="";
	string sh = "";
	while (true)
	{
		char c = file.get();
		Sleep(500);
		cout << "1.读取字符串中" << c << endl;
		if (c=='\n')
		{
			break;
		}
		sw += c;

	}
	
	while (true)
	{
		
		char c = file.get();
		Sleep(500);
		cout << "2.读取字符串中" << c << endl;
		if (c == '\n')
		{
			break;
		}
		sh += c;

	}
	w = stoi(sw);
	h = stoi(sh);
	cout << w << endl << h << endl;
	data.resize(w);
	for (int i = 0; i < w; i++)
	{
		data[i].resize(h, 0);
	}
	
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data[i].size(); j++)
		{
			Sleep(100);
			char c = file.get();
			if (c == '\n')
			{
				j--;
				continue;
			}
				
			
			data[i][j] = c-'0';
			cout << " " << data[i][j] << " ";
		}cout << endl;
	}
	

	
	
}
/*

文件格式
enum class objectCate//物体的几种类型
{
	playerTank=0, enemyTank, playerBullet,
	enemyBullet, space, wall
};
0-9 
数值和含义对用关系
0 表示 space
1 表示 wall
2 表示玩家出生点
3 表示玩家基地
4 表示敌方坦克出生点
5 草
6 水
7 铁墙
8  
9

坦克子弹 等等不属于地图信息














*/