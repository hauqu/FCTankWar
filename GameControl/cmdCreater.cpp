#include "cmdCreater.h"
extern const int baseCmdCateNumber;


cmdCreater::cmdCreater()
{
	srand(time(nullptr));
}
deque<cmd> cmdCreater::out(int ncmd)
{
	deque<cmd>cs;
	for (int i = 0; i < ncmd; i++)
	{
		cs.push_back(int_to_cmd(rand() % baseCmdCateNumber));
	}
	return cs;
	
}

deque<cmd> cmdCreater::out(Aicmd c)
{
	return deque<cmd>();
}

inline cmd cmdCreater::int_to_cmd(int c)
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
		//return cmd::Explosion; break;
		return cmd::NA; break;//�����ױ�ը
	default:
		return cmd::NA; break;
		break;
	}
}

inline cmd cmdCreater::c_to_cmd(char c)
{
	switch (c)
	{
	
	case 'w':
	case 'W':
		return cmd::Up; break;
	case 'D':
	case 'd':
		return cmd::Right; break;
	case 's':
	case 'S':
		return cmd::Down; break;
	case 'a':
	case 'A':
		return cmd::Left; break;
	
	case ' ':
		return cmd::Attack; break;
	case 33:
		return cmd::Explosion; break;
	default:
		return cmd::NA; break;
		break;
	}
}