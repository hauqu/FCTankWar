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
private:
	 int MaxW;
	 int MaxH;
	//�����
	 
	
public:
	Map(string name);//���ļ��м��ر�Ҫ��Ϣ
	Map();//���ļ��м��ر�Ҫ��Ϣ
	vector<vector<Object>>data;
	bool loadMap(unsigned int level);//����ĳһ�ؿ���ͼ
	objectCate c_to_objectCate(char c);
	list<Object>enemybases;//���˳�����
	Object playerbase;//��һ���
private:
	const string mapName;
	
};

/*





*/
