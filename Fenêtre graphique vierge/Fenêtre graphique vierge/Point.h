#ifndef _POINT_H
#define _POINT_H

template <typename T> class MPoint {
public:
	T x;
	T y;

	MPoint();
	MPoint(T, T);
	~MPoint();
};

class Point {
public:
	int _x;
	int _y;

	Point();
	Point(int, int);
	~Point();

	int operator==(const Point &p) const;
	Point &operator=(const Point &p);
};

#endif
