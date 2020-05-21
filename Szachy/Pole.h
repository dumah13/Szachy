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
	int GetIloscWarstw();
	int GetWysokosc();
	int GetKolor();
	void SetFigura(Figura& _fFigura);
	bool Puste();
		
	void ZdejmijFigure();
	void Rysuj(Rysunek& _rRysunek);
	void Rysuj();
	void DodajMaske(vector<string> _vsMaska);
	void DodajMaske(Rysunek _rMaska);
	void UsunMaske();
	void UstawFigure(Figura& _fFigura);
	void ZmienKolor();
};
