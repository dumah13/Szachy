#include "Plansza.h"
#include "DodatkoweFunkcje.h"
#include <iostream>

Plansza::Plansza()
{
	iSzerokoscBuforu = paPlansza[0][0].GetSzerokosc();

	for (int i = 0; i < iWymiaryPlanszy; i++)
	{
		for (int j = 0; j < iWymiaryPlanszy; j++)
		{
			if (paPlansza[i][j].GetKolor() != (i + j) % 2) {
				paPlansza[i][j].ZmienKolor();
			}
		}
	}

	return;
}

void Plansza::RysujWiersz(int _iNrWiersza) {
	int wysokosc = paPlansza[0][0].GetWysokosc();
	Rysunek rWiersz(wysokosc);
	
	string bufor = "";
	vector<string> rBufor;

	for (int i = 0; i < iSzerokoscBuforu; i++) {
		bufor.push_back(' ');
	}

	for (int i = 0; i < wysokosc; i++) {
		if ((i + wysokosc / 2 + 1) % wysokosc == 0) {
			int symbol = '1' + _iNrWiersza;
			if (symbol > '9') {
				char dziesiatki= '0';
				while (symbol > '9') {
					symbol -= 10;
					dziesiatki++;
				}
				bufor[iSzerokoscBuforu - 2] = dziesiatki;
			}
			bufor[iSzerokoscBuforu - 1] = symbol;
			rBufor.push_back(bufor);
			bufor[iSzerokoscBuforu - 1] = ' ';
			bufor[iSzerokoscBuforu - 2] = ' ';
		}
		else rBufor.push_back(bufor);;

	}

	rWiersz.DodajDoRysunku(rBufor);

	for (int i = 0; i < iWymiaryPlanszy; ++i) {
		paPlansza[_iNrWiersza][i].Rysuj(rWiersz);
	}
	/*if (_iNrWiersza == iWymiaryPlanszy - 1) {
		int wymiar = paPlansza[0][0].GetFigura().GetSzerokosc();
		string ostatniaLinijka = "";

		for (int i = 0; i < wymiar * iWymiaryPlanszy; i++) {
			ostatniaLinijka.push_back('-');
		}

		rWiersz.ZastapWiersz(paPlansza[0][0].GetFigura().GetWysokosc() - 1, ostatniaLinijka);
	}*/
	rWiersz.Rysuj();
}

void Plansza::wyczyscPlansze() {
	for (int i = 0; i < iWymiaryPlanszy; i++)
	{
		for (int j = 0; j < iWymiaryPlanszy; j++)
		{
			if (!paPlansza[i][j].Puste()) {
				delete (&paPlansza[i][j].GetFigura());
				paPlansza[i][j].ZdejmijFigure();
			}
		}
	}
}


void Plansza::RysujPlansze() {
	int wymiar = paPlansza[0][0].GetSzerokosc();
	string pierwszaLinijka = "";

	cout << endl;
	cout << endl;
	cout << endl;

	for (int i = 0; i < iSzerokoscBuforu; ++i) {

		pierwszaLinijka.push_back(' ');
	}

	char j = 'A';

	for (int i = 0; i < wymiar*iWymiaryPlanszy; i++) {
		if ((i + wymiar / 2 +1) % wymiar == 0) {

			pierwszaLinijka.push_back(j++);

		}
		else pierwszaLinijka.push_back('_');
	}

	cout << pierwszaLinijka << endl;

	for (int i = iWymiaryPlanszy-1; i >= 0; --i) {
		RysujWiersz(i);
		//std::cout << endl;
	}
	std::cout << endl;
}

Pole* Plansza::operator[](int index) {

	if (index > iWymiaryPlanszy || index < 0) {
		throw exception("Blad! Indeks poza tablica.", 1);
	}

	return paPlansza[index];
}

Pole& Plansza::operator[](const char _sAdresPola[3]) {
	char adres[3] = {};
	strcpy_s(adres, _sAdresPola);
	ToLower(adres, 3);
	int x;
	int y;

	if (adres[0] > adres[1]) {
		x = adres[0] - 97;
		y = adres[1] - 48 - 1;
	}
	else {
		x = adres[1] - 97;
		y = adres[0] - 48 - 1;
	}

	if (x >= iWymiaryPlanszy || x < 0 || y >= iWymiaryPlanszy || y < 0) {
		throw exception("Blad! Indeks poza tablica.", 1);
	}

	return paPlansza[y][x];
}

Pole& Plansza::operator[](string str) {
	char adres[3] = {};

	if (str.length() < 2) {
		throw exception("Blad indeksatora planszy");
	}

	for (int i = 0; i < 3; i++) {
		adres[i] = str[i];
	}
	return (*this)[adres];
}

void Plansza::wczytajUstawienie(const TypFigury _tUstawienie[iWymiaryPlanszy][iWymiaryPlanszy]) {
	wyczyscPlansze();

	for (int i = 0; i < iWymiaryPlanszy; i++)
	{
		for (int j = 0; j < iWymiaryPlanszy; j++)
		{
			int indekserDlaUstawienia = iWymiaryPlanszy - i - 1;
			if (_tUstawienie[indekserDlaUstawienia][j] != TypFigury::Brak) {
				Figura* figura = new Figura(_tUstawienie[indekserDlaUstawienia][j], sSciezkaZasobow + "symbole.txt");
				paPlansza[i][j].UstawFigure(*figura);
			}
		}
	}
}

Plansza::~Plansza() {
	wyczyscPlansze();
	return;
}