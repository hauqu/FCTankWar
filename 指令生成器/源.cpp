#include"cmdMaker.h"
#include<graphics.h>
#include<Windows.h>
/*



*/
class Tank
{
public:
	int x;
	int y;
	deque<cmd>cs;
	Tank()
	{
		x = 200;
		y = 200;
	}
};
cmdMaker m;
Tank t;

int main()
{
	initgraph(640, 480);
	t.cs = m.out(10);
	while (true)
	{
		if (t.cs.empty())
		{
			t.cs = m.out(10);
		}
		cmd c = t.cs.front();
		t.cs.pop_front();
		switch (c)
		{
		case cmd::NA:
			break;
		case cmd::Up:
			t.y += 15;
			break;
		case cmd::Right:
			t.x += 15;
			break;
		case cmd::Down:
			t.y -= 15;
			break;
		case cmd::Left:
			t.x -= 15;
			break;
		case cmd::Stop:
			break;
		case cmd::Attack:
			circle(t.x, t.y, 30);
			
			break;
		case cmd::Explosion:
			fillcircle(t.x, t.y, 30);
			
			break;
		default:
			break;
		}

		fillcircle(t.x, t.y, 20);
		Sleep(200);
		cleardevice();

	}
	closegraph();

	return 0;
}