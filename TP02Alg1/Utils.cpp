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

void Utils::RemoveMaiorTrajeto(vector<Trajeto>* trajetos, vector<Ponto>* pontos)
{
	SortTrajetos(trajetos);
	Trajeto trajetoAux = trajetos->back();
	pontos->at(trajetoAux.GetLojaA().GetIdentificacao()).SomaQuantidade(-1);
	pontos->at(trajetoAux.GetLojaB().GetIdentificacao()).SomaQuantidade(-1);
	trajetos->pop_back();
}

vector<Trajeto> Utils::SelecionaMelhorTrajeto(vector<Loja*>* lojas, vector<Ponto>* pontos, Trajeto* menorTrajeto)
{
	vector<Trajeto>* trajetos = new vector<Trajeto>;
	Trajeto* trajeto = new Trajeto();
	int pontoInicial = menorTrajeto->GetLojaA().GetIdentificacao();

	*trajeto = lojas->at(pontoInicial)->GetTrajetos().front();
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
	*trajeto = Utils::GetTrajetoLigarPontas(pontos, *lojas);
	AdicionaTrajetoAVetor(trajetos, trajeto, pontos);

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

vector<Ponto> Utils::CreateVetorPontos(vector<Loja*>* lojas)
{
	vector<Ponto>* pontos = new vector<Ponto>;
	for (size_t i = 0; i < lojas->size(); i++)
	{
		pontos->push_back(*new Ponto(i, 0));
	}
	return *pontos;
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

vector<Trajeto> Utils::GetTrajetosPorDrone(vector<Trajeto>* trajetos, int qtdDrones)
{
	vector<vector<Trajeto>>* opcoesDeTrajetos = new vector<vector<Trajeto>>;
	vector<Trajeto> auxiliar = vector<Trajeto>();

	for (size_t j = 0; j < trajetos->size(); j++)
	{
		auxiliar = vector<Trajeto>();
		for (size_t y = j; y < j + qtdDrones - 1; y++)
		{
			try {
				auxiliar.push_back(trajetos->at(y));
			}
			catch (exception) {
				break;
			}
		}
		opcoesDeTrajetos->push_back(auxiliar);
	}

	vector<Trajeto> somaMax = vector<Trajeto>();
	double valorSomaMax = 0.0;
	for (size_t i = 0; i < opcoesDeTrajetos->size(); i++)
	{
		double somaAtual = SomarTamanhoTrajetos(opcoesDeTrajetos->at(i));
		if (somaAtual > valorSomaMax) {
			valorSomaMax = somaAtual;
			somaMax = opcoesDeTrajetos->at(i);
		}
	}

	return somaMax;
}

double Utils::GetCustoPorMotos(vector<Trajeto>* trajetos, int kmMaxMoto, int custoKmMoto)
{
	double custoTotalMoto = 0.0;
	for (size_t i = 0; i < trajetos->size(); i++)
	{
		if (trajetos->at(i).GetDistancia() <= kmMaxMoto)
			custoTotalMoto += trajetos->at(i).GetDistancia() * custoKmMoto;
	}
	return custoTotalMoto;
}

double Utils::GetCustoPorCaminhao(vector<Trajeto>* trajetos, int kmMaxMoto, int custoKmCaminhao)
{
	double custoTotalCaminhao = 0.0;
	for (size_t i = 0; i < trajetos->size(); i++)
	{
		if (trajetos->at(i).GetDistancia() > kmMaxMoto)
			custoTotalCaminhao += trajetos->at(i).GetDistancia() * custoKmCaminhao;
	}
	return custoTotalCaminhao;
}

void Utils::OrdenaCaminho(vector<Trajeto>* trajetos, vector<Ponto>* pontos)
{
	vector<Trajeto>* trajetosOrdenados = new vector<Trajeto>;
	Trajeto* trajeto = new Trajeto();
	int verticeAtual = -1;
	int pontoA = -1;
	int pontoB = -1;
	int lastPontoA = -1, lastPontoB = -1;
	for (size_t i = 0; i < pontos->size(); i++)
	{
		if (pontos->at(i).GetQuantidade() == 1) {
			verticeAtual = i;
			break;
		}
	}

	for (size_t j = 0; j < pontos->size(); j++)
	{
		for (size_t i = 0; i < trajetos->size(); i++)
		{
			trajeto = &trajetos->at(i);
			pontoA = trajetos->at(i).GetLojaA().GetIdentificacao();
			pontoB = trajetos->at(i).GetLojaB().GetIdentificacao();
			if ((verticeAtual == pontoA
				|| verticeAtual == pontoB) && (lastPontoA != pontoA || lastPontoB != pontoB)) {
				trajetosOrdenados->push_back(*trajeto);
				break;
			}
		}
		lastPontoA = pontoA;
		lastPontoB = pontoB;
		verticeAtual = verticeAtual == pontoA ? pontoB : pontoA;
	}
	*trajetos = *trajetosOrdenados;
}

double Utils::SomarTamanhoTrajetos(vector<Trajeto> trajetos)
{
	double aux = 0.0;
	for (size_t i = 0; i < trajetos.size(); i++)
	{
		aux += trajetos.at(i).GetDistancia();
	}
	return aux;
}

void Utils::RemoveTrajetoDrone(vector<Trajeto>* trajetos, int qtdDrones)
{
	vector<Trajeto> trajetosPorDrone = vector<Trajeto>();
	trajetosPorDrone = GetTrajetosPorDrone(trajetos, qtdDrones);

	for (size_t i = 0; i < trajetos->size(); i++)
	{
		for (size_t j = 0; j < trajetosPorDrone.size(); j++)
		{
			if (trajetos->at(i).Equals(trajetosPorDrone.at(j))) {
				trajetos->erase(trajetos->begin() + i);
				i--;
				break;
			}
		}
	}
}
