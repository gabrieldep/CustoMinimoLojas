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

vector<Trajeto> SelecionaMelhorTrajeto(vector<Loja*>* lojas)
{
	vector<Trajeto>* trajetos = new vector<Trajeto>;
	Trajeto* trajeto = new Trajeto();
	vector<Ponto>* pontos = new vector<Ponto>;
	Utils::CreateVetorPontos(lojas, pontos);
	if (trajetos->size() == 0) {
		*trajeto = lojas->at(0)->GetTrajetos().front();
		trajetos->push_back(*trajeto);
		Utils::UpdatePontosPercorridos(pontos, trajeto->GetLojaA().GetIdentificacao(), trajeto->GetLojaB().GetIdentificacao());
	}
	int aux = trajeto->GetLojaB().GetIdentificacao();
	while(trajetos->size() < lojas->size() - 1)
	{
		vector<Trajeto> trajetosAuxiliar = lojas->at(aux)->GetTrajetos();
		for (size_t j = 0; j < trajetosAuxiliar.size(); j++)
		{
			*trajeto = trajetosAuxiliar.at(j);
			if (!Utils::EstaNoVetor(trajetos, *trajeto, pontos) && pontos->at(aux).GetQuantidade() < 2) {
				trajetos->push_back(*trajeto);
				aux = trajeto->GetLojaB().GetIdentificacao();
				Utils::UpdatePontosPercorridos(pontos, trajeto->GetLojaA().GetIdentificacao(), trajeto->GetLojaB().GetIdentificacao());
				break;
			}
		}
	}
	trajetos->push_back(Utils::GetTrajetoLigarPontas(pontos, *lojas));
	return *trajetos;
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

	vector<Trajeto>* trajetos = new std::vector<Trajeto>;
	vector<Trajeto>* trajetosDrone = new std::vector<Trajeto>;
	vector<Trajeto>* trajetosMoto = new std::vector<Trajeto>;
	vector<Trajeto>* trajetosCaminhao = new std::vector<Trajeto>;

	*trajetos = SelecionaMelhorTrajeto(lojas);
	Utils::SortTrajetos(trajetos);

	Trajeto t = trajetos->back();
	trajetosDrone->push_back(t);
	int trajetoA = t.GetLojaA().GetIdentificacao();
	int trajetoB = t.GetLojaB().GetIdentificacao();
	Trajeto adicionar = Trajeto();
	for (size_t j = 0; j < qtdDrones - 1; j++)
	{
		for (size_t i = 1; i < trajetos->size(); i++)
		{
			Trajeto trajetoAux = trajetos->at(i);
			int a = trajetoAux.GetLojaA().GetIdentificacao();
			int b = trajetoAux.GetLojaB().GetIdentificacao();
			if ((trajetoB == a && trajetoA != b) || (trajetoA == b && trajetoB != a)) {
				adicionar = adicionar.GetDistancia() > trajetoAux.GetDistancia() ? adicionar : (trajetoAux);
			}
		}
		t = adicionar;
		trajetosDrone->push_back(adicionar);
	}

	fclose(arquivo);
}