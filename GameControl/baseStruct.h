#pragma once
//�ڴ˴��������б�Ҫ��ͷ�ļ�
#include<vector>//map �� �洢��Ϣʹ��
#include<ctime>//���������
#include<string>//map���ļ�����
#include<list>//gameControl ���� tank��ض���
#include<fstream>//map���ļ�����
#include<deque>//�洢ָ������
#include<ctime>

//����һЩ����(��һ��)

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
	stay,//�����غ�ֹ
};//����ָ���Ѱ�ң�Χ�£��ɱ����Ϊ����ָ��
//�����ָ����ָ������������