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
	
	Object(int x, int y, int w, int h,objectCate oc);;//�вι���available Ϊtrue
	
	Object();//�޲ι���available Ϊfalse
	virtual ~Object(){}
	
};

