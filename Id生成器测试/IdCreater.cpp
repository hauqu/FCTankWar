#include "IdCreater.h"

IdCreater::IdCreater(int nc):numberCate(nc)
{
	srand(time(nullptr));
	data.push_back(0);

}

int IdCreater::out()
{
	int r;

	while (true)
	{
		r = rand() % numberCate-1 + 1;
		if (able(r)==true)
			break;
	}
	data.push_back(r);
	return r;

}

bool IdCreater::able(int id)
{
	for (auto i = data.begin(); i != data.end(); i++)
	{
		if (*i == id) return false;
	}
	return true;
	
}
