#include "GameControl.h"
//方法过于混乱，需要重新检查各类构造函数


GameControl::GameControl()	
{
	p = playerTank();
	
	mapDate.playerbase.w = MAP_W;
	mapDate.playerbase.h = MAP_H;
	mapDate.playerbase.x *= MAP_W;
	mapDate.playerbase.y *= MAP_H;
	live = false;
	for (auto i = mapDate.enemybases.begin();
		i != mapDate.enemybases.end();  i++)
	{
		(*i).w = MAP_W;
		(*i).h = MAP_H;
		(*i).x *= MAP_W;
		(*i).y *= MAP_H;
	}
	MaxEnemys = 4;
}
int GameControl::start(int level)
{
	mapDate.loadMap(level);
	mapDate.playerbase.w = MAP_W;
	mapDate.playerbase.h = MAP_H;
	mapDate.playerbase.x *= MAP_W;
	mapDate.playerbase.y *= MAP_H;
	for (auto i = mapDate.enemybases.begin();
		i != mapDate.enemybases.end();  i++)
	{
		(*i).w = MAP_W;
		(*i).h = MAP_H;
		(*i).x *= MAP_W;
		(*i).y *= MAP_H;
	}
	p.available = true;
	p.x = mapDate.playerbase.x;
	p.y = mapDate.playerbase.y;
	p.w = mapDate.playerbase.w;
	p.h = mapDate.playerbase.h;
	p.id = idMaker.out();
	live = true;
	for (auto i = mapDate.enemybases.begin();
		i != mapDate.enemybases.end();  i++)
	{
		enemyTank e;
		e.available = true;
		e.x = (*i).x;
		e.y = (*i).y;
		e.w = (*i).w;
		e.h = (*i).h;
		e.id = idMaker.out();
		enemys.push_back(e);
		
	}

	return 1;
}
int GameControl::run()
{

	//p  b move
	for (list<bullet>::iterator i = playerbullets.begin(); i != playerbullets.end(); i++)
		bullet_move(*i);
	//e b move
	for (auto i = enemybullets.begin(); i != enemybullets.end(); i++)
		bullet_move(*i);
	//检测b  碰撞
	for (list<bullet>::iterator i = playerbullets.begin(); i != playerbullets.end(); i++)
	{
		for (auto j = enemys.begin(); j != enemys.end(); i++)
		{
			if (collision(&(*i), &(*j)))
			{
				//处理玩家子弹与敌人
				(*i).available = false;//子弹失效
				(*j).Hp -= (*i).attack;//减少血量
				if ((*j).Hp <= 0)//死亡
					(*j).available = false;
			}
		}
		if((*i).available==true)
		{
			int w = (*i).x / TANK_W;
			int h = (*i).y / TANK_H;
			if (collision( &(*i),&mapDate.data[w][h]))
			{
				mapDate.data[w][h].cate = objectCate::space;
				(*i).available = false;
			}
		}
	}
	for (auto i = enemybullets.begin(); i != enemybullets.end(); i++)
	{
		if(collision(&(*i),&p))
		{
			(*i).available = false;
			p.Hp -= (*i).attack;
			if (p.Hp<=0)
			{
				p.available = false;
			}
		}
		if ((*i).available==true)
		{
			int w = (*i).x / TANK_W;
			int h = (*i).y / TANK_H;
			if (collision(&(*i), &mapDate.data[w][h]))
			{
				mapDate.data[w][h].cate = objectCate::space;
				(*i).available = false;
			}
		}
	}

	for (auto i = enemys.begin(); i != enemys.end(); i++)
	{
		if ((*i).action.empty()==true)
		{
			(*i).action == cmdMaker.out(10);
		}
		else
		{
			act_enemy(*i);
		}
	}
	return 1;
}

void GameControl::initMap()
{
	//依照date的存储结构来确定相对位置
	//以地图元素长宽常量决定坐标
	for (int i = 0; i < mapDate.data.size(); i++)
	{
		for (int j = 0; j < mapDate.data[i].size(); j++)
		{
			mapDate.data[i][j].available = true;
			mapDate.data[i][j].id = idMaker.out();
			mapDate.data[i][j].w = MAPOBJECT_W;
			mapDate.data[i][j].h = MAPOBJECT_H;
			if (mapDate.data[i][j].cate == objectCate::space) 
			{
				mapDate.data[i][j].x =-100;
				mapDate.data[i][j].y = -100;
			}
			else {
				mapDate.data[i][j].x = i * MAPOBJECT_W;
				mapDate.data[i][j].y = j * MAPOBJECT_H;
			}
			//成员 cate 已经在map 类里初始化
		}
	}
}
bool GameControl::collision(Object* o1, Object* o2)
{
	 if((o1->x - o2->x)*(o1->x - o2->x)<
		 (o1->w+o2->w)* (o1->w + o2->w))
	 {
		 if ((o1->y - o2->y) * (o1->y - o2->y) <
			 (o1->h + o2->h) * (o1->h + o2->h))
			 return true;
	 }
	 return false;
}

 void GameControl::bullet_move(bullet &b)
{
	//子弹移动前检验碰撞？
	//先移动，后处理

	switch (b.dir)
	{
	case cmd::Up:
		b.y += BULLET_STEP;
		break;
	case cmd::Down:
		b.y -= BULLET_STEP;
	case cmd::Left:
		b.x -= BULLET_STEP;
	case cmd::Right:
		b.x += BULLET_STEP;
	default:
		break;
	}
}

