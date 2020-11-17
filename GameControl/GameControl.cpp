#include "GameControl.h"
//方法过于混乱，需要重新检查各类构造函数


GameControl::GameControl():
	MaxEnemys(4),
	mapDate(Map()),
	idMaker(IdCreater()),
	cmdMaker(cmdCreater()),
	p(playerTank()),
	live(false)
{
	playerbullet = nullptr;
}
int GameControl::start(int level)
{
	mapDate.loadMap(level);
	initMap();
	mapDate.playerbase.w = TANK_W;
	mapDate.playerbase.h = TANK_H;
	mapDate.playerbase.x *= TANK_W;
	mapDate.playerbase.y *= TANK_H;
	for (auto i = mapDate.enemybases.begin();
		i != mapDate.enemybases.end();  i++)
	{
		(*i).w = TANK_W;
		(*i).h = TANK_H;
		(*i).x *= TANK_W;
		(*i).y *= TANK_H;
	}
	p.available = true;

	p.x = mapDate.playerbase.x;
	p.y = mapDate.playerbase.y-TANK_H;
	p.w = TANK_W;
	p.h = TANK_H;
	p.id = idMaker.out();
	live = true;
	for (auto i = mapDate.enemybases.begin();
		i != mapDate.enemybases.end();  i++)
	{
		enemyTank e;
		e.available = true;
		e.x = (*i).x+TANK_W;
		e.y = (*i).y;
		e.w = TANK_W;
		e.h = TANK_H;
		e.level = 1;
		e.id = idMaker.out();
		e.action = cmdMaker.out(10);
		enemys.push_back(e);
		
	}
	
	return 1;
}
int GameControl::run()
{

	/*******************玩家子弹移动**********************/
	if (playerbullet != nullptr)
	{
		if (playerbullet->available != false)
			bullet_move(*playerbullet);
		for (auto j = enemys.begin(); j != enemys.end(); j++)
		{
			if (collision(playerbullet, &(*j)))
			{
				//处理玩家子弹与敌人
				playerbullet->available = false;//子弹失效
				(*j).Hp -= playerbullet->attack;//减少血量
				if ((*j).Hp <= 0)//死亡
					(*j).available = false;
			}
		}//子弹与地图元素碰撞
		if (playerbullet->available == true)
		{
			int w = playerbullet->x / TANK_W;//左，上会少一格
			int h = playerbullet->y / TANK_H;//需要补偿
			switch (playerbullet->dir)
			{
				//由于物体的结构是中心点式，需要进行补偿
			case cmd::Up:
				
				break;
			case cmd::Down:
				h++;
				break;
			case cmd::Right:
				w++;
				break;
			case cmd::Left:
				
				break;
			default:
				break;
			}
			if (collision(playerbullet, &mapDate.data[w][h]))
			{
				switch (mapDate.data[w][h].cate)
				{
				case objectCate::wall:
					mapDate.data[w][h].cate = objectCate::space;
					playerbullet->available = false;
					break;
				case objectCate::enemyBase:
				case objectCate::playerBase:
				case objectCate::strongWall:
					playerbullet->available = false;
					break;
				default:
					break;
				}
			}

		}

	}
	/*******************敌方子弹移动***********************/
	if (!enemybullets.empty())
	{
		for (auto i = enemybullets.begin(); i != enemybullets.end(); i++)
		{
			if ((*i).available != false) {
				bullet_move(*i);
				//检测碰撞玩家
				if (collision(&(*i), &p))
				{
					(*i).available = false;
					p.Hp -= (*i).attack;
					if (p.Hp <= 0)
					{
						p.available = false;
					}
				}
				//检测碰撞地图
				if ((*i).available == true)
				{
					int w = (*i).x / TANK_W;
					int h = (*i).y / TANK_H;
					switch ((*i).dir)
					{
						//由于物体的结构是中心点式，需要进行补偿
					case cmd::Up:

						break;
					case cmd::Down:
						h++;
						break;
					case cmd::Right:
						w++;
						break;
					case cmd::Left:

						break;
					default:
						break;
					}
					if (collision(&(*i), &mapDate.data[w][h]))
					{
						switch (mapDate.data[w][h].cate)
						{
						case objectCate::wall:
							mapDate.data[w][h].cate = objectCate::space;
							(*i).available = false;
							break;
						case objectCate::enemyBase:
						case objectCate::playerBase:
						case objectCate::strongWall:
							(*i).available = false;
							break;
						default:
							break;
						}
					}

				}
			}
		}
	}
	/****************敌人行动*******************************/
	if (!enemys.empty()) 
	{
		for (auto i = enemys.begin(); i != enemys.end(); i++)
		{
			if ((*i).action.empty())
			{
				(*i).action = cmdMaker.out(20);
			}
			else
			{
				act_enemy(*i);
			}
		}
	}
	/********************************************************/

	if(p.available==true)
	return 1;
	else
	{
		return 0;
	}
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
			mapDate.data[i][j].x = i * MAPOBJECT_W;
			mapDate.data[i][j].y = j * MAPOBJECT_H;
			
			//成员 cate 已经在map 类里初始化
		}
	}
}
bool GameControl::collision(Object* o1, Object* o2)
{

	
	 if((o1->x - o2->x)*(o1->x - o2->x)<
		 (o1->w/2+o2->w/2)* (o1->w/2 + o2->w/2))
	 {
		 if ((o1->y - o2->y) * (o1->y - o2->y) <
			 (o1->h/2 + o2->h/2) * (o1->h/2 + o2->h/2))
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
		b.y -= BULLET_STEP/2;
		break;
	case cmd::Down:
		b.y += BULLET_STEP/2; 
		break;
	case cmd::Left:
		b.x -= BULLET_STEP/2;
		break;
	case cmd::Right:
		b.x += BULLET_STEP/2;
		break;
	default:
		break;
	}
}

 int GameControl::act_enemy(enemyTank& e)
 {
	 cmd con = e.action.back();
	 e.action.pop_back();
	 if (con == cmd::NA || con == cmd::Stop)
	 {
		 return 0;
	 }
	 if (con == cmd::Attack)
	 {
		 bullet temp(&e,e.dir,e.attack,idMaker.out());
		 enemybullets.push_back(temp);
		 return 1;
	 }
	 else if (con == cmd::Explosion)
	 {
		 e.available = false;
		 return 1;
	 }
	 else if (con == cmd::Up || con == cmd::Right ||
		 con == cmd::Left || con == cmd::Down)
	 {
		 if(con!=e.dir)
		 {
			 e.dir = con;
			 //return 1;
		 }
		 int x = e.x; int y = e.y;
		 switch (con)
		 {
		 case cmd::Up:
			 y -= TANK_STEP;
			 break;
		 case cmd::Right:
			 x += TANK_STEP;
			 break;
		 case cmd::Down:
			 y += TANK_STEP;
			 break;
		 case cmd::Left:
			 x -= TANK_STEP;
			 break;
		 default:
			 break;
		 }
		 int i = x / TANK_W;
		 int j = y / TANK_H;
		 //
		 
		 switch (mapDate.data[i][j].cate)
		{
		 case objectCate::wall:
		 case objectCate::playerBase:
		 case objectCate::strongWall:
				 //do nothing
				 e.dir = con;
				 break;
		 case objectCate::space:
		 case objectCate::enemyBase:
				 e.x = x;
				 e.y = y;
				 e.dir = con;
		 default:
				 break;
			 };

			 return 1;

		 return 0;
	 }
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
	}
}

