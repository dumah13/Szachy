#include "UIHandler.h"
#include "DodatkoweFunkcje.h"
#include <iomanip>

using namespace std;

int UIHandler::DodajWarstweUI(Rysunek& _rWarstwa, string _indeksPola)
{
	(*pAktualnaPlansza)[_indeksPola].DodajMaske(_rWarstwa);
	return (*pAktualnaPlansza)[_indeksPola].GetIloscWarstw();
}


int UIHandler::DodajWarstweUI(vector<string>& _vsWarstwa, string _indeksPola)
{
	(*pAktualnaPlansza)[_indeksPola].DodajMaske(_vsWarstwa);
	return (*pAktualnaPlansza)[_indeksPola].GetIloscWarstw();
}


bool UIHandler::UsunWarsteUI(string _indeksPola)
{
	int iloscWarstw = (*pAktualnaPlansza)[_indeksPola].GetIloscWarstw();

	if (iloscWarstw < 2) {
		return false;
	}

	(*pAktualnaPlansza)[_indeksPola].UsunMaske();

	return true;
}


Plansza* UIHandler::GetPlansza()
{
	return pAktualnaPlansza;
}


void UIHandler::SetPlansza(Plansza* _pPlansza)
{
	pAktualnaPlansza = _pPlansza;
}


string UIHandler::WyswietlZapytanie(string _komunikat, int _iloscZnakow, COORD _punktWyswietlenia, bool _centrum )
{
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	COORD point;
	GetConsoleScreenBufferInfo(wHnd, &bufferInfo);
	point = bufferInfo.dwCursorPosition;


	if (_punktWyswietlenia.X == -1) {
		_punktWyswietlenia = point;
	}

	
		//SetCursorPos(10, 10);

	//cin >> windowBufferSize;
	SHORT* wielkoscOkna = WyswietlOkno(_komunikat, _punktWyswietlenia, _centrum);

	COORD pozycjaKursora = { _punktWyswietlenia.X + wielkoscOkna[0] / 2 - _iloscZnakow / 2, _punktWyswietlenia.Y + wielkoscOkna[2] + 3 };

	SetConsoleCursorPosition(wHnd, pozycjaKursora);
	string input = wczytajWartosc<string>(cin);

	GetConsoleScreenBufferInfo(wHnd, &bufferInfo);
	SetConsoleCursorPosition(wHnd, { point.X, point.Y + wielkoscOkna[1]});

	delete wielkoscOkna;
	return string();
}


SHORT* UIHandler::WyswietlOkno(string _komunikat, COORD _pozycja, bool _centrum)
{
	int iloscLinii = _komunikat.length() / MaxDlugoscLiniiOkna + 1;
	int windowSizeX = iloscLinii == 1 ? _komunikat.length() + 2 * WielkoscBuforaOkna +2 : MaxDlugoscLiniiOkna + 2*WielkoscBuforaOkna + 2;
	int windowSizeY = iloscLinii + 5;
	SHORT Y = _pozycja.Y;

	if (_centrum) {
		_pozycja.X -= windowSizeX / 2;
		_pozycja.Y -= windowSizeY / 2;
	}

	SetConsoleCursorPosition(wHnd, _pozycja);

	cout.fill('-');
	cout.width(windowSizeX);
	cout << "";
	SetConsoleCursorPosition(wHnd, { _pozycja.X, ++Y });
	cout.fill(' ');
	for (int i = 0; i < windowSizeY; i++)
	{
		if (i >= 1 && i < iloscLinii + 1) {

			for (int j = 0; j < iloscLinii; j++, i++)
			{
				cout << "|";
				cout.width(WielkoscBuforaOkna);
				cout << "";
				cout.width(iloscLinii == 1 ? _komunikat.length() : MaxDlugoscLiniiOkna);
				cout << left << _komunikat.substr(j * MaxDlugoscLiniiOkna, MaxDlugoscLiniiOkna);
				cout.width(WielkoscBuforaOkna);
				cout << "" << "|";
				SetConsoleCursorPosition(wHnd, { _pozycja.X, ++Y });
			}
		}
		else
		{
			cout << "|";
			cout.width(windowSizeX - 2);
			cout << "";
			cout << "|";
			SetConsoleCursorPosition(wHnd, { _pozycja.X, ++Y });
		}
	}

	cout.fill('-');
	cout.width(windowSizeX);
	cout << "";

	SHORT* wielkoscOkna = new SHORT[3]{ (SHORT)windowSizeX, (SHORT)windowSizeY, (SHORT)iloscLinii };
	return wielkoscOkna;
}


int UIHandler::Init(Plansza& _plansza, bool _fullscreen)
{
	pAktualnaPlansza = &_plansza;

	if (_fullscreen) {
		SetConsoleDisplayMode(wHnd, CONSOLE_FULLSCREEN_MODE, pConsoleSize);
	}
	else {
		SetConsoleDisplayMode(wHnd, CONSOLE_WINDOWED_MODE, pConsoleSize);
	}

	return 0;
}
