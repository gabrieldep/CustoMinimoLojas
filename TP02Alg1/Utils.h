#pragma once
#include "Trajeto.h"
#include <vector>
#include <algorithm>

class Utils
{
public:
	static vector<Trajeto> SortTrajetos(vector<Trajeto>* trajetos);
	static bool MenorDistancia(Trajeto t1, Trajeto t2);
};

