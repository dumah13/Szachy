#pragma once
#include "Gracz.h"
#include <vector>

class Bot :
	public Gracz
{
private:
	vector<Ruch*> mozliweRuchy;
	int iGlebokoscPrzeszukiwania = 1;
public:
	Bot(Plansza* _paPlansza, HandlerGry* _handlerGry, int _iKolor, int _iWartoscPlanszy = 0): Gracz(_paPlansza, _handlerGry, _iKolor, _iWartoscPlanszy, false) {  };

	Ruch* WybierzRuch();
	void SymulujRuch();
	int NegaMax(int _glebokosc);
	vector<Ruch*>& GetRuchy() { return mozliweRuchy; }
};

