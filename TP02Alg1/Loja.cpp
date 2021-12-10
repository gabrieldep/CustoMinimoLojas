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
	delete this->localizacao;
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

void Loja::SetTrajetos(vector<Loja*>* lojas)
{
	for (size_t i = 0; i < lojas->size(); i++)
	{
		if (this->identificacao != lojas->at(i)->GetIdentificacao()) {
			this->trajetos->push_back(*new Trajeto(this, lojas->at(i)));
		}
	}
	Utils::SortTrajetos(this->trajetos);
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
