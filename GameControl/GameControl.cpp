#include "GameControl.h"

int GameControl::run()
{
	//ִ��˳��
	/*
	1.��ȡplayerbulletlist ִ��move
	2.��ȡenemybulletlist ��ִ��move
	3.��ȡenemylist ִ��ÿ�������ָ��
	4.�����ײ
	5.����
	6.�ȴ�
	*/
	for (list<bullet>::iterator i = playerbullets.begin(); i !=playerbullets.end(); i++)
		bullet_move(&(*i), (*i).dir);
	
	for (auto i = enemybullets.begin(); i !=enemybullets.end(); i++)
		bullet_move(&(*i), (*i).dir);
	
	for (auto i = enemys.begin(); i != enemys.end(); i++)
	{
		if ((*i).available==false)
		{
			die(&(*i));
			enemys.erase(i);
		}else
		{
			enemy_act(*i);
		}
	}
	//�����ײ�����ƶ���������Ҫ���м�⣬
	/*
	1.����ӵ������
	2.�����ӵ������
	3.�ӵ����ͼ
	
	
	*/

	return 0;
}

int GameControl::getcmd(char c)
{
	cmd con = cmdCreater::c_to_cmd(c);
	switch (con)
	{
	case cmd::Up:
		p.y += TANK_STEP;
		break;
	case cmd::Right:
		p.x += TANK_STEP;
		break;
	case cmd::Down:
		p.y -= TANK_STEP;
		break;
	case cmd::Left:
		p.x -= TANK_STEP;
		break;
	
	case cmd::Attack:
//to  do  ����ʣ�������ʵ��
		if (playerbullets.size()<MAX_PLAYER_BULLET)
		{
			bullet temp(&p, p.dir, p.attack);
			temp.id = idMaker.out();
			playerbullets.push_back(temp);
		}
		break;
	case cmd::Explosion:
		live = false;
		die(&p);
		break;
	default:
		break;
	}

	return 0;
}
void GameControl::die(Object* o)
{
}
void GameControl::enemy_act(enemyTank& t)
{
	if (t.action.empty())
		t.action = cmdMaker.out(8);
	else
	{
		switch (t.action.front())
		{
		case cmd::Up:
			t.y += TANK_STEP; break;
		case cmd::Down:
			t.y -= TANK_STEP; break;
		case cmd::Right:
			t.x += TANK_STEP; break;
		case cmd::Left:
			t.x -= TANK_STEP; break;
		case cmd::Attack:
			bullet temp = bullet(&t, t.dir, t.attack);
			t.bulletId = temp.ID();
		case cmd::Explosion:
			t.available = false;
			 break;
		default:
			break;
		}
	}
}
inline void GameControl::bullet_move(Object* o, cmd d)
{
	switch (d)
	{
	case cmd::Up:
		(*o).y += BULLET_STEP;
		break;
	case cmd::Down:
		(*o).y -= BULLET_STEP;
	case cmd::Left:
		(*o).x -= BULLET_STEP;
	case cmd::Right:
		(*o).x += BULLET_STEP;
	default:
		break;
	}
}


