#pragma once
#include <vector>
#include "Localizacao.h"
#include "Trajeto.h"
class Trajeto;

using namespace std;

class Loja
{
private:
	int identificacao;
	Localizacao* localizacao;
	vector<Trajeto>* trajetos;
	
public:
	Loja();
	Loja(int identificacao, int x, int y);
	~Loja();
	void SetIdentificacao(int identificacao);
	void SetLocalizacao(Localizacao* localizacao);
	int GetIdentificacao();
	void SetTrajetos(vector<Loja>* lojas);
	void SetTrajetos(vector<Trajeto>* lojas);
	Localizacao GetLocalizacao();
	vector<Trajeto> GetTrajetos();
};

