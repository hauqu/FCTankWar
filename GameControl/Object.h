#pragma once
#include"baseStruct.h"
//��Ϸ�Ļ������� ��������

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
	//to do �������캯��
	Object(int x, int y, int w, int h,objectCate oc);
	bool collision(const Object& o)const;
	Object();
	int ID(void)const;
	//��ײ��� ��ײ����
};

