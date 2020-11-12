#include"GameControl.h"
#include<conio.h>
#include<graphics.h>
#include<Windows.h>
GameControl mainGame;
void Draw(GameControl& gc);
int main()
{
	initgraph(640, 480);
	setaspectratio(1, -1);
	setorigin(120, 400);
	mainGame.start(1);
	while (true)
	{
		while (!_kbhit())
		{
			mainGame.run();

			Draw(mainGame);
			Sleep(200);
			cleardevice();
		}
		char c = _getch();
		mainGame.getcmd(c);
	}
	return 0;
}


void Draw(GameControl& gc)
{
	
	//»æÖÆµØÍ¼ÔªËØ
	setfillcolor(RGB(128, 128, 64));
	for (int i = 0; i < gc.mapDate.data.size(); i++)
	{
		for (int j = 0; j < gc.mapDate.data[i].size(); j++)
		{
			
			switch(gc.mapDate.data[i][j].cate)
			{
			case objectCate::space :
				//do nothing
				
				break;
			case objectCate::wall:
				setfillcolor(RGB(128, 128, 64));
				fillrectangle(
					gc.mapDate.data[i][j].x - gc.mapDate.data[i][j].w / 2,
					gc.mapDate.data[i][j].y + gc.mapDate.data[i][j].h / 2,
					gc.mapDate.data[i][j].x + gc.mapDate.data[i][j].w / 2,
					gc.mapDate.data[i][j].y - gc.mapDate.data[i][j].h / 2
				);
			case objectCate::enemyBase:
			case objectCate::playerBase:
				setfillcolor(BLUE);
				fillrectangle(
					gc.mapDate.data[i][j].x - gc.mapDate.data[i][j].w / 2,
					gc.mapDate.data[i][j].y + gc.mapDate.data[i][j].h / 2,
					gc.mapDate.data[i][j].x + gc.mapDate.data[i][j].w / 2,
					gc.mapDate.data[i][j].y - gc.mapDate.data[i][j].h / 2
				);
				break;
			case objectCate::strongWall:
				setfillcolor(RGB(128, 128, 64));
				fillrectangle(
					gc.mapDate.data[i][j].x - gc.mapDate.data[i][j].w / 2,
					gc.mapDate.data[i][j].y + gc.mapDate.data[i][j].h / 2,
					gc.mapDate.data[i][j].x + gc.mapDate.data[i][j].w / 2,
					gc.mapDate.data[i][j].y - gc.mapDate.data[i][j].h / 2
				);
				break;
			}
		}
	}

	for (auto i = gc.enemys.begin(); i != gc.enemys.end(); i++)
	{
		setfillcolor(YELLOW);
		fillrectangle((*i).x - (*i).w / 2, (*i).y + (*i).h / 2,
			(*i).x + (*i).w / 2, (*i).y - (*i).h / 2);
	}
	for (auto i = gc.enemybullets.begin(); i !=gc.enemybullets.end(); i++)
	{
		setfillcolor(YELLOW);
		fillrectangle((*i).x - (*i).w / 2, (*i).y + (*i).h / 2,
			(*i).x + (*i).w / 2, (*i).y - (*i).h / 2);
	}
	for (auto i = gc.playerbullets.begin(); i != gc.playerbullets.end(); i++)
	{
		setfillcolor(RED);
		fillrectangle((*i).x - (*i).w / 2, (*i).y + (*i).h / 2,
			(*i).x + (*i).w / 2, (*i).y - (*i).h / 2);
	}
	setfillcolor(RED);
	fillrectangle(gc.p.x - gc.p.w / 2, gc.p.y + gc.p.h / 2,
		gc.p.x + gc.p.w / 2, gc.p.y - gc.p.h / 2);
	circle(gc.p.x - gc.p.w / 2, gc.p.y + gc.p.h / 2, 10);
	circle(gc.p.x + gc.p.w / 2, gc.p.y - gc.p.h / 2, 20);

}