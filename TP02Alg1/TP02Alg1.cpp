#include <iostream>
#include "Loja.h"
#include "Trajeto.h"
#include "Utils.h"
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

void SetValoresEntrada(int* qtdLojas, int* kmMaxMoto, int* qtdDrones, int* custoKmMoto, int* custoKmCaminhao, string leitura)
{
	int posicao = 0;
	int aux = 0;
	for (size_t i = 0; i < leitura.size(); i++)
	{
		if (leitura[i] == ' ' || leitura[i] == '\n') {
			if (aux == 0)
				*qtdLojas = std::stoi(leitura.substr(posicao, i));
			else if (aux == 1)
				*kmMaxMoto = std::stoi(leitura.substr(posicao, i));
			else if (aux == 2)
				*qtdDrones = std::stoi(leitura.substr(posicao, i));
			else if (aux == 3)
				*custoKmMoto = std::stoi(leitura.substr(posicao, i));
			else
				*custoKmCaminhao = std::stoi(leitura.substr(posicao, i));
			posicao = i + 1;
			aux++;
		}
	}
}

void CadastraLojas(vector<Loja*>* lojas, int qtdLojas, FILE* arquivo)
{
	char Linha[100];
	string result;
	for (int i = 0; i < qtdLojas; i++)
	{
		result = fgets(Linha, 100, arquivo);
		if (result.size() == 0)break;
		int primeiroEspaco = result.find(" ");

		Loja* loja = new Loja(i,
			stoi(result.substr(0, primeiroEspaco)),
			stoi(result.substr(primeiroEspaco + 1, result.size())));

		lojas->push_back(loja);
	}
}

int main(int argc, const char* argv[])
{
	int qtdLojas = 0, kmMaxMoto = 0, qtdDrones = 0, custoKmMoto = 0, custoKmCaminhao = 0;
	string result;
	char Linha[100];
	FILE* arquivo = fopen(argv[1], "rt");
	result = fgets(Linha, 100, arquivo);
	SetValoresEntrada(&qtdLojas, &kmMaxMoto, &qtdDrones, &custoKmMoto, &custoKmCaminhao, result);

	vector<Loja*>* lojas = new vector<Loja*>;
	CadastraLojas(lojas, qtdLojas, arquivo);
	for (size_t i = 0; i < qtdLojas; i++)
	{
		lojas->at(i)->SetTrajetos(lojas);
	}
	vector<Ponto>* pontos = new vector<Ponto>;
	Utils::CreateVetorPontos(lojas, pontos);

	vector<Trajeto>* trajetos = new vector<Trajeto>;

	*trajetos = Utils::SelecionaMelhorTrajeto(lojas, pontos);
	Utils::SortTrajetos(trajetos);
	Utils::RemoveMaiorTrajeto(trajetos, pontos);
	Utils::OrdenaCaminho(trajetos, pontos);
	vector<Trajeto> trajetosPorDrone = Utils::GetTrajetosPorDrone(trajetos, qtdDrones);

	Utils::RemoveTrajetoDrone(trajetos, trajetosPorDrone);
	double custoMoto = Utils::GetCustoPorMotos(trajetos, kmMaxMoto, custoKmMoto);
	double custoCaminhao = Utils::GetCustoPorCaminhao(trajetos, kmMaxMoto, custoKmCaminhao);
	fclose(arquivo);
}