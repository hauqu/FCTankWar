#pragma once
#include"Map.h"
#include"IdCreater.h"
#include"cmdCreater.h"
#include"enemyTank.h"
#include"playerTank.h"
#include"bullet.h"
/*
����������пɿ��ƺͷ��ʵ�����
��Ϊ�������ߣ����������ж��Ͳ���

*/
class GameControl
{
public:
	Map mapDate;//��ͼ������
	IdCreater idMaker;//id������
	cmdCreater cmdMaker;//ָ��������
	list<enemyTank>enemys;//���е���
	list<bullet>bullets;//�����ӵ�
	playerTank p;//��ң�1��
public:
	int getcmd(char c);//��ȡ�����ַ�
	
};