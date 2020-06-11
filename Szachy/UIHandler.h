#include "Plansza.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

#define CZYSCLINIE "\33[2K\r"

#pragma once
class UIHandler
{

public:
	const static int WielkoscBuforaOkna = 5;
	const static int MaxDlugoscLiniiOkna = 50;
	
private:
	static HANDLE wHnd;
	static HANDLE rHnd;
	
	static Plansza* pAktualnaPlansza;
	static COORD consoleSize;
	static PCOORD pConsoleSize;
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
	void PrzesunKursor(int _ix, int _iy);
	string WyswietlZapytanie(string _komunikat, int _iloscZnakow, COORD _punktWyswietlenia = { -1,-1 }, bool _centrum = false);
	SHORT* WyswietlOkno(string _komunikat, COORD _pozycja, bool _centrum = false);
	static int Init(Plansza* _plansza);
	static void PrzelaczFullscreen(bool _fullscren);
} static uiHandler;

