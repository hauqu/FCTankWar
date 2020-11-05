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

*/

int TANK_W = 32; int TANK_H = 32;
int BULLET_W = 16; int BULLET_H = 16;
int MAP_W = 10; int MAP_H = 10;
int MAPOBJECT_W = TANK_W;
int MAPOBJECT_H = TANK_H;
int WIN_W = TANK_W * MAP_W;
int WIN_H = TANK_H * MAP_H;
int TANK_STEP = TANK_H;//�ƶ�����
int BULLET_STEP = BULLET_H;

int MAX_PLAYER_BULLET = 1;
class GameControl
{
public:
	Map mapDate;//��ͼ������
	IdCreater idMaker;//id�����������ɲ��ظ���id
	cmdCreater cmdMaker;//ָ��������
	list<enemyTank>enemys;//���е���
	list<bullet>enemybullets;//���е����ӵ�
	list<bullet>playerbullets;//��������ӵ�
	playerTank p;//��ң�1
	bool live;//�����Ƿ������
	int MaxEnemys;//���������� ����������
public:
	GameControl();//���ж���Ĭ�ϵģ��޲�
	~GameControl()
	{
	}
	
public:
	int run();//ÿ֡��Ϸ��Ҫ����ı����
	int start(int level);//������Ϸ��ʼ
	int getcmd(char c);//�����ⲿ�ַ������Կ���p����ң�
	
private:
	void initMap();//���Ƶ�ͼ��Ϣ����������id ��С
	void bullet_move(bullet &b);//ǿ���ƶ����������ײ
	int act_enemy(enemyTank& e);//ִ�� �����cmd
	bool collision(Object* o1, Object* o2);//������ײ���
	cmd c_to_cmd(char c);//���ַ�ת��Ϊcmd
	void clearDieObject();//�����Ѿ�ʧЧ������
	bool CreatEnemy(enemyTank e);//�ڻ���������һ������

};