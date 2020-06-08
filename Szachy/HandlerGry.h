#include "Gracz.h"
#include "Ruch.h"
#include <vector>

class Plansza;

#pragma once
class HandlerGry
{
	Plansza* pPlansza = nullptr;
	vector<Ruch> historiaRuchow;
	Gracz* gGracze[2];
	int iTuraGracza = 0;
	int iLicznikTur = 0;
	int iIloscBotow = 0;
	Figura* enPassant = nullptr;
	bool bSzach = false;
public:
	HandlerGry(int _iIloscBotow, Plansza* _plansza = nullptr);
	~HandlerGry();

	Gracz* GetGracz(int _indeks) { return gGracze[_indeks]; }

	Wektor WykonajRuch(Ruch* _pRuch);
	void InicjalizujGre(int _iIloscBotow);
	void WykonajTure();
	void WyswietlInterefejs();
	void SprawdzLegalneRuchy(int _iKolorGracza);
	int SprawdzSzach();
	int ZakonczGre();
};


