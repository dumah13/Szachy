#include "Figura.h"
#include "Plansza.h"
#include "Ruch.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

Figura::Figura():
	mozliweRuchy {},
	wektoryRuchu {} 
{
	vector<string> svSymbol;

	svSymbol	= { 
				 "",
				 "",
				 "",
				 "",
				 "",
				 ""
	};
	iWysokoscFigury = (int)svSymbol.size();
	iSzerokoscFigury = (int)svSymbol[0].length();
	iTypFigury = TypFigury::Brak;
	rSymbol = svSymbol;
	mozliweRuchy = {};
	wektoryRuchu = {};
}

Figura::Figura(TypFigury _iTyp, string _sSciezka):
	mozliweRuchy{},
	wektoryRuchu{} 
{
	iTypFigury = _iTyp;
	wczytajSymbol(_sSciezka);

	return;
}

void Figura::sprawdzWektoryRuchu() {
	int typ = abs((int)iTypFigury);
	Wektor wektor;
	Wektor tempWektor;
	int i;
	int j;

	switch (typ) {
	case 1:

		wektor = { 0,(int)iTypFigury, false};
		wektoryRuchu.push_back(wektor);
		break;

	case 2:
		i = 1;
		j = 2;

		for (int k = 0; k < 2; k++, i*= -1, j*=-1)
		{
			wektor = { i, j };
			wektoryRuchu.push_back(wektor);
			
			int temp = i;
			i = j;
			j = temp;
			wektor = { i,j };
			wektoryRuchu.push_back(wektor);

			wektor.x = i *= -1;
			wektoryRuchu.push_back(wektor);

			temp = i;
			i = j;
			j = temp;
			wektor = { i,j };
			wektoryRuchu.push_back(wektor);
		}

		break;

	case 5:
	case 3:
		
		wektor = { 1, 1, true };
		wektoryRuchu.push_back(wektor);

		tempWektor = { 1,-1, true };
		wektor *= tempWektor;
		wektoryRuchu.push_back(wektor);

		wektor *= -1;
		wektoryRuchu.push_back(wektor);

		wektor *= tempWektor;
		wektoryRuchu.push_back(wektor);

		if (typ != 5)
		{
			break;
		}

	case 4:

		wektor = { 0,1,true };
		wektoryRuchu.push_back(wektor);

		wektor *= -1;
		wektoryRuchu.push_back(wektor);

		wektor = { 1,0,true };
		wektoryRuchu.push_back(wektor);

		wektor *= -1;
		wektoryRuchu.push_back(wektor);
		break;

	case 6:
		for (i = -1; i < 2; i++)
		{
			for (j = -1; j < 2; j++)
			{
				if (i == 0 && j == 0) {
					continue;
				}
				wektor = { i,j, false};
				wektoryRuchu.push_back(wektor);
			}
		}
		break;
	}
}

TypFigury Figura::GetTyp() {
	return iTypFigury;
}

void Figura::sprawdzRuchy(int _pozycja[2], static Plansza& _plansza) {
	int rozmiarPlanszy = Plansza::iWymiaryPlanszy;

	for(int i = 0; i < wektoryRuchu.size(); i++)
	{
		Wektor wektor = wektoryRuchu[i];
		Wektor ruchZ;
		ruchZ.x = _pozycja[0];
		ruchZ.y = _pozycja[1];

		Wektor pozycja = ruchZ + wektor;

		if (pozycja.x < 0 || pozycja.x >= rozmiarPlanszy || pozycja.y < 0 || pozycja.y >= rozmiarPlanszy) {
			continue;
		}

		bool _promocja = false;

		if (pozycja.x == 0 || pozycja.x == rozmiarPlanszy - 1) {
			_promocja = true;
		}

		bool _zbicie = false;
		TypFigury typZbitej = TypFigury::Brak;

		Pole* docelowe = &_plansza[pozycja.x][pozycja.y];
		Wektor ruchDo = pozycja;

		if (!docelowe->Puste) {
			typZbitej = docelowe->GetFigura().GetTyp();
			_zbicie = true;
		}

		if (iTypFigury == TypFigury::bPion) {
			docelowe = &_plansza[pozycja.x + 1][pozycja.y];
			if (!docelowe->Puste) {
				ruchDo.x += 1;
				typZbitej = docelowe->GetFigura().GetTyp();
				_zbicie = true;
				Ruch ruch(this, &_plansza, ruchZ, ruchDo, _zbicie, _promocja, false, typZbitej);
				mozliweRuchy.push_back(ruch);
			}
		}
	}
}

void Figura::wczytajSymbol(string _sSciezka) {
	fstream plik;
	vector<string> svSymbol;
	string bufor;

	plik.open(_sSciezka);

	if (!plik.good())
	{
		throw exception("Blad! Dostep do pliku zostal zabroniony!");
	}

	bool pobierzSymbol = false;
	bool pobranoSymbol = false;

	while (!plik.eof())
	{
		getline(plik, bufor);
		if (bufor[0] == '#') {
			if (pobierzSymbol) {
				pobierzSymbol = false;
				pobranoSymbol = true;
				break;
			}
			else if (stoi(bufor.substr(1, bufor.length() - 1)) == (int)iTypFigury) {
				pobierzSymbol = true;
			}
		}
		else if (pobierzSymbol) {
			replace(bufor.begin(), bufor.end(), ',', '\0');
			svSymbol.push_back(bufor);
		}
	};


	if (pobranoSymbol)
	{
		rSymbol = svSymbol;
	}
	else {
		throw exception("Blad! Nie mozna pobrac symbolu.");
	}

	iWysokoscFigury = (int)svSymbol.size();
	iSzerokoscFigury = (int)svSymbol[0].length();

	plik.close();

}

int Figura::GetWysokosc() {
	return iWysokoscFigury;
}

int Figura::GetSzerokosc() {
	return iSzerokoscFigury;
}

void Figura::Rysuj(Rysunek& _rPole) {
	_rPole.DodajWarstwe(rSymbol);
}

