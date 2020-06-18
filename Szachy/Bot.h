#pragma once
#include "Gracz.h"
#include <vector>

class Bot :
	public Gracz
{
private:
	int iGlebokoscPrzeszukiwania;
public:
	Bot(Plansza* _paPlansza, HandlerGry* _handlerGry, int _iKolor, int _iWartoscPlanszy = 0, int _glebokoscPrzeszukiwania = 1) : Gracz(_paPlansza, _handlerGry, _iKolor, _iWartoscPlanszy, false), iGlebokoscPrzeszukiwania(_glebokoscPrzeszukiwania) {  };

	virtual Ruch* WybierzRuch();
	int NegaMax( int _glebokosc);
	int AlphaBeta(int _alpha, int _beta, int _glebokosc);
	int Quiesce(int alpha, int beta);
};

