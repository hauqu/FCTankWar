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
