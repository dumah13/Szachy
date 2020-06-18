#include "Bot.h"
#include <limits>
#include "HandlerGry.h"
#include <Windows.h>
#include "DodatkoweFunkcje.h"

Ruch* Bot::WybierzRuch() {
	Sleep(250);
	return mozliweRuchy[AlphaBeta(INT16_MIN,INT16_MAX, iGlebokoscPrzeszukiwania)];
}

int Bot::NegaMax(int _glebokosc) {
	int wartosc = 0;
	int nrRuchu = 0;
	int kolor = GetHandlerGry()->GetGracz(GetHandlerGry()->GetTuraGracza())->GetKolor() == 0 ? 1 : -1;
	if (_glebokosc == 0) return EwaluujPlansze()*kolor;

	vector<Ruch*>& ruchy = GetHandlerGry()->GetGracz(GetHandlerGry()->GetTuraGracza())->GetRuchy();
	int max = INT16_MIN;
	for (int i = 0; i < ruchy.size(); i++){
		GetHandlerGry()->SymulujRuch(ruchy[i]);

		GetHandlerGry()->ZmienTureGracza();
		wartosc = -NegaMax(_glebokosc - 1);
		if (wartosc > max) {
			
			max = wartosc;
			nrRuchu = i;
		}

	
		GetHandlerGry()->CofnijRuch();
	}
	if (_glebokosc == iGlebokoscPrzeszukiwania)
	{
		if (GetHandlerGry()->GetTuraGracza() != GetKolor()) {
			GetHandlerGry()->ZmienTureGracza();
		}
		return nrRuchu;
	}
	return max;
}

int Bot::AlphaBeta(int _alpha, int _beta, int _glebokosc) {
	int wartosc = 0;
	int nrRuchu = 0;
	int kolor = GetHandlerGry()->GetGracz(GetHandlerGry()->GetTuraGracza())->GetKolor() == 0 ? 1 : -1;
	if (_glebokosc == 0) return Quiesce(_alpha, _beta);

	vector<Ruch*>& ruchy = GetHandlerGry()->GetGracz(GetHandlerGry()->GetTuraGracza())->GetRuchy();
	
	if (ruchy.size() == 0) {
		return INT16_MIN;
	}

	for (int i = 0; i < ruchy.size(); i++) {
		GetHandlerGry()->SymulujRuch(ruchy[i]);
		GetHandlerGry()->ZmienTureGracza();

		wartosc = -AlphaBeta(-_beta, -_alpha, _glebokosc - 1);//* losowaPrzedzial<float>(0.7,1);


		GetHandlerGry()->CofnijRuch();
		if (wartosc >= _beta){
			return _beta;
		}   //  fail hard beta-cutoff
		if (wartosc > _alpha)
		{
			nrRuchu = i;
			_alpha = wartosc; // alpha acts like max in MiniMax
		}
	}
	if (_glebokosc == iGlebokoscPrzeszukiwania)
	{
		if (GetHandlerGry()->GetTuraGracza() != GetKolor()) {
			GetHandlerGry()->ZmienTureGracza();
		}
		return nrRuchu;
	}
	return _alpha;
}

int Bot::Quiesce(int _alpha, int _beta) {
	int kolor = GetHandlerGry()->GetGracz(GetHandlerGry()->GetTuraGracza())->GetKolor() == 0 ? 1 : -1;
	int stand_pat = EwaluujPlansze()*kolor;
	int score = 0;
	if (stand_pat >= _beta)
		return _beta;
	if (stand_pat < _alpha - (9)) {
		return _alpha;
	}
	if (_alpha < stand_pat)
		_alpha = stand_pat;
	int BIG_DELTA = 9; // queen value



	vector<Ruch*>& ruchy = GetHandlerGry()->GetGracz(GetHandlerGry()->GetTuraGracza())->GetRuchy();

	for (int i = 0; i < ruchy.size(); i++) {
		if (ruchy[i]->GetZbicie())
		{
			GetHandlerGry()->SymulujRuch(ruchy[i]);
			GetHandlerGry()->ZmienTureGracza();

			score = -Quiesce(-_beta, -_alpha);
			GetHandlerGry()->CofnijRuch();

			if (score >= _beta) {
				if (GetHandlerGry()->GetTuraGracza() != GetKolor()) {
					GetHandlerGry()->ZmienTureGracza();
				}
				return _beta;
			}
			if (score > _alpha)
				_alpha = score;
		}
	}
	if (GetHandlerGry()->GetTuraGracza() != GetKolor()) {
		GetHandlerGry()->ZmienTureGracza();
	}
	return _alpha;
}