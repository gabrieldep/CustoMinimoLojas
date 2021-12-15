#pragma once
#include "Trajeto.h"
#include "Ponto.h"
#include "Loja.h"
#include <vector>
#include <algorithm>

class Utils
{
private:
	vector<Loja*>* lojas;
	vector<Ponto>* pontos;
	vector<Trajeto>* trajetos;
public:
	Utils(vector<Loja*>* lojas);
	~Utils();
	void SelecionaMelhorTrajeto();
	void RemoveTrajetoDrone(int qtdDrones);
	double GetCustoPorMotos(int kmMaxMoto, int custoKmMoto);
	double GetCustoPorCaminhao(int kmMaxMoto, int custoKmCaminhao);
	static vector<Trajeto> SortTrajetos(vector<Trajeto>* trajetos, bool crescente);
	static bool MaiorDistancia(Trajeto t1, Trajeto t2);
	static bool MenorDistancia(Trajeto t1, Trajeto t2);
	static void AdicionaTrajetoAVetor(vector<Trajeto>* trajetos, Trajeto* trajeto, vector<Ponto>* pontos);
	static void UpdatePontosPercorridos(vector<Ponto>* pontos, Trajeto trajeto);
	static vector<Trajeto> GetTrajetosPorDrone(vector<Trajeto> trajetos, int qtdDrones);
};

