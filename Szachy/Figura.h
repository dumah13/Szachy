#include <string>
#include "Rysunek.h"

class Ruch;

using namespace std;

enum class TypFigury {
	Brak = 0,

	bPion = 1,
	cPion = -1,

	bKon = 2,
	cKon =-2,

	bGoniec = 3,
	cGoniec = -3,

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
	vector<Ruch> mozliweRuchy;
	vector<Wektor> wektoryRuchu;
public:
	Figura();
	Figura(TypFigury _iTyp, string _sSciezka);
	
	void sprawdzRuchy(int _pozycja[2], static Plansza& _plansza);
	void sprawdzWektoryRuchu();
	void wczytajSymbol(string _sSciezka);
	int GetWysokosc();
	int GetSzerokosc();
	TypFigury GetTyp();
	void Rysuj(Rysunek& _rPole);
	
	virtual void WykonajRuch() {};
	virtual void SprawdzRuch() {};
};

