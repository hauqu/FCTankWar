#pragma once
//�ڴ˴��������б�Ҫ��ͷ�ļ�
#include<vector>//map �� �洢��Ϣʹ��
#include<ctime>//���������
#include<string>//map���ļ�����
#include<list>//gameControl ���� tank��ض���
#include<fstream>//map���ļ�����
#include<deque>//�洢ָ������

//����һЩ����(��һ��)
int TANK_W=32; int TANK_H = 32;
int BULLET_W = 16; int BULLET_H = 16;
int MAP_W=10; int MAP_H = 10;
int MAPOBJECT_W = TANK_W;
int MAPOBJECT_H = TANK_H;
int WIN_W = TANK_W * MAP_W;
int WIN_H = TANK_H * MAP_H;
int TANK_STEP = TANK_H;//�ƶ�����
int BULLET_STEP = BULLET_H;

int MAX_PLAYER_BULLET=1;
//�������ܷ�����ڵ������ﵽ���޷�ִ��attack

//����������Ҫ���ڻ�ͼ����
enum class objectCate//����ļ�������
{
	playerTank=0, enemyTank, Bullet,
	space, wall,enemyBase,playerBase,
	falg,water,galss,strongWall
};//�������ܹ���GameControl���ദ��
enum class cmd//����ָ��
{
	NA = 0,//��Ч
	Up, Right, Down, Left, Stop,//�ƶ� �� �� �� ��
	Attack,//����ָ��
	Explosion,//�Ա�
};//GameControl ���ȡenemyTank��ָ����в�ִ����ز���

 const int baseCmdCateNumber = 8;//����ָ����������
enum class Aicmd
{
	random,//���
};//����ָ���Ѱ�ң�Χ�£��ɱ����Ϊ����ָ��
//�����ָ����ָ������������