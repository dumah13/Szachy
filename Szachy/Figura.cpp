#include "Figura.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

Figura::Figura() {
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

}

Figura::Figura(TypFigury _iTyp, string _sSciezka) {
	iTypFigury = _iTyp;
	wczytajSymbol(_sSciezka);
	return;
}

TypFigury Figura::GetTyp() {
	return iTypFigury;
}

void Figura::wczytajSymbol(string _sSciezka) {
	fstream plik;
	vector<string> svSymbol;
	string bufor;

	plik.open(_sSciezka);

	if (!plik.good())
	{
		throw exception("Blad!Dostep do pliku zostal zabroniony!");
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

