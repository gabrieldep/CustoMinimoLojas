#pragma once
#include "Trajeto.h"
#include "Ponto.h"
#include "Loja.h"
#include <vector>
#include <algorithm>

class Utils
{
public:
	static vector<Trajeto> SortTrajetos(vector<Trajeto>* trajetos, bool crescente);
	static bool MaiorDistancia(Trajeto t1, Trajeto t2);
	static bool MenorDistancia(Trajeto t1, Trajeto t2);
	static vector<Trajeto> SelecionaMelhorTrajeto(vector<Loja*>* lojas, vector<Ponto>* pontos);
	static void AdicionaTrajetoAVetor(vector<Trajeto>* trajetos, Trajeto* trajeto, vector<Ponto>* pontos);
	static void UpdatePontosPercorridos(vector<Ponto>* pontos, Trajeto trajeto);
	static vector<Trajeto> GetTrajetosPorDrone(vector<Trajeto> trajetos, int qtdDrones);
	static double GetCustoPorMotos(vector<Trajeto>* trajetos, int kmMaxMoto, int custoKmMoto);
	static double GetCustoPorCaminhao(vector<Trajeto>* trajetos, int kmMaxMoto, int custoKmCaminhao);
	static void RemoveTrajetoDrone(vector<Trajeto>* trajetos, int qtdDrones);
	static void SetarTrajetosPorLoja(vector<Loja*> lojas);
};