int GameControl::act_enemy(enemyTank& e)
{
	cmd con = e.action.back();
	e.action.pop_back();
	if (con==cmd::NA||con==cmd::Stop)
	{
		return 0;
	}
	if (con==cmd::Attack)
	{
		bullet temp(&e,e.dir,e.attack,idMaker.out());
		enemybullets.push_back(temp);
		return 1;
	}
	else if(con==cmd::Explosion)
	{
		e.available = false;
		return 1;
	}else if(con==cmd::Up|| con == cmd::Right || 
		con == cmd::Left || con == cmd::Down  )
	{
		int x = e.x; int y = e.y;
		switch (con)
		{
		
		case cmd::Up:
			y += TANK_STEP;
			break;
		case cmd::Right:
			x += TANK_STEP;
			break;
		case cmd::Down:
			y -= TANK_STEP;
			break;
		case cmd::Left:
			x -= TANK_STEP;
			break;
		default:
			break;
		}
		if (!collision(&e,&mapDate.data[x/TANK_W][x/TANK_H]))
		{
			e.x = x; e.y = y;
		}
		return 1;
	}

	return 0;
}
cmd GameControl::c_to_cmd(char c)
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

void GameControl::clearDieObject()
{
	//迭代器删除之后无效，需要删除前保存


	auto i = playerbullets.begin();
	while (i != playerbullets.end())
	{
		if ((*i).available == false)
			playerbullets.erase(i++);//删除当前位置并后移
		else i++;
	}//玩家子弹
	auto it = enemybullets.begin();
	while (it != enemybullets.end())
	{
		if ((*it).available == false)
			enemybullets.erase(it++);//删除当前位置并后移
		else it++;
	}//敌人子弹

	auto it_e = enemys.begin();
	while (it_e != enemys.end())
	{
		if ((*it_e).available == false)
			enemys.erase(it_e++);//删除当前位置并后移
		else it_e++;
	}//敌人

}

int GameControl::getcmd(char c)
{
	cmd con = c_to_cmd(c);
	if (con == cmd::NA || con == cmd::Stop)
	{
		return 0;
	}
	if (con == cmd::Attack)
	{
		bullet temp(&p, p.dir, p.attack, idMaker.out());
		enemybullets.push_back(temp);
		return 1;
	}
	else if (con == cmd::Explosion)
	{
		p.available = false;
		return 1;
	}
	else if (con == cmd::Up || con == cmd::Right ||
		con == cmd::Left || con == cmd::Down)
	{
		int x = p.x; int y = p.y;
		switch (con)
		{

		case cmd::Up:
			y += TANK_STEP;
			break;
		case cmd::Right:
			x += TANK_STEP;
			break;
		case cmd::Down:
			y -= TANK_STEP;
			break;
		case cmd::Left:
			x -= TANK_STEP;
			break;
		default:
			break;
		}
		if (!collision(&p, &mapDate.data[x / TANK_W][x / TANK_H]))
		{
			p.x = x; p.y = y;
		}
		return 1;
	}

	return 0;
}
bool GameControl::CreatEnemy(enemyTank e)
{

	//生成要求，1.当前坦克数量小于最大数
	//2.敌人基地没有其他坦克
	for (auto i = mapDate.enemybases.begin(); i != mapDate.enemybases.end(); i++)
	{
		bool falg = true;//该基地是否可用
		for (auto j = enemys.begin(); j != enemys.end(); j++)
		{
				if ((*i).available)
				if (collision(&(*i), &(*j)))
					falg = false;//有坦克，不可用
		}
		if (falg)//生成一个就结束
		{
			e.x = (*i).x;
			e.y = (*i).y;
			e.id = idMaker.out();
			e.available = true;
			enemys.push_back(e);
			return true;

		}
	}
	return false;//

}




