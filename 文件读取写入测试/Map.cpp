#include "Map.h"
#include<Windows.h>
Map::Map(int level)
{
	string s =to_string(level) ;
	string fileName ="map_";
	fileName += s;
	fileName += ".txt";
	//ȷ���ļ����ƣ�����map_1.txt

	ifstream file(fileName,ios::in);//ֻ��
	if(file.fail())//��ʧ��
	{
		file.open("map_1.txt");
		cout << "��ʧ��" << endl;
	}
	int w = 10; int h = 10;
	string sw="";
	string sh = "";
	while (true)
	{
		char c = file.get();
		Sleep(500);
		cout << "1.��ȡ�ַ�����" << c << endl;
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
		cout << "2.��ȡ�ַ�����" << c << endl;
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

�ļ���ʽ
enum class objectCate//����ļ�������
{
	playerTank=0, enemyTank, playerBullet,
	enemyBullet, space, wall
};
0-9 
��ֵ�ͺ�����ù�ϵ
0 ��ʾ space
1 ��ʾ wall
2 ��ʾ��ҳ�����
3 ��ʾ��һ���
4 ��ʾ�з�̹�˳�����
5 ��
6 ˮ
7 ��ǽ
8  
9

̹���ӵ� �ȵȲ����ڵ�ͼ��Ϣ














*/