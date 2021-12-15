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

/// <summary>
/// Calcula distancia entre duas localizações
/// </summary>
/// <param name="localizacao">Segunda localização para calcular a distancia;</param>
/// <returns>Distancia entre as duas localizações;</returns>
double Localizacao::CalcularDistancia(Localizacao localizacao)
{
	return sqrt(pow(localizacao.GetX() - this->x, 2) + pow(localizacao.GetY() - this->y, 2));
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
