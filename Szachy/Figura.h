#include <string>
#include "Rysunek.h"

using namespace std;

enum class TypFigury {
	Brak = 0,

	bPion = 1,
	cPion = -1,

	bKon = 2,
	cKon =-2,

	bHetman = 3,
	cHetman = -3,

	bWieza = 4,
	cWieza = -4,

	bKrolowa = 5,
	cKrolowa = -5,

	bKrol = 6,
	cKrol = -6,
};

#pragma once
class Figura
{
private:
	int iWysokoscFigury;
	int iSzerokoscFigury;
	Rysunek rSymbol;
	TypFigury iTypFigury;
public:
	Figura();
	Figura(TypFigury _iTyp, string _sSciezka);
	
	void wczytajSymbol(string _sSciezka);
	int GetWysokosc();
	int GetSzerokosc();
	TypFigury GetTyp();
	void Rysuj(Rysunek& _rPole);
	
	virtual void Ruch() {};
	virtual void SprawdzRuch() {};
};

