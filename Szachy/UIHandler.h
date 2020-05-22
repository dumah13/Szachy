#include "Plansza.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#pragma once



class UIHandler
{

public:
	const static int WielkoscBuforaOkna = 5;
	const static int MaxDlugoscLiniiOkna = 40;
private:
	HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE rHnd = GetStdHandle(STD_INPUT_HANDLE);
	Plansza* pAktualnaPlansza = nullptr;
	COORD consoleSize;
	PCOORD pConsoleSize = &consoleSize;
public:
	Plansza* GetPlansza();
	void SetPlansza(Plansza* _pPlansza);
	int DodajWarstweUI(Rysunek& _rWarstwa, string _indeksPola);
	int DodajWarstweUI(Rysunek& _rWarstwa, int _ix, int _iy);
	int DodajWarstweUI(vector<string>& _vsWarstwa, string _indeksPola);
	int DodajWarstweUI(vector<string>& _vsWarstwa, int _ix, int _iy);
	void UsunWarsteUI(string _indeksPola);
	void UsunWarsteUI(int _ix, int _iy);
	void OdswiezPole(string Pole);
	void OdswiezPole(int _ix, int _iy);
	void OdswiezPlansze();
	string WyswietlZapytanie(string _komunikat, int _iloscZnakow, COORD _punktWyswietlenia = { -1,-1 }, bool _centrum = false);
	SHORT* WyswietlOkno(string _komunikat, COORD _pozycja, bool _centrum = false);
	int Init(Plansza& _plansza, bool _fullscreen);
} static uiHandler;

