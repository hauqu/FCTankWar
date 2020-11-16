#include "cmdCreater.h"

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
		cs.push_back(cmd::NA);
	}
	return cs;
	
}

deque<cmd> cmdCreater::out(Aicmd c)
{
	deque<cmd>temp;
	if (c == Aicmd::stay)
	{
		temp.push_back(cmd::Down);
		for (int i = 0; i < 100; i++)
		{
			temp.push_back(cmd::Stop);
		}
	}
	return temp;

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

