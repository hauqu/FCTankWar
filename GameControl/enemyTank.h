#pragma once
/*

ÿ�δ������������ж�ȡһ�����ִ�У�
������Ϊ�գ���������������л�ȡһ��

*/
#include"Object.h"
using namespace std;
class enemyTank:public Object
{

public:
	int Hp;//Ѫ��
	int level;//�ȼ�
	int bulletId;//�Լ����ӵ�
	deque<cmd>attion;//����ִ�е��ж�

};

