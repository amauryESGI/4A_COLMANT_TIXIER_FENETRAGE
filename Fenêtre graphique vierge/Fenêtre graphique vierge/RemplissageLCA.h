#ifndef _REMPLISSAGE_H
#define _REMPLISSAGE_H

#include "stdafx.h"

using namespace std;

#pragma once
class RemplissageLCA {
public:
	void Remplir(vector<MPoint<int>> v);
	float coefDir(MPoint<int> pA, MPoint<int> pB);

	RemplissageLCA(const int width, const int height);
	~RemplissageLCA();

private:
	int _height;
	int _width;

	map<int, MPoint<int>> allPoint(MPoint<int> pA, MPoint<int> pB);
};

#endif