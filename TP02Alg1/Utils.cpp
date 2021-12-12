#include "Utils.h"
#include "Trajeto.h"
#include "Ponto.h"
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

bool Utils::EstaNoVetor(vector<Trajeto>* trajetos, Trajeto atual, vector<Ponto>* pontos)
{
	int atualB = atual.GetLojaB().GetIdentificacao();
	return pontos->at(atualB).GetQuantidade() > 0;
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

void Utils::UpdatePontosPercorridos(vector<Ponto>* pontos, int ponto1, int ponto2)
{
	pontos->at(ponto1).SomaQuantidade(1);
	pontos->at(ponto2).SomaQuantidade(1);
}

void Utils::CreateVetorPontos(vector<Loja*>* lojas, vector<Ponto>* pontos)
{
	for (size_t i = 0; i < lojas->size(); i++)
	{
		pontos->push_back(*new Ponto(i, 0));
	}
}

Trajeto Utils::GetTrajetoLigarPontas(vector<Ponto>* pontos, vector<Loja*> lojas)
{
	int a = -1;
	int b = -1;
	for (size_t i = 0; i < pontos->size(); i++)
	{
		if (pontos->at(i).GetQuantidade() == 1) {
			if (a == -1)
				a = i;
			else {
				b = i;
				break;
			}
		}
	}
	return *new Trajeto(lojas.at(a), lojas.at(b));
}
