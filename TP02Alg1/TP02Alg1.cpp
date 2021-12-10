#include <iostream>
#include "Loja.h"
#include "Trajeto.h"
#include "Utils.cpp"
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
		int segundoEspaco = result.find_last_of(" ");

		lojas->push_back(new Loja(i,
			stoi(result.substr(0, primeiroEspaco)),
			stoi(result.substr(primeiroEspaco + 1, result.size()))));
	}
}

void CalcularTrajetos(vector<Loja*>* lojas, vector<Trajeto*>* trajetos)
{
	for (size_t i = 0; i < lojas->size(); i++)
	{
		for (size_t j = i + 1; j < lojas->size(); j++)
		{
			if (i != j) {
				trajetos->push_back(new Trajeto(lojas->at(i), lojas->at(j)));
			}
		}
	}
}

bool MenorDistancia(Trajeto* t1, Trajeto* t2)
{
	return t1->GetDistancia() > t2->GetDistancia();
}

vector<Trajeto*> SortTrajetos(vector<Trajeto*> trajetos) {
	sort(trajetos.begin(), trajetos.end(), MenorDistancia);
	return trajetos;
}

void SelecionaMelhorTrajeto(vector<Loja*>* lojas) 
{
}

int main(int argc, const char* argv[])
{
	int qtdLojas = 0, kmMaxMoto = 0, qtdDrones = 0, custoKmMoto = 0, custoKmCaminhao = 0;
	string result;
	char Linha[100];
	FILE* arquivo = fopen(argv[1], "rt");
	result = fgets(Linha, 100, arquivo);
	SetValoresEntrada(&qtdLojas, &kmMaxMoto, &qtdDrones, &custoKmMoto, &custoKmCaminhao, result);

	vector<Loja*>* lojas = new std::vector<Loja*>;
	CadastraLojas(lojas, qtdLojas, arquivo);
	for (size_t i = 0; i < qtdLojas; i++)
	{
		lojas->at(i)->SetTrajetos(lojas);
	}

	SelecionaMelhorTrajeto(lojas);

	vector<Trajeto*>* trajetos = new std::vector<Trajeto*>;
	CalcularTrajetos(lojas, trajetos);
	*trajetos = SortTrajetos(*trajetos);
	fclose(arquivo);
}