void GameControl::clearDieObject()
{
	//迭代器删除之后无效，需要删除前保存

	/*
	auto i = playerbullets.begin();
	while (i != playerbullets.end())
	{
		if ((*i).available == false)
			playerbullets.erase(i++);//删除当前位置并后移
		else i++;
	}//玩家子弹
	*/
	if(playerbullet!=nullptr)
	if (playerbullet->available == false)
		playerbullet =nullptr;

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
	}else 
	if (con == cmd::Attack)
	{
		if (playerbullet == nullptr) {
			bullet temp(&p, p.dir, p.attack, idMaker.out());
			//playerbullets.push_back(temp);
			playerbullet = new bullet(temp);
			return 1;
		}
	}
	else if (con == cmd::Explosion)
	{
		p.available = false;
		return 1;
	}
	else if (con == cmd::Up || con == cmd::Right ||
		con == cmd::Left || con == cmd::Down)
		{
			if (con != p.dir){	p.dir = con;return 1;}//转向
			else 
			{
				int x = p.x; int y = p.y;
				switch (con)
				{

				case cmd::Up:
					y -= TANK_STEP;
					break;
				case cmd::Right:
					x += TANK_STEP;
					break;
				case cmd::Down:
					y += TANK_STEP;
					break;
				case cmd::Left:
					x -= TANK_STEP;
					break;
				default:
					break;
				}
				//构建移动规则 与 活动物体交互
				Object o(x, y, p.w, p.h, objectCate::playerTank);
				if (!enemys.empty()) 
				{
					for (auto k = enemys.begin(); k != enemys.end(); k++)
					if (collision(&o, &(*k)))
							return 0;
				}
				//构建移动规则(与地图交互)
				int i = x / TANK_W;
				int j = y / TANK_H;
				//
				//if (!collision(&p, &mapDate.data[i][j]))
				{
					switch (mapDate.data[i][j].cate)
					{
					case objectCate::wall:
					case objectCate::enemyBase:
					case objectCate::strongWall:
						//do nothing
						p.dir = con;
						break;
					case objectCate::space:
					case objectCate::playerBase:
						p.x = x;
						p.y = y;
						p.dir = con;
					default:

						break;
					};
					return 1;
				}
			}

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
Graph& GameControl::creatGraph()
{
	Graph temp(mapDate.MaxW, mapDate.MaxH, TANK_W);
	//建立全通图
	
	//地图元素生成图
	for (int i = 0; i < mapDate.data.size(); i++)
	{
		for (int j = 0; j < mapDate.data[i].size(); j++)
		{
			temp.G[i][j].cate = mapDate.data[i][j].cate;
			switch (mapDate.data[i][j].cate)
			{
			case objectCate::playerBase:
			case objectCate::wall:
			case objectCate::strongWall:
			case objectCate::water:
				//不可通过元素
				if (j > 0) { temp.G[i][j].up = nullptr; }
				if (j < mapDate.MaxH - 1) { temp.G[i][j].down = nullptr; }
				if (i > 0) { temp.G[i][j].left = nullptr; }
				if (i < mapDate.MaxW - 1) { temp.G[i][j].right = nullptr; }
				//断开自身连接外面
				if(j>1) temp.G[i][j-1].down = nullptr;
				if(j<mapDate.MaxH-2) temp.G[i][j+1].up = nullptr;
				if(i>1) temp.G[i - 1][j].right = nullptr;
				if(i<mapDate.MaxW-2) temp.G[i + 1][j].left = nullptr;
				//断开外界与自身的连接
				break;
			case objectCate::space:
			case objectCate::enemyBase:
				//do nothing

				break;
			default:
				break;
			}
		}
	}


}



