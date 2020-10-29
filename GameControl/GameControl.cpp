#include "GameControl.h"

int GameControl::run()
{
	//执行顺序
	/*
	1.读取playerbulletlist 执行move
	2.读取enemybulletlist ，执行move
	3.读取enemylist 执行每个对象的指令
	4.检测碰撞
	5.绘制
	6.等待
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
	//检测碰撞，在移动方法中需要进行检测，
	/*
	1.玩家子弹与敌人
	2.敌人子弹与玩家
	3.子弹与地图
	
	
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
//to  do  处理剩余命令的实现
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


