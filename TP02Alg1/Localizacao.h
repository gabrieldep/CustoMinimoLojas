#pragma once
class Localizacao
{
private:
	int x;
	int y;
public:
	Localizacao();
	Localizacao(int x, int y);
	~Localizacao();
	int CalcularDistancia(Localizacao localizacao);
	void SetX(int x);
	void SetY(int y);
	int GetY();
	int GetX();
};

