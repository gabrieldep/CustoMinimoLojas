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

void Utils::RemoveMaiorTrajeto(vector<Trajeto>* trajetos)
{
	SortTrajetos(trajetos);
	trajetos->pop_back();
}

vector<Trajeto> Utils::SelecionaMelhorTrajeto(vector<Loja*>* lojas)
{
	vector<Trajeto>* trajetos = new vector<Trajeto>;
	Trajeto* trajeto = new Trajeto();
	vector<Ponto>* pontos = new vector<Ponto>;
	CreateVetorPontos(lojas, pontos);

	*trajeto = lojas->at(0)->GetTrajetos().front();
	AdicionaTrajetoAVetor(trajetos, trajeto, pontos);

	int aux = trajeto->GetLojaB().GetIdentificacao();
	while (trajetos->size() < lojas->size() - 1)
	{
		vector<Trajeto> trajetosAuxiliar = lojas->at(aux)->GetTrajetos();
		for (size_t j = 0; j < trajetosAuxiliar.size(); j++)
		{
			*trajeto = trajetosAuxiliar.at(j);
			if (!EstaNoVetor(trajetos, *trajeto, pontos) && pontos->at(aux).GetQuantidade() < 2) {
				aux = trajeto->GetLojaB().GetIdentificacao();
				AdicionaTrajetoAVetor(trajetos, trajeto, pontos);
				break;
			}
		}
	}
	trajetos->push_back(Utils::GetTrajetoLigarPontas(pontos, *lojas));
	return *trajetos;
}

void Utils::AdicionaTrajetoAVetor(vector<Trajeto>* trajetos, Trajeto* trajeto, vector<Ponto>* pontos)
{
	trajetos->push_back(*trajeto);
	UpdatePontosPercorridos(pontos, trajeto->GetLojaA().GetIdentificacao(), trajeto->GetLojaB().GetIdentificacao());
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
