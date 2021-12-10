#include "Loja.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

Loja::Loja()
{
	this->identificacao = -1;
	this->localizacao = new Localizacao();
}

Loja::Loja(int identificacao, int x, int y)
{
	this->identificacao = identificacao;
	this->localizacao = new Localizacao(x, y);
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

Localizacao Loja::GetLocalizacao()
{
	return *this->localizacao;
}