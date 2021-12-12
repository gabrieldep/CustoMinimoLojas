#pragma once
#include "Trajeto.h"
#include "Ponto.h"
#include "Loja.h"
#include <vector>
#include <algorithm>

class Utils
{
public:
	static vector<Trajeto> SortTrajetos(vector<Trajeto>* trajetos);
	static bool MaiorDistancia(Trajeto t1, Trajeto t2);
	static bool EstaNoVetor(vector<Trajeto>* trajetos, Trajeto l1, vector<Ponto>* pontos);
	static void CalcularTodosTrajetos(vector<Loja*>* lojas, vector<Trajeto>* trajetos);
	static void UpdatePontosPercorridos( vector<Ponto>* pontos, int ponto1, int ponto2);
	static void CreateVetorPontos(vector<Loja*>* lojas, vector<Ponto>* pontos);
	static Trajeto GetTrajetoLigarPontas(vector<Ponto>* pontos, vector<Loja*> lojas);
};

