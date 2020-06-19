#pragma once
#include "opennn.h"
#include "Bot.h"

using namespace OpenNN;

class AI :
	public Bot
{
	NeuralNetwork siecNeuronowa;
public:
	AI(Plansza* _paPlansza, HandlerGry* _handlerGry, int _iKolor, int _iWartoscPlanszy = 0, int _glebokoscPrzeszukiwania = 1);
	~AI();
	Ruch* WybierzRuch();
	void SzkolSiec(int _wybranyRuch);
	void ZapiszWagiDoPliku(string _nazwa = "wagi_sieci.txt");
	void WczytajWagiZPliku(string _nazwa = "wagi_sieci.txt");
};

