#include "Figura.h"
#include "Pole.h"
#include "Rysunek.h"

#pragma once

class Plansza
{
public:
	static const int iWymiaryPlanszy = 8;
	const string sSciezkaZasobow = "";
private:
	
	int iSzerokoscBuforu;
	int iSzerokoscPola;
	int iWysokoscPola;
	Pole paPlansza[iWymiaryPlanszy][iWymiaryPlanszy];

	void RysujWiersz(int _iNrWiersza);

public:
	Plansza();
	void wczytajUstawienie(const TypFigury _tUstawienie[iWymiaryPlanszy][iWymiaryPlanszy]);
	void RysujPlansze();
	void wyczyscPlansze();

	int getSzerokoscPola() { return iSzerokoscPola; }
	int getSzerokoscBuforu() { return iSzerokoscBuforu; }
	int getWysokoscPola() { return iWysokoscPola; }

	Pole* operator[](int _iIndex);
	Pole& operator[](const char _sAdresPola[3]);
	Pole& operator[](string str);
//	~Plansza();
};

const TypFigury ustawienieBialeDol[8][8] = {
	TypFigury::cWieza, TypFigury::cKon,TypFigury::cGoniec,TypFigury::cKrolowa, TypFigury::cKrol,TypFigury::cGoniec,TypFigury::cKon,TypFigury::cWieza,
	TypFigury::cPion, TypFigury::cPion, TypFigury::cPion, TypFigury::cPion, TypFigury::cPion, TypFigury::cPion, TypFigury::cPion, TypFigury::cPion,
	TypFigury::Brak, TypFigury::Brak, TypFigury::Brak, TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,
	TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,
	TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,
	TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,
	TypFigury::bPion, TypFigury::bPion, TypFigury::bPion, TypFigury::bPion, TypFigury::bPion, TypFigury::bPion, TypFigury::bPion, TypFigury::bPion,
	TypFigury::bWieza, TypFigury::bKon,TypFigury::bGoniec,TypFigury::bKrol,TypFigury::bKrolowa, TypFigury::bGoniec,TypFigury::bKon,TypFigury::bWieza,
};

const TypFigury ustawienieCzarneDol[8][8] = {
	TypFigury::bWieza, TypFigury::bKon,TypFigury::bGoniec,TypFigury::bKrolowa, TypFigury::bKrol,TypFigury::bGoniec,TypFigury::bKon,TypFigury::bWieza,
	TypFigury::bPion, TypFigury::bPion, TypFigury::bPion, TypFigury::bPion, TypFigury::bPion, TypFigury::bPion, TypFigury::bPion, TypFigury::bPion,
	TypFigury::Brak, TypFigury::Brak, TypFigury::Brak, TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,
	TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,
	TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,
	TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,
	TypFigury::cPion, TypFigury::cPion, TypFigury::cPion, TypFigury::cPion, TypFigury::cPion, TypFigury::cPion, TypFigury::cPion, TypFigury::cPion,
	TypFigury::cWieza, TypFigury::cKon,TypFigury::cGoniec,TypFigury::cKrol,TypFigury::cKrolowa, TypFigury::cGoniec,TypFigury::cKon,TypFigury::cWieza,
};
