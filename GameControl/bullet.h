#pragma once
/*

�����ӵ���

*/
#include"Object.h"
/*
�ڽ��ܵ�һ��attackָ���
gameControl ������һ���ӵ�����
������ӵ�list����
tank�޷�ͨ���Լ��ҵ��Լ�������ӵ�
ֻ��ͨ��id���������������tank��Ȩ����������
��ȡattack ��cmd������gameControl�У�
�����ӵ���ʵ����ҲӦ���ڴˣ�

*/

class bullet:public Object
{
public:
	int attack;//������
	cmd dir;//�ӵ��н�����
	int TankId;//̹�˵�id
	bullet();//��������һ���ӵ���
	bullet(Object*o,cmd d,int a);
	//�������ָ꣬�򣬹���������

	
};