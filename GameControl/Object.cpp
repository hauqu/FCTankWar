#pragma
#include"Object.h"
inline bool Object::collision(const Object& o) const
{


	if ((x - o.x) * (x - o.x) < (w / 2 + o.w / 2) * (w / 2 + o.w / 2))
	{
		if ((y - o.y) * (y - o.y) < (h / 2 + o.h / 2) * (h / 2 + o.h / 2))
		{
			return true;
		}
	}
}

inline int Object::ID(void) const
{
	return id;
}
Object::Object()
{
	this->x = 0;
	this->y = 0;
	this->w = 0;
	this->h = 0;
	this->cate = objectCate::space;
	id = 0;
	available = false;
}
Object::Object(int x, int y, int w, int h, objectCate oc)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->cate = oc;
	id = 0;
	available = false;


}