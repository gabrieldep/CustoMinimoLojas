#include "Utils.h"
#include "Trajeto.h"
#include <vector>
#include <algorithm>

vector<Trajeto> Utils::SortTrajetos(vector<Trajeto>* trajetos)
{
	sort(trajetos->begin(), trajetos->end(), MenorDistancia);
	return *trajetos;
}

bool Utils::MenorDistancia(Trajeto t1, Trajeto t2)
{
	return t1.GetDistancia() > t2.GetDistancia();
}
