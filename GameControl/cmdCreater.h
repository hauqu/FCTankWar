#pragma once
#include"baseStruct.h"
using namespace std;
class cmdCreater
{
public:
	cmdCreater();
	 cmd int_to_cmd(int c);
	
	 deque<cmd>out(int ncmd);//��������һ�����ɼ���ָ��

	//Aicmd ��Ҫ��ȡ��ͼ��Ϣ�������Ϣ���з�̹����Ϣ�ȵ�
	deque<cmd>out(Aicmd c);
};