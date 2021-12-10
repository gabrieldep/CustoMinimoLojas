#include "Localizacao.h"
#include "Math.h"

Localizacao::Localizacao()
{
	this->x = -1;
	this->y = -1;
}

Localizacao::Localizacao(int x, int y)
{
	this->x = x;
	this->y = y;
}

Localizacao::~Localizacao()
{
}

int Localizacao::CalcularDistancia(Localizacao localizacao)
{
	double distanciaEixoX = fabs((double)localizacao.GetX() - (double)this->x);
	double distanciaEixoY = fabs((double)localizacao.GetY() - (double)this->y);

	int maiorLado = fmax(distanciaEixoX, distanciaEixoY);

	return maiorLado - 1;
}

void Localizacao::SetX(int x)
{
	this->x = x;
}

void Localizacao::SetY(int y)
{
	this->y = y;
}

int Localizacao::GetY()
{
	return this->y;
}

int Localizacao::GetX()
{
	return this->x;
}
