#include"GameControl.h"
#include<conio.h>
#include<graphics.h>
#include<Windows.h>
using namespace std;
//Í¼Æ¬×ÊÔ´
IMAGE p_wall;
IMAGE p_strongwall;
IMAGE p_player;
IMAGE p_playerbullet;
IMAGE p_enemy;
IMAGE p_enemybullet;
IMAGE p_tank_w;
IMAGE p_tank_s;
IMAGE p_tank_a;
IMAGE p_tank_d;
IMAGE p_enemy_w;
IMAGE p_enemy_s;
IMAGE p_enemy_a;
IMAGE p_enemy_d;
IMAGE p_water;
IMAGE p_grass;


IMAGE p_playerbase;
GameControl mainGame;

struct Pos
{
	int x;
	int y;
};

void loadPicture();
void Draw(GameControl& gc);
void Draw_1(GameControl& gc);
void gameOver();
int main()
{
	initgraph(640, 480);
	setaspectratio(0.7, 0.7);
	loadPicture();
	//setaspectratio(1, -1);
	setorigin(16, 16);
	mainGame.start(1);
	BeginBatchDraw();

	while (true)
	{
		while (!_kbhit())
		{
			int  falg= mainGame.run();
			if (falg == 0) 
			{
				goto END;
			}
			Draw(mainGame);
			mainGame.clearDieObject();
			FlushBatchDraw();
			Sleep(100);
			cleardevice();
		}
		char c = _getch();
		mainGame.getcmd(c);
	}
	EndBatchDraw();
	closegraph();


END:
	cleardevice();
	gameOver();
	return 0;
}


void Draw(GameControl& gc)
{
	list<Pos>grasses;

	for (int i = 0; i < gc.mapDate.data.size(); i++)
	{
		for (int j = 0; j < gc.mapDate.data[i].size(); j++)
		{
			
			switch(gc.mapDate.data[i][j].cate)
			{
			case objectCate::wall:
				putimage(gc.mapDate.data[i][j].x
					- gc.mapDate.data[i][j].w / 2,
					gc.mapDate.data[i][j].y
					- gc.mapDate.data[i][j].h / 2,
					&p_wall
				);break;
			case objectCate::strongWall:
				putimage(gc.mapDate.data[i][j].x
					- gc.mapDate.data[i][j].w / 2,
					gc.mapDate.data[i][j].y
					- gc.mapDate.data[i][j].h / 2,
					&p_strongwall
				); break;
			case objectCate::water:
				putimage(gc.mapDate.data[i][j].x
					- gc.mapDate.data[i][j].w / 2,
					gc.mapDate.data[i][j].y
					- gc.mapDate.data[i][j].h / 2,
					&p_water
				); break;
			case objectCate::grass:
				grasses.push_back
				({ gc.mapDate.data[i][j].x,
					gc.mapDate.data[i][j].y });
				
			case objectCate::space:
				/*
				rectangle(gc.mapDate.data[i][j].x
					- gc.mapDate.data[i][j].w / 2,
					gc.mapDate.data[i][j].y
					+ gc.mapDate.data[i][j].h / 2,
					gc.mapDate.data[i][j].x
					+ gc.mapDate.data[i][j].w / 2,
					gc.mapDate.data[i][j].y
					- gc.mapDate.data[i][j].h / 2);
					*/
				break;
			case objectCate::enemyBase:
			case objectCate::playerBase:
				putimage(gc.mapDate.data[i][j].x
					- gc.mapDate.data[i][j].w / 2,
					gc.mapDate.data[i][j].y
					- gc.mapDate.data[i][j].h / 2,
					&p_playerbase
				);
				/*
				fillrectangle(gc.mapDate.data[i][j].x
					- gc.mapDate.data[i][j].w / 2,
					gc.mapDate.data[i][j].y
					+ gc.mapDate.data[i][j].h / 2,
					gc.mapDate.data[i][j].x
					+ gc.mapDate.data[i][j].w / 2,
					gc.mapDate.data[i][j].y
					- gc.mapDate.data[i][j].h / 2);
				*/
				break;
				
			}
			
			//circle(gc.mapDate.data[i][j].x,
				//gc.mapDate.data[i][j].y, 16);
		}
	}

	if(gc.playerbullet!=nullptr)
	{
		putimage(gc.playerbullet->x - (gc.playerbullet->w / 2),
			gc.playerbullet->y - (gc.playerbullet->h / 2),
			&p_playerbullet
		);
		//circle(gc.playerbullet->x, gc.playerbullet->y, 8);
	}
	switch (gc.p.dir)
	{
	case cmd::Up:
		p_player = p_tank_w;
		break;
	case cmd::Down:
		p_player = p_tank_s;
		break;
	case cmd::Right:
		p_player = p_tank_d;
		break;
	case cmd::Left:
		p_player = p_tank_a;
		break;
	default:
		break;
	}
	putimage(gc.p.x - (gc.p.w / 2),
		gc.p.y - (gc.p.h / 2),
		&p_player
	); //circle(gc.p.x, gc.p.y, 16);
	if (!gc.enemybullets.empty())
	{
		for (auto i = gc.enemybullets.begin(); i != gc.enemybullets.end(); i++)
		{
			putimage((*i).x - (*i).w / 2,
				(*i).y - (*i).h / 2,
				&p_enemybullet);
		}
	}
	if (!gc.enemys.empty())
	{
		for (auto i = gc.enemys.begin(); i != gc.enemys.end(); i++)
		{
			switch ((*i).dir)
			{
			case cmd::Up:
				p_enemy = p_enemy_w;
				break;
			case cmd::Down:
				p_enemy = p_enemy_s;
				break;
			case cmd::Right:
				p_enemy = p_enemy_d;
				break;
			case cmd::Left:
				p_enemy = p_enemy_a;
				break;
			default:
				break;
			}

			putimage((*i).x - (*i).w / 2,
				(*i).y - (*i).h / 2,
				&p_enemy);
			//circle((*i).x, (*i).y, (*i).w);
		}
	}

	for (auto i = grasses.begin(); i != grasses.end(); i++)
	{
		putimage(
			(*i).x- gc.mapDate.data[0][0].w / 2,
			(*i).y- gc.mapDate.data[0][0].h / 2,
			&p_grass
		);
	}
}

