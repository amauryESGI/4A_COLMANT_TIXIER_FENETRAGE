#include "RemplissageLCA.h"

RemplissageLCA::RemplissageLCA(const int w, const int h) {
	_width = w;
	_height = h;
}


RemplissageLCA::~RemplissageLCA() {
}

void RemplissageLCA::Remplir(vector<MPoint<int>> v) {
	vector<vector<int>> lca(_height);

	for (int i = 0; i < _height; i++) {
		lca[i].push_back(0);
		lca[i].push_back(_width);
	}

	for (vector<MPoint<int>>::iterator itV = v.begin(); itV != v.end(); ++itV) {
		MPoint<int> pA = *itV;
		MPoint<int> pB = (itV + 1) == v.end() ? v[0] : *(itV + 1);

		if (pA.y == pB.y) {
			lca[pA.y].push_back(pA.x);
			lca[pB.y].push_back(pB.x);
		} else {
			map<int, MPoint<int>> segment = allPoint(pA, pB);

			for (map<int, MPoint<int>>::iterator itM = segment.begin(); itM != segment.end(); ++itM) {
				lca[(*itM).first].push_back((*itM).second.x);
			}
		}

		for (int y = 0; y < lca.size; ++y) {
			if (lca[y].size % 2)
				continue;

			sort(lca[y].begin(), lca[y].end(), myobject);

			for (int j = 0; j < lca[y].size - 1; ++j) {
				if (lca[y][j] % 2) {
					for (int x = lca[y][j]; x <= lca[y][j + 1]; x++) {
						glBegin(GL_POINTS);
						glVertex2f(x, y);
						glEnd();
					}
				}
			}
		}
	}


}

float RemplissageLCA::coefDir(MPoint<int> pA, MPoint<int> pB) {
	return (pB.y - pA.y) / (pB.x - pA.x);
}

map<int, MPoint<int>> RemplissageLCA::allPoint(MPoint<int> pA, MPoint<int> pB) {
	map<int, MPoint<int>> retour;

	int i, check, size;
	if (pA.y < pB.y) {
		i = pA.y;
		check = pB.y;
		size = pB.y - pA.y;
	} else {
		i = pB.y;
		check = pA.y;
		size = pA.y - pB.y;
	}

	int m = coefDir(pA, pB);

	retour[pA.y] = pA;
	retour[pB.y] = pB;

	MPoint<float> tmp = pA.y < pB.y
		? MPoint<float>(pA.x / 1, pA.y / 1)
		: MPoint<float>(pB.x / 1, pB.y / 1);

	for (i += 1; i < check; ++i) {
		tmp = MPoint<float>(tmp.x + 1 / m, i);
		retour[i] = MPoint<int>(round(tmp.x), tmp.y);
	}
	return retour;
}

struct myclass {
	bool operator() (int i, int j) { return (i < j); }
} myobject;