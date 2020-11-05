#include "enemyTank.h"

enemyTank::enemyTank()
{
	x = 0; y = 0;
	w = 0;
	y = 0;
	Hp = 1;
	attack = 1;
	dir = cmd::Stop;
	level = 0;
	bulletId = 0;
	available = false;
}
