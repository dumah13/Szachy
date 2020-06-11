#include "Plansza.h"
#include "Ruch.h"

class HandlerGry;

#pragma once
class Gracz
{
	int iKolor;
	int iWartoscPlanszy;
	bool bLudzkiGracz;
	Plansza* paPlansza;
	HandlerGry* handlerGry;
public:
	Gracz(Plansza* _paPlansza, HandlerGry* _handlerGry ,int _iKolor, int _iWartoscPlanszy = 0) : paPlansza(_paPlansza), handlerGry(_handlerGry) ,iKolor(_iKolor), iWartoscPlanszy(_iWartoscPlanszy), bLudzkiGracz(true) {};

	int GetKolor();
	int GetWartosc();
	bool CzyLudzki() { return bLudzkiGracz; }
	Ruch* WybierzRuch();
};

