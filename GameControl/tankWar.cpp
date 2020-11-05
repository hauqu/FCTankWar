#include"GameControl.h"
#include<conio.h>
#include<graphics.h>
GameControl mainGame;
void Draw(GameControl &gc);
int main()
{
	mainGame.start(1);
	while (true)
	{
		while (!_kbhit())
		{
			mainGame.run();
			Draw(mainGame);
			_sleep(200);
		}
		char c = _getch();
		mainGame.getcmd(c);
	}
	return 0;
}


void Draw(GameControl& gc)
{

}