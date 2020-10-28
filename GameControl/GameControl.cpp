#include "GameControl.h"

int GameControl::getcmd(char c)
{
	cmd con = cmdCreater::c_to_cmd(c);
	switch (con)
	{
	case cmd::Up:
		p.y += TANK_STEP;
		break;
	case cmd::Right:
		p.x += TANK_STEP;
		break;
	case cmd::Down:
		p.y -= TANK_STEP;
		break;
	case cmd::Left:
		p.x -= TANK_STEP;
		break;
	
	case cmd::Attack:

		break;
	case cmd::Explosion:
		break;
	default:
		break;
	}

	return 0;
}
