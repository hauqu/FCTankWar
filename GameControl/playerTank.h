#pragma once

#include"Object.h"
/*
tank �࣬�̳��� object����Ϊ enemyTank �� player�Ļ���

*/
class playerTank:public Object
{
public:
	int Hp;//Ѫ��
	int level;//�ȼ�
	int attack;
	int bulletId;//�Լ����ӵ�
	cmd dir;

};