#pragma once
#include"baseStruct.h"
using namespace std;
class cmdCreater
{
public:
	cmdCreater();
	cmd int_to_cmd(int c);
	deque<cmd>out(int ncmd);




	//Aicmd 需要获取地图信息，玩家信息，敌方坦克信息等等
	deque<cmd>out(Aicmd c);
};