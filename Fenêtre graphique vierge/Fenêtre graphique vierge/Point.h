#ifndef _POINT_H
#define _POINT_H

template <typename T> class Point {
public:
	T x;
	T y;

	Point(T, T);
	~Point();

	bool operator==(const Point<int>& pA, const Point<int>& pB) {
		return pA.x == pB.x && pA.y == pB.y;
	}
};

#endif