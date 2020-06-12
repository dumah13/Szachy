#include "Bot.h"
#include <limits>
#include "HandlerGry.h"
#include <Windows.h>

Ruch* Bot::WybierzRuch() {
	Sleep(500);
	return mozliweRuchy[NegaMax(iGlebokoscPrzeszukiwania)];
}

int Bot::NegaMax(int _glebokosc) {
	int wartosc = 0;
	int nrRuchu = 0;
	int kolor = GetKolor() == 0 ? 1 : -1;
	if (_glebokosc == 0) return EwaluujPlansze()*kolor;


	int max = INT16_MIN;
	for (int i = 0; i < mozliweRuchy.size(); i++){
		GetHandlerGry()->SymulujRuch(mozliweRuchy[i]);
		wartosc = NegaMax(_glebokosc - 1);
		if (wartosc > max) {
			
			max = wartosc;
			nrRuchu = i;
		}
	
		GetHandlerGry()->CofnijRuch();
	}
	if (_glebokosc == iGlebokoscPrzeszukiwania)
	{
		cout << "Max: " << max << "nr: " << nrRuchu << endl;
		return nrRuchu;
	}
	return max;
}