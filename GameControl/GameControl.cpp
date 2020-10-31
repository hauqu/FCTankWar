#include "GameControl.h"

int GameControl::run()
{
	//ִ��˳��
	/*
	
	*/
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
		int w = (*i).x / MAP_W;
		int h = (*i).y / MAP_H; 

		/*
		mapDate.data[w][h]
		��Ԫ��Ϊ�ӵ� ���½�Ԫ��
		������Ҫ��� ���ϣ����ϣ����£�����
		
		*/
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

