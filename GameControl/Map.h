#pragma once
#include"Object.h"
#include"baseStruct.h"
using namespace std;
// ���map ��date�����ݽṹ
/*
������ͼ��Ϣ��������ͼ�ļ���ȡ
�����ײʱֻ��Ҫ������帽��������
�Կռ任ʱ�䣬���ö�ά����

*/
class Map
{

public:
	vector<vector<Object>>data;
	list<Object>enemybases;//���˳�����
	Object playerbase;//��һ���
public:
	Map(string name);//���ļ��м��ر�Ҫ��Ϣ
	Map();//���ļ��м��ر�Ҫ��Ϣ
	bool loadMap(unsigned int level);//����ĳһ�ؿ���ͼ
	~Map() {}
private:
	objectCate c_to_objectCate(char c);
	
private:
	int MaxW;
	int MaxH;
	//�����
	const string mapName;
	
};

/*





*/
