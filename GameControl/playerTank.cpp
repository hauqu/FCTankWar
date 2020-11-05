#include "playerTank.h"

playerTank::playerTank()
{
	x = 0; y = 0;
	w = 0;
	y = 0;
	Hp = 1;
	attack = 1;
	dir = cmd::Stop;
	level = 1;
	bulletId = 0;
	available = false;
}
