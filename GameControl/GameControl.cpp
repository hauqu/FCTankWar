#include "GameControl.h"
//�������ڻ��ң���Ҫ���¼����๹�캯��


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
	//���b  ��ײ
	for (list<bullet>::iterator i = playerbullets.begin(); i != playerbullets.end(); i++)
	{
		for (auto j = enemys.begin(); j != enemys.end(); i++)
		{
			if (collision(&(*i), &(*j)))
			{
				//��������ӵ������
				(*i).available = false;//�ӵ�ʧЧ
				(*j).Hp -= (*i).attack;//����Ѫ��
				if ((*j).Hp <= 0)//����
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
			if (mapDate.data[i][j].cate == objectCate::space) 
			{
				mapDate.data[i][j].x =-100;
				mapDate.data[i][j].y = -100;
			}
			else {
				mapDate.data[i][j].x = i * MAPOBJECT_W;
				mapDate.data[i][j].y = j * MAPOBJECT_H;
			}
			//��Ա cate �Ѿ���map �����ʼ��
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
	//�ӵ��ƶ�ǰ������ײ��
	//���ƶ�������

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
	//������ɾ��֮����Ч����Ҫɾ��ǰ����


	auto i = playerbullets.begin();
	while (i != playerbullets.end())
	{
		if ((*i).available == false)
			playerbullets.erase(i++);//ɾ����ǰλ�ò�����
		else i++;
	}//����ӵ�
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




/*
int GameControl::run()
{
	//ִ��˳��
	
	//p  b move
	for (list<bullet>::iterator i = playerbullets.begin(); i !=playerbullets.end(); i++)
		bullet_move(&(*i), (*i).dir);
	//e b move
	for (auto i = enemybullets.begin(); i !=enemybullets.end(); i++)
		bullet_move(&(*i), (*i).dir);
	
	//���b  ��ײ
	for (list<bullet>::iterator i = playerbullets.begin(); i != playerbullets.end(); i++)
	{
		for (auto j = enemys.begin(); j != enemys.end(); i++)
		{
			if((*i).collision(*j))
			{
				//��������ӵ������
				(*i).available = false;//�ӵ�ʧЧ
				(*j).Hp -= (*i).attack;//����Ѫ��
				if ((*j).Hp<=0)//����
					(*j).available = false;
			}
		}
		//��� b t

		/*
		���� һ���������ͼ��˵�����������x��y
		�ܹ�����ȷ��һ����Χ��
		���ٱȽϴ���
		x/mapW
		y/mapH
		ȷ����һ��Ԫ��
		//to do �Կռ任ʱ�䣬���ִ��Ч��
		10.30

		*/
/*
		int w = (*i).x / MAP_W;
		int h = (*i).y / MAP_H; 

		/*
		mapDate.data[w][h]
		��Ԫ��Ϊ�ӵ� ���½�Ԫ��
		������Ҫ��� ���ϣ����ϣ����£�����
		
		*/
/*
		//���ȼ����ײԪ��
		w++; h++;
		switch (mapDate.data[w][h].cate)
		{
		case objectCate::water:
		case objectCate::space:
			//ͨ��
			break;
		case objectCate::wall:

			//ͬʱ�ݻ�
			mapDate.data[w][h].cate = objectCate::space;
			(*i).available = false;
			break;
		case objectCate::falg:
		case objectCate::strongWall:
		case objectCate::enemyBase:
			//�ӵ��ݻ�
			(*i).available = false;
			break;
		
		case objectCate::playerBase:
			//�����Լ��Ļ���
			//��Ϸ����
			p.available = false;
			break;
		default:
			break;
		}



	}

	for (list<bullet>::iterator i = enemybullets.begin(); i != playerbullets.end(); i++)
	{
		
		if ((*i).collision(p))//����Ƿ�������
		{
			p.Hp -= (*i).attack;
			if (p.Hp <= 0) p.available = false;
			(*i).available = false;
		}


		int w = (*i).x / MAP_W;
		int h = (*i).y / MAP_H;

		/*
		mapDate.data[w][h]
		��Ԫ��Ϊ�ӵ� ���½�Ԫ��
		������Ҫ��� ���ϣ����ϣ����£�����

		*/
/*		w++; h++;
		switch (mapDate.data[w][h].cate)
		{
		case objectCate::water:
		case objectCate::space:
			//ͨ��
			break;
		case objectCate::wall:

			//ͬʱ�ݻ�
			mapDate.data[w][h].cate = objectCate::space;
			(*i).available = false;
			break;
		case objectCate::falg:
		case objectCate::strongWall:
		case objectCate::enemyBase:
			//�ӵ��ݻ�
			(*i).available = false;
			break;

		case objectCate::playerBase:
			//������ҵĻ���
			//��Ϸ����
			p.available = false;
			break;
		default:
			break;
		}



	}
	

	


	return 1;//ִ�гɹ�
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
	//�ӵ��ƶ�ǰ������ײ��
	//���ƶ�������

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
	//������ɾ��֮����Ч����Ҫɾ��ǰ����


	auto i = playerbullets.begin();
	while (i != playerbullets.end())
	{
		if ((*i).available == false)
			playerbullets.erase(i++);//ɾ����ǰλ�ò�����
		else i++;
	}//����ӵ�
	auto it = enemybullets.begin();
	while (it!=enemybullets.end())
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

void GameControl::initMap()
{
	//����date�Ĵ洢�ṹ��ȷ�����λ��
	//�Ե�ͼԪ�س�������������
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
			//��Ա cate �Ѿ���map �����ʼ��
		}
	}
}

*/