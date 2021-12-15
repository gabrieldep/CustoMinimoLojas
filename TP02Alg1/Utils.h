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
	static bool EstaNoVetor(vector<Trajeto> l1, vector<Ponto>* pontos);
	static void RemoveMaiorTrajeto(vector<Trajeto>* trajetos, vector<Ponto>* pontos);
	static vector<Trajeto> SelecionaMelhorTrajeto(vector<Loja*>* lojas, vector<Ponto>* pontos, Trajeto* menorTrajeto);
	static void AdicionaTrajetoAVetor(vector<Trajeto>* trajetos, Trajeto* trajeto, vector<Ponto>* pontos);
	static void CalcularTodosTrajetos(vector<Loja*>* lojas, vector<Trajeto>* trajetos);
	static void UpdatePontosPercorridos(vector<Ponto>* pontos, int ponto1, int ponto2);
	static vector<Ponto> CreateVetorPontos(vector<Loja*>* lojas);
	static Trajeto GetTrajetoLigarPontas(vector<Ponto>* pontos, vector<Loja*> lojas);
	static vector<Trajeto> GetTrajetosPorDrone(vector<Trajeto> trajetos, int qtdDrones);
	static double GetCustoPorMotos(vector<Trajeto>* trajetos, int kmMaxMoto, int custoKmMoto);
	static double GetCustoPorCaminhao(vector<Trajeto>* trajetos, int kmMaxMoto, int custoKmCaminhao);
	static double SomarTamanhoTrajetos(vector<Trajeto> trajetos);
	static void RemoveTrajetoDrone(vector<Trajeto>* trajetos, int qtdDrones);
};