/*
int GameControl::run()
{
	//执行顺序
	
	//p  b move
	for (list<bullet>::iterator i = playerbullets.begin(); i !=playerbullets.end(); i++)
		bullet_move(&(*i), (*i).dir);
	//e b move
	for (auto i = enemybullets.begin(); i !=enemybullets.end(); i++)
		bullet_move(&(*i), (*i).dir);
	
	//检测b  碰撞
	for (list<bullet>::iterator i = playerbullets.begin(); i != playerbullets.end(); i++)
	{
		for (auto j = enemys.begin(); j != enemys.end(); i++)
		{
			if((*i).collision(*j))
			{
				//处理玩家子弹与敌人
				(*i).available = false;//子弹失效
				(*j).Hp -= (*i).attack;//减少血量
				if ((*j).Hp<=0)//死亡
					(*j).available = false;
			}
		}
		//检测 b t

		/*
		对于 一个对象与地图来说，根据自身的x，y
		能够大致确定一个范围，
		减少比较次数
		x/mapW
		y/mapH
		确定了一个元素
		//to do 以空间换时间，提高执行效率
		10.30

		*/
/*
		int w = (*i).x / MAP_W;
		int h = (*i).y / MAP_H; 

		/*
		mapDate.data[w][h]
		该元素为子弹 左下角元素
		所以需要检测 左上，右上，左下，右下
		
		*/
/*
		//首先检测碰撞元素
		w++; h++;
		switch (mapDate.data[w][h].cate)
		{
		case objectCate::water:
		case objectCate::space:
			//通过
			break;
		case objectCate::wall:

			//同时摧毁
			mapDate.data[w][h].cate = objectCate::space;
			(*i).available = false;
			break;
		case objectCate::falg:
		case objectCate::strongWall:
		case objectCate::enemyBase:
			//子弹摧毁
			(*i).available = false;
			break;
		
		case objectCate::playerBase:
			//攻击自己的基地
			//游戏结束
			p.available = false;
			break;
		default:
			break;
		}



	}

	for (list<bullet>::iterator i = enemybullets.begin(); i != playerbullets.end(); i++)
	{
		
		if ((*i).collision(p))//检测是否击中玩家
		{
			p.Hp -= (*i).attack;
			if (p.Hp <= 0) p.available = false;
			(*i).available = false;
		}


		int w = (*i).x / MAP_W;
		int h = (*i).y / MAP_H;

		/*
		mapDate.data[w][h]
		该元素为子弹 左下角元素
		所以需要检测 左上，右上，左下，右下

		*/
/*		w++; h++;
		switch (mapDate.data[w][h].cate)
		{
		case objectCate::water:
		case objectCate::space:
			//通过
			break;
		case objectCate::wall:

			//同时摧毁
			mapDate.data[w][h].cate = objectCate::space;
			(*i).available = false;
			break;
		case objectCate::falg:
		case objectCate::strongWall:
		case objectCate::enemyBase:
			//子弹摧毁
			(*i).available = false;
			break;

		case objectCate::playerBase:
			//攻击玩家的基地
			//游戏结束
			p.available = false;
			break;
		default:
			break;
		}



	}
	

	


	return 1;//执行成功
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
			playerbullets.push_back(bullet(&p, p.dir, p.attack, idMaker.out()));
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
			enemybullets.push_back(bullet(&t, t.dir, t.level, idMaker.out()));
			break;
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
	//子弹移动前检验碰撞？
	//先移动，后处理

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
void GameControl::clearDieObject()
{
	//迭代器删除之后无效，需要删除前保存


	auto i = playerbullets.begin();
	while (i != playerbullets.end())
	{
		if ((*i).available == false)
			playerbullets.erase(i++);//删除当前位置并后移
		else i++;
	}//玩家子弹
	auto it = enemybullets.begin();
	while (it!=enemybullets.end())
	{
		if ((*it).available == false)
			enemybullets.erase(it++);//删除当前位置并后移
		else it++;
	}//敌人子弹
	
	auto it_e = enemys.begin();
	while (it_e != enemys.end())
	{
		if ((*it_e).available == false)
			enemys.erase(it_e++);//删除当前位置并后移
		else it_e++;
	}//敌人

}

void GameControl::initMap()
{
	//依照date的存储结构来确定相对位置
	//以地图元素长宽常量决定坐标
	for (int i = 0; i < mapDate.data.size(); i++)
	{
		for(int j=0;j<mapDate.data[i].size();j++)
		{
			mapDate.data[i][j].available = true;
			mapDate.data[i][j].id = idMaker.out();
			mapDate.data[i][j].w = MAPOBJECT_W;
			mapDate.data[i][j].h = MAPOBJECT_H;
			mapDate.data[i][j].x = i * MAPOBJECT_W;
			mapDate.data[i][j].y = j * MAPOBJECT_H;
			//成员 cate 已经在map 类里初始化
		}
	}
}

*/