#pragma once
#include "Loja.h"
#include <vector>
#include <algorithm>
#include <string>
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
	bool Equals(Trajeto t2);
};

