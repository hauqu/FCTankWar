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