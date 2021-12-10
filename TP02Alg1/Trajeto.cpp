#include "Trajeto.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

Trajeto::Trajeto()
{
    this->a = new Loja();
    this->b = new Loja();
    this->distancia = 0;
}

Trajeto::Trajeto(Loja* a, Loja* b)
{
    this->a = a;
    this->b = b;
    CalcularDistancia();
    this->distancia = GetDistancia();
}

Trajeto::~Trajeto()
{
}

void Trajeto::CalcularDistancia()
{
    this->distancia = this->a->GetLocalizacao().CalcularDistancia(b->GetLocalizacao());
}

double Trajeto::GetDistancia()
{
    return this->distancia;
}

void Trajeto::SetLojaA(Loja a)
{
    this->a = &a;
}

void Trajeto::SetLojaB(Loja b)
{
    this->b = &b;
}

Loja Trajeto::GetLojaA()
{
    return *a;
}

Loja Trajeto::GetLojaB()
{
    return *b;
}
