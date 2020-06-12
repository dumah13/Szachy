#include "Gracz.h"
#include "Ruch.h"
#include <vector>
#include <iostream>

class Plansza;

#pragma once
class HandlerGry
{
	Plansza* pPlansza = nullptr;
	vector<Ruch> historiaRuchow;
	Gracz* gGracze[2];
	int iTuraGracza = 0;
	int iZwyciezca = 0;
	int iLicznikTur = 0;
	int iIloscBotow = 0;
	int iLiczbaRuchow = 0;
	int iLiczbaRuchowPrzeciwnika = 0;
	Figura* enPassant = nullptr;
	bool bWyswietlonyInterfejs = false;
	bool bSzach = false;
public:
	HandlerGry(int _iIloscBotow = 0, Plansza* _plansza = nullptr, int kolorGracza = 0);
	~HandlerGry();

	Gracz* GetGracz(int _indeks) { return gGracze[_indeks]; }

	Wektor WykonajRuch(Ruch* _pRuch, bool _widoczne = true);
	void SymulujRuch(Ruch* _pRuch);
	void CofnijRuch();
	void InicjalizujGre(int _iIloscBotow, int kolorGracza = 0);
	int GetLiczbaRuchow() { return iLiczbaRuchow; }
	int GetLiczbaRuchowPrzeciwnika() { return iLiczbaRuchowPrzeciwnika; }
	void RysujPlansze();
	int WykonajTure();
	void WyczyscInterfejs();
	void WyswietlInterfejs();
	string TypDoString(TypFigury _typ);
	void WypiszDaneRuchu(Ruch* _ruch, ostream& _os = cout);
	void SprawdzLegalneRuchyKrola(int _iKolorGracza);
	void SprawdzLegalneRuchy(int _iKolorGracza);
	int SprawdzSzach();
	int SprawdzMat();
	int ZakonczGre();
	string KonwertujIndeks(Wektor _we);
	Wektor KonwertujIndeks(string _s);
};


