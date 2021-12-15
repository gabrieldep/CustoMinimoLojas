#include "Trajeto.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

Trajeto::Trajeto()
{
    this->a = new Loja();
    this->b = new Loja();
    this->distancia = INT64_MAX;
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

/// <summary>
/// Calcula distancia entre dois vértices do grafo.
/// </summary>
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

Loja* Trajeto::GetLojaA()
{
    return a;
}

Loja* Trajeto::GetLojaB()
{
    return b;
}

/// <summary>
/// Verifica se dois trajetos representam a mesma aresta do grafo.
/// </summary>
/// <param name="t2">Trajeto a ser comparado com o atual.</param>
/// <returns>True se forem iguais, False caso contrário.</returns>
bool Trajeto::Equals(Trajeto t2)
{
    int atualA = this->a->GetIdentificacao();
    int atualB = this->b->GetIdentificacao();
    int t2A = t2.GetLojaA()->GetIdentificacao();
    int t2B = t2.GetLojaB()->GetIdentificacao();

    return (atualA == t2A && atualB == t2B) || (atualB == t2A && atualA == t2B);
}

Trajeto* Trajeto::GetProximoTrajeto(vector<Trajeto>* trajetos)
{
    return trajetos->size() == 0 ? this : &trajetos->back();
}
