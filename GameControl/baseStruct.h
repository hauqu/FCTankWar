#pragma once
//�ڴ˴��������б�Ҫ��ͷ�ļ�
#include<vector>
#include<ctime>
#include<string>
#include<list>
#include<fstream>
#include<deque>
enum class objectCate//����ļ�������
{
	playerTank=0, enemyTank, playerBullet,
	enemyBullet, space, wall,enemyBase,playerBase,
	falg,water,galss,strongWall
};
enum class cmd
{
	NA = 0,//��Ч
	Up, Right, Down, Left, Stop,//�ƶ� �� �� �� ��
	Attack,//����ָ��
	Explosion,//�Ա�
};
 const int baseCmdCateNumber = 8;//����ָ����������
enum class Aicmd
{
	random,
};//����ָ���Ѱ�ң�Χ�£��ɱ����Ϊ����ָ��