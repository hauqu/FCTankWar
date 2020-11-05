#pragma once
#include"Map.h"
#include"IdCreater.h"
#include"cmdCreater.h"
#include"enemyTank.h"
#include"playerTank.h"
#include"bullet.h"
#include"constDate.h"
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
	
	playerTank p;//��ң�1
	GameControl();//���ж���Ĭ�ϵģ��޲�
	bool live;//�����Ƿ������
	
public:
	int run();//ÿ֡��Ϸ��Ҫ����ͻ��Ƽ���
	int start(int level);//������Ϸ��ʼ
	int getcmd(char c);//��ȡ�����ַ�
	
private:
	void initMap();//���Ƶ�ͼ��Ϣ����������id ��С
	void bullet_move(bullet &b);//ǿ���ƶ����������ײ
	int act_enemy(enemyTank& e);
	bool collision(Object* o1, Object* o2);
	cmd c_to_cmd(char c);
	int MaxEnemys;
private:
	void clearDieObject();//�����Ѿ�ʧЧ������

};