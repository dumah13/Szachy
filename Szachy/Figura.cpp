#include "Figura.h"
#include "Plansza.h"
#include "Ruch.h"
#include "DodatkoweFunkcje.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

Figura::Figura():
	mozliweRuchy {},
	wektoryRuchu {} 
{
	vector<string> svSymbol;
	iPozycjaStartowa = 1;

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
	iPozycjaStartowa = 1;
	iTypFigury = _iTyp;
	wczytajSymbol(_sSciezka);

	sprawdzWektoryRuchu();
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

		wektor = { (int)iTypFigury, 0, false};
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

vector<Ruch>& Figura::GetRuchy() {
	return mozliweRuchy;
}

void Figura::sprawdzRuchy(int _pozycja[2], Plansza& _plansza) {
	int rozmiarPlanszy = Plansza::iWymiaryPlanszy;

	mozliweRuchy.clear();

	for(int i = 0; i < wektoryRuchu.size(); i++)
	{
		Wektor wektor = wektoryRuchu[i];

		do
		{
			Wektor ruchZ;
			ruchZ.x = _pozycja[0];
			ruchZ.y = _pozycja[1];
			bool niedozwolonyRuch = false;
			Wektor pozycja = ruchZ + wektor;

			//Wyjœcie poza planszê
			if (pozycja.x < 0 || pozycja.x >= rozmiarPlanszy || pozycja.y < 0 || pozycja.y >= rozmiarPlanszy) {
				break;
			}

			int _pozStartZbitej = 0;
			bool _promocja = false;
			bool _roszada = false;
			bool _zbicie = false;
			TypFigury typZbitej = TypFigury::Brak;

			Pole* docelowe = &_plansza[pozycja.x][pozycja.y];
			Wektor ruchDo = pozycja;

			//Zbicie normalne
			if (!docelowe->Puste()) 
			{
				if (sgn(docelowe->GetFigura()->GetTyp()) == sgn(iTypFigury) || abs((int)iTypFigury) == (int)TypFigury::bPion) {
					if (abs((int)iTypFigury) == (int)TypFigury::bWieza && iPozycjaStartowa && docelowe->GetFigura()->GetPozycjaStartowa() && abs((int)docelowe->GetFigura()->GetTyp()) == (int)TypFigury::bKrol && docelowe->GetFigura()->GetPozycjaStartowa()) {
						_roszada = true;
						_pozStartZbitej = docelowe->GetFigura()->iPozycjaStartowa;
					}
					else {
						niedozwolonyRuch = true;
					}
				}
				else {
					typZbitej = docelowe->GetFigura()->GetTyp();
					_zbicie = true;
					_pozStartZbitej = docelowe->GetFigura()->iPozycjaStartowa;
				}
			}
			
			//Specjalne piona
			if (iTypFigury == TypFigury::bPion || iTypFigury == TypFigury::cPion) {
				int k = 1;

				//Ostatni lub pierwszy wiersz - promocja
				if (pozycja.x == 0 || pozycja.x == rozmiarPlanszy - 1) {
					_promocja = true;
				}

				//Handling double pusha piona
				if (wektor.wersor) {
					if (niedozwolonyRuch) {
						break;
					}
					Ruch ruch2(this, &_plansza, ruchZ, ruchDo, _zbicie, _promocja, true, iPozycjaStartowa, _pozStartZbitej, typZbitej);
					mozliweRuchy.push_back(ruch2);
					break;
				}

				if (!niedozwolonyRuch)
				{
					Ruch ruch1(this, &_plansza, ruchZ, ruchDo, _zbicie, _promocja, false, iPozycjaStartowa, _pozStartZbitej, typZbitej);
					mozliweRuchy.push_back(ruch1);
				}

				int enPassant = 0;

				//Bicie piona
				for (int k = 0; k < 2; k++)
				{
					for (int j = -1; j < 2; j++) {
						if (_pozycja[1] + j < 0 || _pozycja[1] + j >= rozmiarPlanszy || j == 0) {
							continue;
						}
						int x = pozycja.x;
						int y = pozycja.y + j;

						if (k == 1) {
							enPassant = 1;
							if (!_plansza[x][y].Puste()) {
								continue;
							}
							x -= sgn(iTypFigury);
						}

						docelowe = &_plansza[x][y];
						if (!docelowe->Puste() && (sgn(docelowe->GetFigura()->GetTyp()) != sgn(iTypFigury))) {
							_pozStartZbitej = docelowe->GetFigura()->iPozycjaStartowa;
							if (enPassant) {
								if (docelowe->GetFigura()->GetPozycjaStartowa() != 2) {
									continue;
								}
							}
							ruchDo.y = y;
							typZbitej = docelowe->GetFigura()->GetTyp();
							_zbicie = true;

							Ruch ruch2(this, &_plansza, ruchZ, ruchDo, _zbicie, _promocja, enPassant, iPozycjaStartowa, _pozStartZbitej, typZbitej);
							mozliweRuchy.push_back(ruch2);
						}

					}
				}

				//double push
				if (iPozycjaStartowa) {
					if (niedozwolonyRuch) {
						break;
					}
					wektor *= 2;
					wektor.wersor = true;
					continue;
				}

				break;
			}

			if (!niedozwolonyRuch)
			{
				Ruch ruch(this, &_plansza, ruchZ, ruchDo, _zbicie, _promocja, _roszada, iPozycjaStartowa, _pozStartZbitej, typZbitej);
				mozliweRuchy.push_back(ruch);
			}
			else {
				break;
			}
			if (!_zbicie && !_roszada)
			{
				wektor++;
			}
			else {
				break;
			}

		} while (wektor.wersor);
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

int Figura::GetPozycjaStartowa() {
	return iPozycjaStartowa;
}

void Figura::SetPozycjaStartowa(int _nowa) {
	iPozycjaStartowa = _nowa;
}

void Figura::Rysuj(Rysunek& _rPole) {
	_rPole.DodajWarstwe(rSymbol);
}

