#pragma once
#include"baseStruct.h"
using namespace std;
class IdCreater
{
public:
	list<int>data;
	IdCreater(int nc);
	int out();
private:
	bool able(int id);
	int numberCate;
};