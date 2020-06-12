#include <string>
#include "Ruch.h"
#include "Rysunek.h"

class Plansza;

using namespace std;

#pragma once
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

class Figura
{
private:
	int iWysokoscFigury;
	int iSzerokoscFigury;
	int iPozycjaStartowa = 1;
	Rysunek rSymbol;
	TypFigury iTypFigury;
	vector<Ruch> mozliweRuchy;
	vector<Wektor> wektoryRuchu;
public:
	Figura();
	Figura(TypFigury _iTyp, string _sSciezka);

	void sprawdzRuchy(int _pozycja[2], Plansza& _plansza);
	void sprawdzWektoryRuchu();
	void wczytajSymbol(string _sSciezka);
	int GetWysokosc();
	int GetSzerokosc();
	int GetPozycjaStartowa();
	void SetPozycjaStartowa(int _nowa);
	TypFigury GetTyp();
	vector<Ruch>& GetRuchy();
	void SetRuchy(vector<Ruch> _ruchy) { mozliweRuchy = _ruchy; }
	void Rysuj(Rysunek& _rPole);
	
	virtual void WykonajRuch() {};
	virtual void SprawdzRuch() {};
};

