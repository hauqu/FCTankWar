#include"Graph.h"
#include<graphics.h>
#include<Windows.h>
#include<conio.h>
Graph map(5, 5, 64);
void drawGraph();
int main(int arg,char *arv[])
{

	initgraph(640, 480);
	
	setorigin(40, 40);
	
	
	while (true)
	{
		drawGraph();
		Sleep(1000);
	}
	return 0;

}
void drawGraph()
{
	
	for(int i=0;i<map.G.size();i++)
	{
		for(int j=0;j<map.G[i].size();j++)
		{
			setcolor(RGB(128, 128, 64));
			circle(map.G[i][j].x, map.G[i][j].y,map.K/8);
			rectangle(map.G[i][j].x-map.K/2, map.G[i][j].y - map.K / 2,
				map.G[i][j].x + map.K / 2, map.G[i][j].y + map.K / 2);

			setcolor(GREEN);
			if(map.G[i][j].up!=nullptr)
			{
				line(map.G[i][j].x, map.G[i][j].y,
					map.G[i][j].x, map.G[i][j].y-map.K/2);
			}
			if (map.G[i][j].right != nullptr)
			{
				line(map.G[i][j].x, map.G[i][j].y,
					map.G[i][j].x + map.K / 2, map.G[i][j].y);
			}
			if (map.G[i][j].down != nullptr)
			{
				line(map.G[i][j].x, map.G[i][j].y,
					map.G[i][j].x, map.G[i][j].y + map.K / 2);
			}
			if (map.G[i][j].left != nullptr)
			{
				line(map.G[i][j].x, map.G[i][j].y,
					map.G[i][j].x - map.K / 2, map.G[i][j].y);
			}

		}
		
	}
}