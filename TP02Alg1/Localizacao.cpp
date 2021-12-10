#include "Localizacao.h"
#include "Math.h"

Localizacao::Localizacao()
{
	this->x = -1;
	this->y = -1;
}

Localizacao::Localizacao(double x, double y)
{
	this->x = x;
	this->y = y;
}

Localizacao::~Localizacao()
{
}

double Localizacao::CalcularDistancia(Localizacao localizacao)
{
	double xQuadrado = pow(localizacao.GetX() - this->x, 2);
	double yQuadrado = pow(localizacao.GetY() - this->y, 2);
	double teste = sqrt(xQuadrado + yQuadrado);
	return teste;
}

void Localizacao::SetX(double x)
{
	this->x = x;
}

void Localizacao::SetY(double y)
{
	this->y = y;
}

double Localizacao::GetY()
{
	return this->y;
}

double Localizacao::GetX()
{
	return this->x;
}
