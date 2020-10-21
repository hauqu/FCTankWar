/*
计算两个任意矩形是否碰撞
*/
#include<graphics.h>
#include<conio.h>
#include<cmath>
using namespace std;
struct block
{
	int x;
	int y;
	int w; int h;
	block(int _x,int _y,int _w,int _h):x(_x),y(_y),w(_w),h(_h)
	{}
};
bool collision(block a, block b);
int main()
{
	initgraph(640, 480);
	setorigin(0, 480);
	setaspectratio(1, -1);
	block red(300, 250, 100, 100);
	block blue(100, 100, 40, 40);
	setfillcolor(RED);
	fillrectangle(red.x - (red.w / 2), red.y - (red.h / 2),
		red.x + (red.w / 2), red.y + (red.h / 2));
	setfillcolor(BLUE);
	fillrectangle(blue.x - (blue.w / 2), blue.y - (blue.h / 2),
		blue.x + (blue.w / 2), blue.y + (blue.h / 2));
	while (true)
	{
		setfillcolor(RED);
		fillrectangle(red.x - (red.w / 2), red.y - (red.h / 2),
			red.x + (red.w / 2), red.y + (red.h / 2));
		setfillcolor(BLUE);
		fillrectangle(blue.x - (blue.w / 2), blue.y - (blue.h / 2),
			blue.x + (blue.w / 2), blue.y + (blue.h / 2));
		if (collision(red, blue))
		{
			setfillcolor(YELLOW);
			fillrectangle(red.x - (red.w / 2), red.y - (red.h / 2),
				red.x + (red.w / 2), red.y + (red.h / 2));
			fillrectangle(blue.x - (blue.w / 2), blue.y - (blue.h / 2),
				blue.x + (blue.w / 2), blue.y + (blue.h / 2));
			
		}
		char c = _getch();
		if (c=='w'||c=='W')
		{
			blue.y += 5;
		}
		else 
		if (c == 's' || c == 'S')
		{
			blue.y -= 5;
		}
		else
		if (c == 'a' || c == 'A')
		{
			blue.x -= 5;
		}
		else
		if (c == 'd' || c == 'D')
		{
			blue.x += 5;
		}
		else
			if (c == ' ')
			{
				break;
			}
		
		cleardevice();
		
	}
	closegraph();
	return 0;
}
bool collision(block a, block b)
{
	
	if ((a.x-b.x)* (a.x - b.x)<(a.w/2+b.w/2)* (a.w/2 + b.w/2))
	{
		if ((a.y - b.y) * (a.y - b.y) < (a.h / 2 + b.h / 2) * (a.h / 2 + b.h / 2))
		{
			return true;
		}
	}
	return false;
}