#include "Plansza.h"
#include "Ruch.h"

class HandlerGry;

#pragma once
class Gracz
{
public:
	static const int wagaMobilnosci = 1;
private:

	int iKolor;
	int iWartoscPlanszy;
	bool bLudzkiGracz;
	Plansza* paPlansza;
	HandlerGry* handlerGry;
public:
	Gracz(Plansza* _paPlansza, HandlerGry* _handlerGry ,int _iKolor, int _iWartoscPlanszy = 0, bool _ludzki = true) : paPlansza(_paPlansza), handlerGry(_handlerGry) ,iKolor(_iKolor), iWartoscPlanszy(_iWartoscPlanszy), bLudzkiGracz(_ludzki) {};

	int GetKolor();
	int GetWartosc();
	Plansza* GetPlansza() { return paPlansza; }
	HandlerGry* GetHandlerGry() { return handlerGry; }
	int EwaluujPlansze();
	void SetWartosc(int _nowa) { iWartoscPlanszy = _nowa; }
	bool CzyLudzki() { return bLudzkiGracz; }
	virtual Ruch* WybierzRuch();
};

