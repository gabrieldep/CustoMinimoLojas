#include "Ponto.h"

Ponto::Ponto(int id, int quantidade)
{
    this->id = id;
    this->quantidade = quantidade;
}

Ponto::~Ponto()
{
}

void Ponto::SetId(int id)
{
    this->id = id;
}

void Ponto::SetQuantidade(int quantidade)
{
    this->quantidade = quantidade;
}

void Ponto::SomaQuantidade(int quantidade)
{
    this->quantidade += quantidade;
}

int Ponto::GetId()
{
    return this->id;
}

int Ponto::GetQuantidade()
{
    return this->quantidade;
}


/// <summary>
/// Cria a lista de pontos para fazer o controle da quantidade de vertices que ja estão na árvore.
/// </summary>
/// <param name="lojas">Lista com as lojas para fazer o controle</param>
/// <returns></returns>
vector<Ponto> Ponto::CreateVetorPontos(vector<Loja*>* lojas)
{
    vector<Ponto>* pontos = new vector<Ponto>;
    for (size_t i = 0; i < lojas->size(); i++)
    {
        pontos->push_back(*new Ponto(i, 0));
    }
    return *pontos;
}
