#pragma once
#include "Map.h"
//�����ö�ά�����ʱ�� �±��start - Max
/*
//test 1
�ļ��ĸ�ʽ���ȡ�������໥�󶨵�
ǰ����Ϊ ����������
Ȼ�����ά���� ��ʾ����



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
	//ȷ���ļ����ƣ�����map_1.txt

	ifstream file(fileName, ios::in);//ֻ��
	if (file.fail())//��ʧ��
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
			map ��ֻ�ܾ����Լ�������
			���ܾ����Լ��Ĵ�С������ id ���Ƿ����
			�������Ҫ��GameControlʵ��
			����� �� initMap()����
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
