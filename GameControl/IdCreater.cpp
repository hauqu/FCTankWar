#include "IdCreater.h"

IdCreater::IdCreater()
{
	this->id = 0;
}

int IdCreater::out()
{
	id++;
	return id;

}


