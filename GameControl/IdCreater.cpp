#include "IdCreater.h"

IdCreater::IdCreater(int cn):numberCate(cn)
{
	srand(time(nullptr));

	data.resize(numberCate);
	for (int i = 0; i < data.size(); i++)
	{
		data[i].resize(1, 0);
	}

}

int IdCreater::out(objectCate c)
{
	int r;

	while (true)
	{
		r = rand() % 9998 + 1;
		if (able(r)==true)
			break;
	}

	switch (c)
	{
	case objectCate::playerTank:
		data[(int)objectCate::playerTank].push_back(r);
		break;
	case objectCate::enemyTank:
		data[(int)objectCate::enemyTank].push_back(r);
		break;
	case objectCate::playerBullet:
		data[(int)objectCate::playerBullet].push_back(r);
		break;
	case objectCate::enemyBullet:
		data[(int)objectCate::enemyBullet].push_back(r);
		break;
	case objectCate::space:
		data[(int)objectCate::space].push_back(r);
		break;
	case objectCate::wall:
		data[(int)objectCate::wall].push_back(r);
		break;
	default:
		break;
	}
	return r;

}

bool IdCreater::able(int id)
{
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data[i].size(); i++)
		{
			if (id == data[i][j])
				return false;
		}
	}	
	return true;
	
}
