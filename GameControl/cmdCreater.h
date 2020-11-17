#pragma once
#include"baseStruct.h"
using namespace std;
/*
该类负责每个敌人对象的行动
因为生成aicmd 所以需要区分每个敌人，每个元素
故为每个object 分配id
*/
class cmdCreater
{
public:
	
	cmdCreater();
	 cmd int_to_cmd(int c);
	
	 deque<cmd>out(int ncmd);//参数决定一次生成几个指令

	//Aicmd 需要获取地图信息，玩家信息，敌方坦克信息等等
	deque<cmd>out(Aicmd c);

};