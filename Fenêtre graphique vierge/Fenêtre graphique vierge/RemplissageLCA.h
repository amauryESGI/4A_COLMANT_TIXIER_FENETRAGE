#include "stdafx.h"

using namespace std;

#pragma once
class RemplissageLCA {
public:
	RemplissageLCA(const int width, const int height);
	~RemplissageLCA();

	void Remplir(vector<Point<int>> v);
	float coefDir(Point<int> pA, Point<int> pB);

private:
	int _height;
	int _width;

	map<int, Point<int>> allPoint(Point<int> pA, Point<int> pB);
};