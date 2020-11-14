#include"GameControl.h"
#include<conio.h>
#include<graphics.h>
#include<Windows.h>

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

GameControl mainGame;



void loadPicture();
void Draw(GameControl& gc);
int main()
{
	initgraph(640, 480);
	loadPicture();
	//setaspectratio(1, -1);
	setorigin(100, 100);
	mainGame.start(1);
	BeginBatchDraw();

	while (true)
	{
		while (!_kbhit())
		{
			mainGame.run();

			Draw(mainGame);
			FlushBatchDraw();
			Sleep(200);
			cleardevice();
		}
		char c = _getch();
		mainGame.getcmd(c);
	}
	EndBatchDraw();
	closegraph();
	return 0;
}


void Draw(GameControl& gc)
{

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
				(*i).y + (*i).h / 2,
				&p_enemybullet);
		}
	}
	if (!gc.enemys.empty())
	{
		for (auto i = gc.enemys.begin(); i != gc.enemys.end(); i++)
		{
			putimage((*i).x - (*i).w / 2,
				(*i).y - (*i).h / 2,
				&p_enemy);
			circle((*i).x, (*i).y, (*i).w);
		}
	}

	
}



void loadPicture()
{
	loadimage(&p_wall, "p_wall.jpg", 32, 32);
	loadimage(&p_strongwall, "p_strongwall.jpg", 32, 32);
	loadimage(&p_player, "p_player.jpg", 32, 32);
	
	loadimage(&p_tank_w, "tank_w.jpg", 32, 32);
	loadimage(&p_tank_s, "tank_s.jpg", 32, 32);
	loadimage(&p_tank_a, "tank_a.jpg", 32, 32);
	loadimage(&p_tank_d, "tank_d.jpg", 32, 32);

	loadimage(&p_enemy, "p_enemy.jpg", 32, 32);
	loadimage(&p_enemybullet, "p_enemybullet.jpg", 16, 16);
	loadimage(&p_playerbullet, "p_playerbullet.jpg", 16, 16);

}