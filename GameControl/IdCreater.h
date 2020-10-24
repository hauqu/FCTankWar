#pragma once
#include"baseStruct.h"
using namespace std;
class IdCreater
{
public:
	vector<vector<int>>data;
	IdCreater(int cn);
	int out(objectCate c);
private:
	bool able(int id);
	 int numberCate;
};