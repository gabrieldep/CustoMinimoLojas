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

bool Trajeto::Equals(Trajeto t2)
{
    int atualA = this->a->GetIdentificacao();
    int atualB = this->b->GetIdentificacao();
    int t2A = t2.GetLojaA().GetIdentificacao();
    int t2B = t2.GetLojaB().GetIdentificacao();

    return (atualA == t2A && atualB == t2B) || (atualB == t2A && atualA == t2B);
}
