#include "Utils.h"
#include "Trajeto.h"
#include "Ponto.h"
#include <vector>
#include <algorithm>

vector<Trajeto> Utils::SortTrajetos(vector<Trajeto>* trajetos, bool crescente)
{
	sort(trajetos->begin(), trajetos->end(), crescente ? MaiorDistancia : MenorDistancia);
	return *trajetos;
}

bool Utils::MaiorDistancia(Trajeto t1, Trajeto t2)
{
	return t1.GetDistancia() > t2.GetDistancia();
}

bool Utils::MenorDistancia(Trajeto t1, Trajeto t2)
{
	return t1.GetDistancia() < t2.GetDistancia();
}


bool Utils::EstaNoVetor(vector<Trajeto> atual, vector<Ponto>* pontos)
{
	for (size_t i = 0; i < atual.size(); i++)
	{
		int atualB = atual.at(i).GetLojaB().GetIdentificacao();
		if (pontos->at(atualB).GetQuantidade() == 0)
			return true;
	}
	return false;
}

void Utils::RemoveMaiorTrajeto(vector<Trajeto>* trajetos, vector<Ponto>* pontos)
{
	SortTrajetos(trajetos, true);
	Trajeto trajetoAux = trajetos->back();
	pontos->at(trajetoAux.GetLojaA().GetIdentificacao()).SomaQuantidade(-1);
	pontos->at(trajetoAux.GetLojaB().GetIdentificacao()).SomaQuantidade(-1);
	trajetos->pop_back();
}

/// <summary>
/// Algoritimo para calcular a árvore mínima geradora.
/// </summary>
/// <param name="lojas">Lijas que representam os vértices de cada grafo.</param>
/// <param name="pontos">Lista de pontos para fazer o controle.</param>
/// <param name="menorTrajeto">Menor vértice do grafo- Ponto de partida da árvore minima geradora</param>
/// <returns>Lista com os trajetos que formam a ávore mínima geradora.</returns>
vector<Trajeto> Utils::SelecionaMelhorTrajeto(vector<Loja*>* lojas, vector<Ponto>* pontos, Trajeto* menorTrajeto)
{
	vector<Trajeto>* trajetos = new vector<Trajeto>;
	Trajeto trajetoMinimo = Trajeto();
	Trajeto a = Trajeto();
	Trajeto b = Trajeto();
	AdicionaTrajetoAVetor(trajetos, menorTrajeto, pontos);

	while (trajetos->size() < lojas->size() - 1)
	{
		for (size_t j = 0; j < trajetos->size(); j++)
		{
			a = trajetos->at(j).GetLojaA().GetTrajetos().size() == 0 ? a : trajetos->at(j).GetLojaA().GetTrajetos().back();
			b = trajetos->at(j).GetLojaB().GetTrajetos().size() == 0 ? b : trajetos->at(j).GetLojaB().GetTrajetos().back();

			while (pontos->at(a.GetLojaB().GetIdentificacao()).GetQuantidade() > 0) {
				trajetos->at(j).GetLojaA().RemoveUltimoTrajeto();
				a = trajetos->at(j).GetLojaA().GetTrajetos().size() == 0 ? a : trajetos->at(j).GetLojaA().GetTrajetos().back();
			}
			while (pontos->at(b.GetLojaB().GetIdentificacao()).GetQuantidade() > 0) {
				trajetos->at(j).GetLojaB().RemoveUltimoTrajeto();
				b = trajetos->at(j).GetLojaB().GetTrajetos().size() == 0 ? b : trajetos->at(j).GetLojaB().GetTrajetos().back();
			}
			trajetoMinimo = a.GetDistancia() < b.GetDistancia() ? a : b;
		}
		AdicionaTrajetoAVetor(trajetos, &trajetoMinimo, pontos);
	}
	return *trajetos;
}

/// <summary>
/// Adiciona determinado trajeto a uma lista de trajetos e faz o controle na lista de pontos.
/// </summary>
/// <param name="trajetos">Lista de trajetos onde o trajeto sera adicionado.</param>
/// <param name="trajeto">Trajeto a ser adicionado.</param>
/// <param name="pontos">Lista de pontos para fazer o controle.</param>
void Utils::AdicionaTrajetoAVetor(vector<Trajeto>* trajetos, Trajeto* trajeto, vector<Ponto>* pontos)
{
	trajetos->push_back(*trajeto);
	UpdatePontosPercorridos(pontos, *trajeto);
}

