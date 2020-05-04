#include "Figura.h"
#include <vector>

#pragma once
class Pole
{
private:
	bool bPuste;
	int iSzerokosc;
	int iKolor;
	int iWysokosc;
	Rysunek rSymbol;
	Figura* fFiguraNaPolu;

public:
	Pole();

	Figura& GetFigura();
	
	int GetSzerokosc();
	int GetWysokosc();
	int GetKolor();
	void SetFigura(Figura& _fFigura);
	bool Puste();
		
	void UsunFigure();
	void Rysuj(Rysunek& _rRysunek);
	void Rysuj();
	void DodajMaske(vector<string> _vsMaska);
	void DodajMaske(Rysunek _rMaska);
	void UsunMaske();
	void DodajFigure(Figura& _fFigura);
	void ZmienKolor();
};
