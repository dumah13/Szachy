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
	int iGlebokoscPrzeszukiwania = 1;
	Wektor enPassant = {-1,-1};
	bool bWyswietlonyInterfejs = false;
	bool bSzach = false;
	int iLiczbaSzachujacych = 0;
	bool bMat = false;
public:
	HandlerGry(int _iIloscBotow = 0, Plansza* _plansza = nullptr, int kolorGracza = 0);
	~HandlerGry();

	Gracz* GetGracz(int _indeks) { return gGracze[_indeks]; }

	Wektor WykonajRuch(Ruch* _pRuch, bool _widoczne = true);
	void SymulujRuch(Ruch* _pRuch, bool _sprawdzLegalnosc = true);
	void CofnijRuch(bool _sprawdzLegalnosc = true);
	void InicjalizujGre(int _iIloscBotow, int kolorGracza = 0);
	int GetLiczbaRuchow() { return iLiczbaRuchow; }
	int GetLiczbaRuchowPrzeciwnika() { return iLiczbaRuchowPrzeciwnika; }
	int GetTuraGracza() { return iTuraGracza; }
	int GetGlebokoscPrzeszukiwania() { return iGlebokoscPrzeszukiwania; }
	int GetLiczbaSzachujacych() { return iLiczbaSzachujacych; }
	bool GetSzach() { return bSzach; }
	bool GetMat() { return bMat; }
	void SetGlebokosc(int _nowaGlebokosc) { iGlebokoscPrzeszukiwania = _nowaGlebokosc; }
	void RysujPlansze();
	int WykonajTure();
	void WyczyscInterfejs();
	void WyswietlInterfejs();
	string TypDoString(TypFigury _typ);
	void WypiszDaneRuchu(Ruch* _ruch, ostream& _os = cout);
	void SprawdzLegalneRuchyKrola(int _iKolorGracza);
	void SprawdzLegalneRuchy(int _iKolorGracza);
	int SprawdzSzach(int _iKolorGracza);
	int SprawdzMat();
	int ZakonczGre();
	void ZmienTureGracza();
	string KonwertujIndeks(Wektor _we);
	Wektor KonwertujIndeks(string _s);
};


