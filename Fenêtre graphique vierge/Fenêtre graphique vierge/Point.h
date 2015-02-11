#pragma once
class Point
{
public:
	int _x;
	int _y;

	Point();
	Point(int, int);
	~Point();
	int operator==(const Point &p) const;
	Point &operator=(const Point &p);
};

