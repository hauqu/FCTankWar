#pragma once

//��Ϸ�Ļ������� ��������
enum class objectCate//����ļ�������
{
	playerTank, enemyTank, playerBullet,
	enemyBullet, space,wall
};
class Object
{
public:
	bool available;//����
	objectCate cate;
	int id;//id ��������ʶ��

	int x;//������
	int y;//������
	int w;//���
	int h;//����

	bool collision(const Object& o)const;
	int ID(void)const;
	//��ײ��� ��ײ����
};

