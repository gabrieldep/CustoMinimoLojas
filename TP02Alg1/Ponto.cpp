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
