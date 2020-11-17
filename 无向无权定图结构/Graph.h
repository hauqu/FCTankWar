#pragma once
#include<vector>

using namespace std;
enum class objectCate//物体的几种类型
{
	playerTank = 0, enemyTank, Bullet,
	space, wall, enemyBase, playerBase,
	falg, water, galss, strongWall
};//该类型能够被GameControl分类处理
struct node
{
	int x;
	int y;
	objectCate cate;
	struct node* up;
	struct node* right;
	struct node* down;
	struct node* left;

};
//无权 无向 定图

class Graph {
public:
	vector<vector<node>>G;
	const int K;
	Graph(int w, int h, int mapsize):K(mapsize) //全通图
	{

		G.resize(w);
		for (int i = 0; i < w; i++)
		{
			G[i].resize(h);
		}
		for (int i = 0; i < G.size(); i++)
		{
			for (int j = 0; j < G[i].size(); j++)
			{
				G[i][j] = { i * mapsize,j * mapsize,
					objectCate::space,
					nullptr,nullptr,nullptr,nullptr };
				if (j > 0) { G[i][j].up = &G[i][j - 1]; }
				if (j < h-1) { G[i][j].down = &G[i][j + 1]; }
				if (i > 0) { G[i][j].left = &G[i-1][j]; }
				if (i < w-1) { G[i][j].right = &G[i+1][j]; }
			}
		}


	}

};