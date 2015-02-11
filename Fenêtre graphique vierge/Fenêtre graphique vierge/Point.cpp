#include "Point.h"


Point::Point()
{
}

Point::Point(int x, int y)
{
	this->_x = x;
	this->_y = y;
}

Point::~Point()
{
}

int Point::operator==(const Point &p) const
{
	if (this->_x != p._x) return 0;
	if (this->_y != p._y) return 0;
	return 1;
}

Point& Point::operator=(const Point &p)
{
	this->_x = p._x;
	this->_y = p._y;

	return *this;
}