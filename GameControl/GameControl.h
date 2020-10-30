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


�ؼ������ں��ʵ��¼������ײ
�����ӵ���˵����ִ���ƶ�����ټ����̹�ˣ���ͼ����ײ
����̹����˵��ֻ��Ҫ���Ե�ͼ����ײ

����
Ӧ�����µ�ִ��˳��
1.����p bullet ִ��move
2.����e bullet ִ��move
3.���bullet ��Tank��ײ
������
4.���bullet ��map��ײ������








*/
class GameControl
{
public:
	Map mapDate;//��ͼ������
	IdCreater idMaker;//id������
	cmdCreater cmdMaker;//ָ��������
	list<enemyTank>enemys;//���е���
	list<bullet>enemybullets;//���е����ӵ�
	list<bullet>playerbullets;//��������ӵ�
	playerTank p;//��ң�1��
	bool live;//����Ƿ�����
	void die(Object*o);//��������
public:
	int run();//ÿ֡��Ϸ��Ҫ����ͻ��Ƽ���
	int getcmd(char c);//��ȡ�����ַ�
private:
	void initMap();//���Ƶ�ͼ��Ϣ����������id ��С
private:
	void bullet_move(Object*o,cmd d);//�ƶ�һ������
	void enemy_act(enemyTank& t);
	void enemy_move(enemyTank& t);
	void clearDieObject();//�����Ѿ�ʧЧ������
};