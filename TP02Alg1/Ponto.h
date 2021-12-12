#pragma once
class Ponto
{
private:
	int id;
	int quantidade;
public:
	Ponto(int id, int quantidade);
	~Ponto();
	void SetId(int id);
	void SetQuantidade(int quantidade);
	void SomaQuantidade(int quantidade);
	int GetId();
	int GetQuantidade();
};

