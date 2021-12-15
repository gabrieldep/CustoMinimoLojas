#include "Loja.h"
#include "Utils.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

Loja::Loja()
{
	this->identificacao = -1;
	this->localizacao = new Localizacao();
	this->trajetos = new vector<Trajeto>;
}

Loja::Loja(int identificacao, int x, int y)
{
	this->identificacao = identificacao;
	this->localizacao = new Localizacao(x, y);
	this->trajetos = new vector<Trajeto>;
}

Loja::~Loja()
{
}

void Loja::SetIdentificacao(int identificacao)
{
	this->identificacao = identificacao;
}

void Loja::SetLocalizacao(Localizacao* localizacao)
{
	this->localizacao = localizacao;
}

int Loja::GetIdentificacao()
{
	return this->identificacao;
}

/// <summary>
/// Calcula a distancia dessa loja com todas as outras lojas e seta as distancias em ordem crescente.
/// </summary>
/// <param name="lojas">Lojas para calcular a distancia.</param>
void Loja::SetTrajetos(vector<Loja*>* lojas)
{
	for (size_t i = 0; i < lojas->size(); i++)
	{
		if (this->identificacao != lojas->at(i)->GetIdentificacao()) {
			this->trajetos->push_back(*new Trajeto(this, lojas->at(i)));
		}
	}
	Utils::SortTrajetos(this->trajetos, true);
}

void Loja::SetTrajetos(vector<Trajeto>* trajetos)
{
	this->trajetos = trajetos;
}

Localizacao Loja::GetLocalizacao()
{
	return *this->localizacao;
}

vector<Trajeto> Loja::GetTrajetos()
{
	return *this->trajetos;
}

/// <summary>
/// Remove ultimo trajeto da lista de trajetos que saem desta loja.
/// </summary>
void Loja::RemoveUltimoTrajeto()
{
	if (this->trajetos->size() > 0)
		this->trajetos->pop_back();
}
