#pragma once
#include"baseStruct.h"
using namespace std;
class cmdCreater
{
public:
	cmdCreater();
	 cmd int_to_cmd(int c);
	static cmd c_to_cmd(char c);
	deque<cmd>out(int ncmd);




	//Aicmd ��Ҫ��ȡ��ͼ��Ϣ�������Ϣ���з�̹����Ϣ�ȵ�
	deque<cmd>out(Aicmd c);
};