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

bool Utils::EstaNoVetor(vector<Trajeto>* trajetos, Trajeto atual, int* ponta)
{
	for (size_t i = 0; i < trajetos->size(); i++)
	{
		Trajeto trajetoAuxiliar = trajetos->at(i);
		int atualB = atual.GetLojaB().GetIdentificacao();
		int atualA = atual.GetLojaA().GetIdentificacao();
		int trajetoAuxiliarA = trajetoAuxiliar.GetLojaA().GetIdentificacao();

		if (trajetoAuxiliarA == atualB || trajetoAuxiliarA == atualA) {
			if (atualB == *ponta) {
				for (size_t j = 0; j < trajetos->size(); j++)
				{
					if (atualA == trajetos->at(j).GetLojaB().GetIdentificacao()) {
						return true;
					}
					else {
						*ponta = atualA;
						return false;
					}
				}
			}
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
