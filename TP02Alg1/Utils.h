#pragma once
#include "Trajeto.h"
#include "Loja.h"
#include <vector>
#include <algorithm>

class Utils
{
public:
	static vector<Trajeto> SortTrajetos(vector<Trajeto>* trajetos);
	static bool MaiorDistancia(Trajeto t1, Trajeto t2);
	static bool EstaNoVetor(vector<Trajeto>* trajetos, Trajeto l1);
	static void CalcularTodosTrajetos(vector<Loja*>* lojas, vector<Trajeto>* trajetos);
};

