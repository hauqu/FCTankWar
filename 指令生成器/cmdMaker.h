#pragma once
#include<ctime>
#include<deque>
/*
�����˵��˵Ĺ���Ƶ�ʣ��ƶ�Ƶ�ʣ�
����aiָ��

*/
using namespace std;
enum class cmd
{
	NA=0,//��Ч
	Up, Right, Down, Left, Stop,//�ƶ� �� �� �� ��
	Attack,//����ָ��
	Explosion,//�Ա�
};
enum class Aicmd 
{
	random,
};//����ָ���Ѱ�ң�Χ�£��ɱ����Ϊ����ָ��
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
	// TODO: �ڴ˴����� return ���
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