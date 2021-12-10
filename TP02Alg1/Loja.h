#pragma once
#include <vector>
#include "Localizacao.h"
class Cliente;

using namespace std;

class Loja
{
private:
	int identificacao;
	Localizacao* localizacao;
public:
	Loja();
	Loja(int identificacao, int x, int y);
	~Loja();
	void SetIdentificacao(int identificacao);
	void SetLocalizacao(Localizacao* localizacao);
	int GetIdentificacao();
	Localizacao GetLocalizacao();
};

