#include "UIHandler.h"
#include "DodatkoweFunkcje.h"
#include <iomanip>

using namespace std;

Plansza* UIHandler:: pAktualnaPlansza = nullptr;
COORD UIHandler::consoleSize = {300,300};
PCOORD UIHandler::pConsoleSize = &consoleSize;
HANDLE UIHandler::wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE UIHandler::rHnd = GetStdHandle(STD_INPUT_HANDLE);

int UIHandler::DodajWarstweUI(Rysunek& _rWarstwa, string _indeksPola)
{
	if (pAktualnaPlansza == nullptr) {
		throw exception("Blad! Brak planszy dla UIHandlera.");
	}

	(*pAktualnaPlansza)[_indeksPola].DodajMaske(_rWarstwa);
	return (*pAktualnaPlansza)[_indeksPola].GetIloscWarstw();
}

int UIHandler::DodajWarstweUI(Rysunek& _rWarstwa, int _ix, int _iy) {
	if (pAktualnaPlansza == nullptr) {
		throw exception("Blad! Brak planszy dla UIHandlera.");
	}

	(*pAktualnaPlansza)[_ix][_iy].DodajMaske(_rWarstwa);
	return (*pAktualnaPlansza)[_ix][_iy].GetIloscWarstw();
}

int UIHandler::DodajWarstweUI(vector<string>& _vsWarstwa, string _indeksPola)
{
	if (pAktualnaPlansza == nullptr) {
		throw exception("Blad! Brak planszy dla UIHandlera.");
	}

	(*pAktualnaPlansza)[_indeksPola].DodajMaske(_vsWarstwa);
	return (*pAktualnaPlansza)[_indeksPola].GetIloscWarstw();
}

int UIHandler::DodajWarstweUI(vector<string>& _vsWarstwa, int _ix, int _iy)
{
	if (pAktualnaPlansza == nullptr) {
		throw exception("Blad! Brak planszy dla UIHandlera.");
	}

	(*pAktualnaPlansza)[_ix][_iy].DodajMaske(_vsWarstwa);
	return (*pAktualnaPlansza)[_ix][_iy].GetIloscWarstw();
}

void UIHandler::UsunWarsteUI(string _indeksPola)
{
	if (pAktualnaPlansza == nullptr) {
		throw exception("Blad! Brak planszy dla UIHandlera.");
	}

	int iloscWarstw = (*pAktualnaPlansza)[_indeksPola].GetIloscWarstw();

	if (iloscWarstw < 1 || (iloscWarstw < 2 && !(*pAktualnaPlansza)[_indeksPola].Puste())) {
		throw exception("Blad! Pole nie posiada warstwy UI.");
	}

	(*pAktualnaPlansza)[_indeksPola].UsunMaske();

}

void UIHandler::UsunWarsteUI(int _ix, int _iy) {
	char pierwsza = '1' + _ix;
	char druga = 'a' + _iy;

	string indeks = { druga, pierwsza };

	UsunWarsteUI(indeks);
}


Plansza* UIHandler::GetPlansza()
{
	return pAktualnaPlansza;
}


void UIHandler::SetPlansza(Plansza* _pPlansza)
{
	pAktualnaPlansza = _pPlansza;
}

void UIHandler::OdswiezPole(int _iy, int _ix) {
	if (pAktualnaPlansza == nullptr) {
		throw exception("Blad! Brak planszy dla UIHandlera.");
	}

	try
	{
		CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
		GetConsoleScreenBufferInfo(wHnd, &bufferInfo);

		COORD staraPozycja = bufferInfo.dwCursorPosition;;
		COORD pozycjaKursora = { _ix * pAktualnaPlansza->getSzerokoscPola() + pAktualnaPlansza->getSzerokoscBuforu(), 4 + (Plansza::iWymiaryPlanszy - _iy - 1) * pAktualnaPlansza->getWysokoscPola() };
		SetConsoleCursorPosition(wHnd, pozycjaKursora);

		(*pAktualnaPlansza)[_iy][_ix].Rysuj();

		SetConsoleCursorPosition(wHnd, staraPozycja);
	}
	catch (const std::exception& e)
	{
		OdswiezPlansze();
	}
}

void UIHandler::OdswiezPole(string _sPole) {
		ToLower(_sPole);
		int y = _sPole[0] - 'a';
		int x = _sPole[1] - '1';

		OdswiezPole(x, y);
		
}

void UIHandler::OdswiezPlansze() {
	if (pAktualnaPlansza == nullptr) {
		throw exception("Blad! Brak planszy.");
	}

	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(wHnd, &bufferInfo);

	COORD staraPozycja = bufferInfo.dwCursorPosition;;

	SetConsoleCursorPosition(wHnd, {0,0});

	pAktualnaPlansza->RysujPlansze();

	SetConsoleCursorPosition(wHnd, staraPozycja);
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

	
	if (_centrum) {
		pozycjaKursora.X -= wielkoscOkna[0] / 2;
		pozycjaKursora.Y -= wielkoscOkna[1] / 2;
	}

	SetConsoleCursorPosition(wHnd, pozycjaKursora);
	string input = wczytajWartosc<string>(cin);


	GetConsoleScreenBufferInfo(wHnd, &bufferInfo);
	SetConsoleCursorPosition(wHnd, { point.X, point.Y});

	delete wielkoscOkna;
	return input;
}

void UIHandler::PrzesunKursor(int _ix, int _iy) {
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	COORD point;
	GetConsoleScreenBufferInfo(wHnd, &bufferInfo);
	point = bufferInfo.dwCursorPosition;

	point.X += _ix;
	point.Y += _iy;

	SetConsoleCursorPosition(wHnd, point);
}

SHORT* UIHandler::WyswietlOkno(string _komunikat, COORD _pozycja, bool _centrum)
{
	int iloscLinii = _komunikat.length() / MaxDlugoscLiniiOkna + 1;
	int windowSizeX = iloscLinii == 1 ? _komunikat.length() + 2 * WielkoscBuforaOkna +2 : MaxDlugoscLiniiOkna + 2*WielkoscBuforaOkna + 2;
	int windowSizeY = iloscLinii + 5;


	if (_centrum) {
		_pozycja.X -= windowSizeX / 2;
		_pozycja.Y -= windowSizeY / 2;
	}
	SHORT Y = _pozycja.Y;

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
	cout.fill(' ');

	SHORT* wielkoscOkna = new SHORT[3]{ (SHORT)windowSizeX, (SHORT)windowSizeY, (SHORT)iloscLinii };
	return wielkoscOkna;
}


int UIHandler::Init(Plansza* _plansza)
{
	UIHandler::pAktualnaPlansza = _plansza;

	return 0;
}

void UIHandler::PrzelaczFullscreen(bool _fullscreen) {
	if (_fullscreen) {
		SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, pConsoleSize);
	}
	else {
		SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_WINDOWED_MODE, pConsoleSize);
	}
}