void Draw_1(GameControl& gc)
{

	for (int i = 0; i < gc.mapDate.data.size(); i++)
	{
		for (int j = 0; j < gc.mapDate.data[i].size(); j++)
		{

			switch (gc.mapDate.data[i][j].cate)
			{
			case objectCate::wall:
				putimage(gc.mapDate.data[i][j].x
					- gc.mapDate.data[i][j].w / 2,
					gc.mapDate.data[i][j].y
					- gc.mapDate.data[i][j].h / 2,
					&p_wall
				); break;
			case objectCate::strongWall:
				putimage(gc.mapDate.data[i][j].x
					- gc.mapDate.data[i][j].w / 2,
					gc.mapDate.data[i][j].y
					- gc.mapDate.data[i][j].h / 2,
					&p_strongwall
				); break;
			case objectCate::space:

				rectangle(gc.mapDate.data[i][j].x
					- gc.mapDate.data[i][j].w / 2,
					gc.mapDate.data[i][j].y
					+ gc.mapDate.data[i][j].h / 2,
					gc.mapDate.data[i][j].x
					+ gc.mapDate.data[i][j].w / 2,
					gc.mapDate.data[i][j].y
					- gc.mapDate.data[i][j].h / 2);
				break;
			case objectCate::enemyBase:
			case objectCate::playerBase:
				fillrectangle(gc.mapDate.data[i][j].x
					- gc.mapDate.data[i][j].w / 2,
					gc.mapDate.data[i][j].y
					+ gc.mapDate.data[i][j].h / 2,
					gc.mapDate.data[i][j].x
					+ gc.mapDate.data[i][j].w / 2,
					gc.mapDate.data[i][j].y
					- gc.mapDate.data[i][j].h / 2);
				break;

			}

			circle(gc.mapDate.data[i][j].x,
				gc.mapDate.data[i][j].y, 16);
		}
	}

	if (gc.playerbullet != nullptr)
	{
		putimage(gc.playerbullet->x - (gc.playerbullet->w / 2),
			gc.playerbullet->y - (gc.playerbullet->h / 2),
			&p_playerbullet
		);
		circle(gc.playerbullet->x, gc.playerbullet->y, 8);
	}
	switch (gc.p.dir)
	{
	case cmd::Up:
		p_player = p_tank_w;
		break;
	case cmd::Down:
		p_player = p_tank_s;
		break;
	case cmd::Right:
		p_player = p_tank_d;
		break;
	case cmd::Left:
		p_player = p_tank_a;
		break;
	default:
		break;
	}
	putimage(gc.p.x - (gc.p.w / 2),
		gc.p.y - (gc.p.h / 2),
		&p_player
	); circle(gc.p.x, gc.p.y, 16);
	if (!gc.enemybullets.empty())
	{
		for (auto i = gc.enemybullets.begin(); i != gc.enemybullets.end(); i++)
		{
			putimage((*i).x - (*i).w / 2,
				(*i).y - (*i).h / 2,
				&p_enemybullet);
		}
	}
	if (!gc.enemys.empty())
	{
		for (auto i = gc.enemys.begin(); i != gc.enemys.end(); i++)
		{
			switch ((*i).dir)
			{
			case cmd::Up:
				p_enemy = p_enemy_w;
				break;
			case cmd::Down:
				p_enemy = p_enemy_s;
				break;
			case cmd::Right:
				p_enemy = p_enemy_d;
				break;
			case cmd::Left:
				p_enemy = p_enemy_a;
				break;
			default:
				break;
			}

			putimage((*i).x - (*i).w / 2,
				(*i).y - (*i).h / 2,
				&p_enemy);
			circle((*i).x, (*i).y, (*i).w);
		}
	}


}

void gameOver()
{
	IMAGE p;
	loadimage(&p,"gameover.jpg",640,480);
	putimage(0, 0, &p);

}




void loadPicture()
{
	loadimage(&p_wall, "p_wall.jpg", 32, 32);
	loadimage(&p_strongwall, "p_strongwall.jpg", 32, 32);
	loadimage(&p_player, "p_player.jpg", 32, 32);
	loadimage(&p_grass, "p_grass.jpg", 32, 32);
	loadimage(&p_water, "p_water.jpg", 32, 32);

	loadimage(&p_tank_w, "tank_w.jpg", 32, 32);
	loadimage(&p_tank_s, "tank_s.jpg", 32, 32);
	loadimage(&p_tank_a, "tank_a.jpg", 32, 32);
	loadimage(&p_tank_d, "tank_d.jpg", 32, 32);

	loadimage(&p_enemy_d, "p_enemy_d.jpg", 32, 32);
	loadimage(&p_enemy_s, "p_enemy_s.jpg", 32, 32);
	loadimage(&p_enemy_a, "p_enemy_a.jpg", 32, 32);
	loadimage(&p_enemy_w, "p_enemy_w.jpg", 32, 32);

	loadimage(&p_enemy, "p_enemy.jpg", 32, 32);
	loadimage(&p_enemybullet, "p_enemybullet.jpg", 16, 16);
	loadimage(&p_playerbullet, "p_playerbullet.jpg", 16, 16);
	loadimage(&p_playerbase, "playerbase.jpg", 32, 32);

}