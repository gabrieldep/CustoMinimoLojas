#pragma once
class Localizacao
{
private:
	double x;
	double y;
public:
	Localizacao();
	Localizacao(double x, double y);
	~Localizacao();
	double CalcularDistancia(Localizacao localizacao);
	void SetX(double x);
	void SetY(double y);
	double GetY();
	double GetX();
};

