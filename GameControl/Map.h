#pragma once
#include"Object.h"
#include"baseStruct.h"
using namespace std;
//to do ���map ��date�����ݽṹ
/*
������ͼ��Ϣ��������ͼ�ļ���ȡ
�����ײʱֻ��Ҫ������帽��������
�Կռ任ʱ�䣬���ö�ά����

*/
class Map
{
private:
	 int MaxW;//���ó���
	 int MaxH;//���ÿ��
	//�����
	 const int startW = 1;//��ʼ����
	 const int startH = 1;//��ʼ���
	//���÷�Χ Ϊ������-1 ���ڼ򻯱߽紦��
	
public:
	Map(int level);//���ļ��м��ر�Ҫ��Ϣ
	vector<vector<Object>>data;
	
};

/*





*/
