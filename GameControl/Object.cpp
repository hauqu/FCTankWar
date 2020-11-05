#pragma
#include"Object.h"



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
	available = true;


}