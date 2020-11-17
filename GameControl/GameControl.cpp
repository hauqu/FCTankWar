#include "GameControl.h"
//�������ڻ��ң���Ҫ���¼����๹�캯��


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

	/*******************����ӵ��ƶ�**********************/
	if (playerbullet != nullptr)
	{
		if (playerbullet->available != false)
			bullet_move(*playerbullet);
		for (auto j = enemys.begin(); j != enemys.end(); j++)
		{
			if (collision(playerbullet, &(*j)))
			{
				//��������ӵ������
				playerbullet->available = false;//�ӵ�ʧЧ
				(*j).Hp -= playerbullet->attack;//����Ѫ��
				if ((*j).Hp <= 0)//����
					(*j).available = false;
			}
		}//�ӵ����ͼԪ����ײ
		if (playerbullet->available == true)
		{
			int w = playerbullet->x / TANK_W;//���ϻ���һ��
			int h = playerbullet->y / TANK_H;//��Ҫ����
			switch (playerbullet->dir)
			{
				//��������Ľṹ�����ĵ�ʽ����Ҫ���в���
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
	/*******************�з��ӵ��ƶ�***********************/
	if (!enemybullets.empty())
	{
		for (auto i = enemybullets.begin(); i != enemybullets.end(); i++)
		{
			if ((*i).available != false) {
				bullet_move(*i);
				//�����ײ���
				if (collision(&(*i), &p))
				{
					(*i).available = false;
					p.Hp -= (*i).attack;
					if (p.Hp <= 0)
					{
						p.available = false;
					}
				}
				//�����ײ��ͼ
				if ((*i).available == true)
				{
					int w = (*i).x / TANK_W;
					int h = (*i).y / TANK_H;
					switch ((*i).dir)
					{
						//��������Ľṹ�����ĵ�ʽ����Ҫ���в���
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
	/****************�����ж�*******************************/
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
	//����date�Ĵ洢�ṹ��ȷ�����λ��
	//�Ե�ͼԪ�س�������������
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
			
			//��Ա cate �Ѿ���map �����ʼ��
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
	//�ӵ��ƶ�ǰ������ײ��
	//���ƶ�������

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
	//������ɾ��֮����Ч����Ҫɾ��ǰ����

	/*
	auto i = playerbullets.begin();
	while (i != playerbullets.end())
	{
		if ((*i).available == false)
			playerbullets.erase(i++);//ɾ����ǰλ�ò�����
		else i++;
	}//����ӵ�
	*/
	if(playerbullet!=nullptr)
	if (playerbullet->available == false)
		playerbullet =nullptr;

	auto it = enemybullets.begin();
	while (it != enemybullets.end())
	{
		if ((*it).available == false)
			enemybullets.erase(it++);//ɾ����ǰλ�ò�����
		else it++;
	}//�����ӵ�

	auto it_e = enemys.begin();
	while (it_e != enemys.end())
	{
		if ((*it_e).available == false)
			enemys.erase(it_e++);//ɾ����ǰλ�ò�����
		else it_e++;
	}//����

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
			if (con != p.dir){	p.dir = con;return 1;}//ת��
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
				//�����ƶ����� �� ����彻��
				Object o(x, y, p.w, p.h, objectCate::playerTank);
				if (!enemys.empty()) 
				{
					for (auto k = enemys.begin(); k != enemys.end(); k++)
					if (collision(&o, &(*k)))
							return 0;
				}
				//�����ƶ�����(���ͼ����)
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

	//����Ҫ��1.��ǰ̹������С�������
	//2.���˻���û������̹��
	for (auto i = mapDate.enemybases.begin(); i != mapDate.enemybases.end(); i++)
	{
		bool falg = true;//�û����Ƿ����
		for (auto j = enemys.begin(); j != enemys.end(); j++)
		{
				if ((*i).available)
				if (collision(&(*i), &(*j)))
					falg = false;//��̹�ˣ�������
		}
		if (falg)//����һ���ͽ���
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
	//����ȫͨͼ
	
	//��ͼԪ������ͼ
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
				//����ͨ��Ԫ��
				if (j > 0) { temp.G[i][j].up = nullptr; }
				if (j < mapDate.MaxH - 1) { temp.G[i][j].down = nullptr; }
				if (i > 0) { temp.G[i][j].left = nullptr; }
				if (i < mapDate.MaxW - 1) { temp.G[i][j].right = nullptr; }
				//�Ͽ�������������
				if(j>1) temp.G[i][j-1].down = nullptr;
				if(j<mapDate.MaxH-2) temp.G[i][j+1].up = nullptr;
				if(i>1) temp.G[i - 1][j].right = nullptr;
				if(i<mapDate.MaxW-2) temp.G[i + 1][j].left = nullptr;
				//�Ͽ���������������
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



