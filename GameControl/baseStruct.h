#pragma once
//�ڴ˴��������б�Ҫ��ͷ�ļ�
#include<vector>
#include<ctime>
#include<string>
#include<list>
#include<fstream>
enum class objectCate//����ļ�������
{
	playerTank=0, enemyTank, playerBullet,
	enemyBullet, space, wall,EnemyBase,playerBase,
	falg,water,galss,StrongWall
};