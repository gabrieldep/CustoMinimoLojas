#pragma once
#include <vector>
#include "Localizacao.h"
class Cliente;

using namespace std;

class Loja
{
private:
	int identificacao;
	int estoque;
	int qtdClientes;
	Localizacao* localizacao;
	vector<int>* clientes;
public:
	Loja();
	Loja(int identificacao, int estoque, int x, int y);
	~Loja();
	void SetIdentificacao(int identificacao);
	void SetLocalizacao(Localizacao* localizacao);
	void SetEstoque(int estoque);
	int GetIdentificacao();
	Localizacao GetLocalizacao();
	int GetEstoque();
	void SomaEstoque(int i);
	bool AlocarClienteLoja(int idCliente, vector<Cliente*>* clientes);
	int RetornaPosicaoCliente(int idCliente, vector<Cliente*>* clientes);
	void DesalocarClienteLoja(int idCliente);
	void ListarClientesAlocadas();
};

