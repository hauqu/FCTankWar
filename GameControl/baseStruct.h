#pragma once
//在此处包含所有必要的头文件
#include<vector>//map 类 存储信息使用
#include<ctime>//随机数种子
#include<string>//map类文件处理
#include<list>//gameControl 管理 tank相关对象
#include<fstream>//map类文件处理
#include<deque>//存储指令序列

using namespace std;

enum class objectCate//物体的几种类型
{
	playerTank=0, enemyTank, Bullet,
	space, wall,enemyBase,playerBase,
	falg,water,grass,strongWall
};//该类型能够被GameControl分类处理
enum class cmd//基础指令
{
	NA = 0,//无效
	Up, Right, Down, Left, Stop,//移动 上 右 下 左
	Attack,//攻击指令
	Explosion,//自爆
};//GameControl 会读取enemyTank的指令队列并执行相关操作

const int baseCmdCateNumber = 8;//基础指令的种类个数
enum class Aicmd
{
	random,//随机
	stay,//出基地后静止
	gotoxy,//前往x，y
	BFS,//广度优先搜索
	DFS,//深度优先搜索

};//复杂指令，如寻找，围堵，可被拆分为基础指令
//具体的指令由指令生成器生成


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
	int K;//k 用于生成对应坐标
	Graph(int w, int h, int mapsize) :K(mapsize) //全通图
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
				if (j < h - 1) { G[i][j].down = &G[i][j + 1]; }
				if (i > 0) { G[i][j].left = &G[i - 1][j]; }
				if (i < w - 1) { G[i][j].right = &G[i + 1][j]; }
			}
		}


	}
	Graph():K(0)
	{
		
	}

};
