#include "Utils.h"
#include "Trajeto.h"
#include <vector>
#include <algorithm>

vector<Trajeto> Utils::SortTrajetos(vector<Trajeto>* trajetos)
{
	sort(trajetos->begin(), trajetos->end(), MaiorDistancia);
	return *trajetos;
}

bool Utils::MaiorDistancia(Trajeto t1, Trajeto t2)
{
	return t1.GetDistancia() < t2.GetDistancia();
}

bool Utils::EstaNoVetor(vector<Trajeto>* trajetos, Trajeto l1)
{
	for (size_t i = 0; i < trajetos->size(); i++)
	{
		Trajeto t2 = trajetos->at(i);
		int a1 = t2.GetLojaA().GetIdentificacao();
		int b1 = l1.GetLojaB().GetIdentificacao();
		int b2 = l1.GetLojaA().GetIdentificacao();
		if (a1 == b1 || a1 == b2) {
			return true;
		}
	}
	return false;
}

void Utils::CalcularTodosTrajetos(vector<Loja*>* lojas, vector<Trajeto>* trajetos)
{
	for (size_t i = 0; i < lojas->size(); i++)
	{
		for (size_t j = i + 1; j < lojas->size(); j++)
		{
			if (i != j) {
				trajetos->push_back(*new Trajeto(lojas->at(i), lojas->at(j)));
			}
		}
	}
}
