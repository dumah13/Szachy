﻿#include "Plansza.h"
#include "DodatkoweFunkcje.h"
#include <iostream>
#include <algorithm>

Plansza::Plansza()
{
	iWysokoscPola = 0;
	iSzerokoscBuforu = paPlansza[0][0].GetSzerokosc()*2;
	iSzerokoscPola = paPlansza[0][0].GetSzerokosc();

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
	iWysokoscPola = paPlansza[0][0].GetWysokosc();
	Rysunek rWiersz(iWysokoscPola);
	
	string bufor = "";
	vector<string> rBufor;

	for (int i = 0; i < iSzerokoscBuforu; i++) {
		bufor.push_back(' ');
	}

	for (int i = 0; i < iWysokoscPola; i++) {
		if ((i + iWysokoscPola / 2 + 1) % iWysokoscPola == 0) {
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
	for (int i = 0; i < rBufor.size(); ++i) {
		rBufor[i].erase(rBufor[i].begin(), rBufor[i].end() - 1);
	}
	rWiersz.DodajDoRysunku(rBufor);
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
				paPlansza[i][j].UsunFigure();
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
	std::replace(pierwszaLinijka.begin(), pierwszaLinijka.end(), '_', ' ');
	cout << pierwszaLinijka << endl;
	std::cout << endl;
}

Pole* Plansza::operator[](int index) {

	if (index > iWymiaryPlanszy || index < 0) {
		throw exception("Blad! Dane pole nie istnieje.", 1);
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
		throw exception("Blad! Dane pole nie istnieje.", 1);
	}

	return paPlansza[y][x];
}

Pole& Plansza::operator[](string str) {
	char adres[3] = {};

	if (str.length() != 2) {
		throw exception("Indeks pola jest nieprawidlowy. Prawidlowy format: 'B6'.");
	}

	for (int i = 0; i < 2; i++) {
		adres[i] = str[i];
	}
	adres[2] = '\0';

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
				Figura figura(_tUstawienie[indekserDlaUstawienia][j], sSciezkaZasobow + "symbole.txt");
				paPlansza[i][j].UstawFigure(figura);
			}
		}
	}
}

/*Plansza::~Plansza() {
	wyczyscPlansze();
	return;
}*/