#include "Figura.h"
#include "Pole.h"
#include "Rysunek.h"

#pragma once
class Plansza
{
public:
	static const int iWymiaryPlanszy = 8;
private:
	const string sSciezkaZasobow = "";
	int iSzerokoscBuforu;
	Pole paPlansza[iWymiaryPlanszy][iWymiaryPlanszy];
	void RysujWiersz(int _iNrWiersza);

public:
	Plansza();
	void wczytajUstawienie(TypFigury _tUstawienie[iWymiaryPlanszy][iWymiaryPlanszy]);
	void RysujPlansze();
	void wyczyscPlansze();

	Pole* operator[](int _iIndex);
	Pole& operator[](const char _sAdresPola[3]);
	~Plansza();
};

