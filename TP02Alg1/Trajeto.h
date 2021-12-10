#pragma once
#include "Loja.h"
class Loja;

class Trajeto
{
private:
	Loja* a;
	Loja* b;
	double distancia;
public:
	Trajeto();
	Trajeto(Loja* a, Loja* b);
	~Trajeto();
	void CalcularDistancia();
	double GetDistancia();
	void SetLojaA(Loja a);
	void SetLojaB(Loja b);
	Loja GetLojaA();
	Loja GetLojaB();
};