/// <summary>
/// Calcula todas as possibilidades de caminho entre todas as lojas- sem repetição [(n * (n -1)) / 2!]
/// </summary>
/// <param name="lojas"></param>
/// <param name="trajetos"></param>
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

/// <summary>
/// Adiciona vertices de um trajeto à lista de controle.
/// </summary>
/// <param name="pontos">Lista de controle.</param>
/// <param name="trajeto">Trajeto para adicionar os vertices.</param>
void Utils::UpdatePontosPercorridos(vector<Ponto>* pontos, Trajeto trajeto)
{
	pontos->at(trajeto.GetLojaA().GetIdentificacao()).SomaQuantidade(1);
	pontos->at(trajeto.GetLojaB().GetIdentificacao()).SomaQuantidade(1);
}

/// <summary>
/// Cria a lista de pontos para fazer o controle da quantidade de vertices que ja estão na árvore.
/// </summary>
/// <param name="lojas">Lista com as lojas para fazer o controle</param>
/// <returns></returns>
vector<Ponto> Utils::CreateVetorPontos(vector<Loja*>* lojas)
{
	vector<Ponto>* pontos = new vector<Ponto>;
	for (size_t i = 0; i < lojas->size(); i++)
	{
		pontos->push_back(*new Ponto(i, 0));
	}
	return *pontos;
}

/// <summary>
/// Get em todos os trajetos que serão realizados por drone.
/// </summary>
/// <param name="trajetos">Lista com os trajetos a serem percorridos.</param>
/// <param name="qtdDrones">Quantidade de drones disponiveis para fazer o trajeto.</param>
/// <returns>Lista com os trajetos que serão realizados por drone.</returns>
vector<Trajeto> Utils::GetTrajetosPorDrone(vector<Trajeto> trajetos, int qtdDrones)
{
	Utils::SortTrajetos(&trajetos, false);

	vector<Trajeto> trajetosDrone = vector<Trajeto>();
	for (size_t i = 0; i < qtdDrones - 1; i++)
	{
		trajetosDrone.push_back(trajetos.back());
		trajetos.pop_back();
	}

	return trajetosDrone;
}

/// <summary>
/// Faz o cálculo de quanto será gasto com motor para realizar o trajeto.
/// </summary>
/// <param name="trajetos">Lista com os trajetos a serem percorridos.</param>
/// <param name="kmMaxMoto">Quilometragem maxima que um trajeto pode ser feito por moto.</param>
/// <param name="custoKmCaminhao">Custo por quilometro percorrido de moto.</param>
/// <returns>Valor total gasto com motos</returns>
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

/// <summary>
/// Faz o cálculo de quanto será gasto com caminhões para realizar o trajeto.
/// </summary>
/// <param name="trajetos">Lista com os trajetos a serem percorridos.</param>
/// <param name="kmMaxMoto">Quilometragem maxima que um trajeto pode ser feito por moto.</param>
/// <param name="custoKmCaminhao">Custo por quilometro percorrido de caminhão.</param>
/// <returns>Valor total gasto com caminhões</returns>
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

/// <summary>
/// Remove os trajetos que serão feitos por drone do cálculo do custo
/// </summary>
/// <param name="trajetos">Lista com os trajetos a serem percorridos.</param>
/// <param name="qtdDrones">Quantidade de drones disponíveis</param>
void Utils::RemoveTrajetoDrone(vector<Trajeto>* trajetos, int qtdDrones)
{
	vector<Trajeto> trajetosPorDrone = vector<Trajeto>();
	trajetosPorDrone = GetTrajetosPorDrone(*trajetos, qtdDrones);

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

/// <summary>
/// Setta os trajetos e suas distancias a partir de cada loja.
/// </summary>
/// <param name="lojas">Lista de lojas para fazer o cálculo de distancia.</param>
void Utils::SetarTrajetosPorLoja(vector<Loja*> lojas)
{
	for (size_t i = 0; i < lojas.size(); i++)
	{
		lojas.at(i)->SetTrajetos(&lojas);
	}
}

