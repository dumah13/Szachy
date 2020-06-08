#include "Plansza.h"
#include "Ruch.h"

#pragma once
class Gracz
{
	int iKolor;
	int iWartoscPlanszy;
	Plansza* paPlansza;
public:
	Gracz(Plansza* _paPlansza, int _iKolor, int _iWartoscPlanszy = 0) : paPlansza(_paPlansza), iKolor(_iKolor), iWartoscPlanszy(_iWartoscPlanszy) {};

	int GetKolor();
	int GetWartosc();
	Ruch* WybierzRuch();
};

