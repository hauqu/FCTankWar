#include "bullet.h"

bullet::bullet()
{
	this->x = 0;
	this->y = 0;
	this->w = 0;
	this->h = 0;
	this->cate = objectCate::Bullet;
	id = 0;
	TankId = 0;
	available = false;
	attack = 0;
	dir = cmd::Stop;
}
bullet::bullet(Object* o, cmd d, int a)
{
	dir = d;
	attack = a;
	TankId = o->ID();
	available = true;
	switch (d)
	{
	case cmd::Up:
		this->x = o->x;
		this->y = o->y + o->h;
		break;
	case cmd::Right:
		this->y = o->y;
		this->x = o->x + o->w;
		break;
	case cmd::Down:
		this->x = o->x;
		this->y = o->y - o->h;
		break;
	case cmd::Left:
		this->y = o->y;
		this->x = o->x - o->w;
		break;
	default:
		this->x = o->x;
		this->y = o->y + o->h;
		break;
	}
}
