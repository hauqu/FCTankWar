#pragma once
#include<ctime>
#include<deque>
/*
决定了敌人的攻击频率，移动频率，
生成ai指令

*/
using namespace std;
enum class cmd
{
	NA=0,//无效
	Up, Right, Down, Left, Stop,//移动 上 右 下 左
	Attack,//攻击指令
	Explosion,//自爆
};
enum class Aicmd 
{
	random,
};//复杂指令，如寻找，围堵，可被拆分为基础指令
class cmdMaker
{
public:
	cmdMaker();
	deque<cmd> out(int numberCmd);
	cmd int_to_cmd(int c);
};
inline cmdMaker::cmdMaker()
{
	srand(time(nullptr));
}
deque<cmd> cmdMaker::out(int numberCmd)
{
	deque<cmd>cs;
	for (int i = 0; i < numberCmd; i++)
	{
		cs.push_back(int_to_cmd(rand() % 8));
	}
	return cs;
	// TODO: 在此处插入 return 语句
}
inline cmd cmdMaker::int_to_cmd(int c)
{
	switch (c)
	{
	case 0:
		return cmd::NA; break;
	case 1:
		return cmd::Up; break;
	case 2:
		return cmd::Right; break;
	case 3:
		return cmd::Down; break;
	case 4:
		return cmd::Left; break;
	case 5: 
		return cmd::Stop; break;
	case 6:
		return cmd::Attack; break;
	case 7:
		return cmd::Explosion; break;
	default:
		return cmd::NA; break;
		break;
	}
}