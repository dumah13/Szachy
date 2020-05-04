#include "Rysunek.h"
#include <vector>
#include <algorithm> 
#include <iostream>

using namespace std;

Rysunek::Rysunek(int _IloscWierszy) {
	InitRysunek(_IloscWierszy);
}

Rysunek::Rysunek(vector<string> _svObraz) {
	InitRysunek(_svObraz.size());
	DodajDoRysunku(_svObraz);
}

void Rysunek::InitRysunek(int _iIloscWierszy) {
	iIloscWarstw = 0;
	iIloscWierszy = _iIloscWierszy;
	svRysunek.clear();
	svRysunek.reserve(_iIloscWierszy);

	for (int i = 0; i < iIloscWierszy; ++i)
	{
		svRysunek.push_back("");
	}
}

int Rysunek::GetLiczbaWierszy() {
	return iIloscWierszy;
}

void Rysunek::DodajDoRysunku(Rysunek& _rRysunek) {
	if (_rRysunek.iIloscWierszy != iIloscWierszy) {
		throw exception("Blad! Rysunek ma niewlasciwa liczbe wierszy.", 1);
	}

	for (int i = 0; i < iIloscWierszy; ++i)
	{
		svRysunek[i + iIloscWarstw * iIloscWierszy].append(_rRysunek.svRysunek[i+ _rRysunek.iIloscWarstw*iIloscWierszy]);
	}
}

void Rysunek::DodajWarstwe(vector<string>& _vsWarstwa) {
	if (_vsWarstwa.size() != iIloscWierszy) {
		throw exception("Blad! Zla ilosc wierszy dla warstwy", 2);
	}


	for (int i = 0; i < iIloscWierszy; ++i)
	{
		svRysunek.push_back("");
	}

	++iIloscWarstw;

	for (int i = iIloscWierszy*iIloscWarstw; i < (iIloscWarstw + 1)*iIloscWierszy; ++i)
	{
		int iDlaWarstwy = i - iIloscWierszy * iIloscWarstw;
		int iDlaPoprzedniejWarstwy = i - iIloscWierszy;
		int length = svRysunek[iDlaPoprzedniejWarstwy].length();

		for (int j = 0; j < length; j++) {
			if (j < _vsWarstwa[iDlaWarstwy].length() && _vsWarstwa[iDlaWarstwy][j] != '.') {
				svRysunek[i].push_back(_vsWarstwa[iDlaWarstwy][j]);
			}
			else {
				svRysunek[i].push_back(svRysunek[iDlaPoprzedniejWarstwy][j]);
			}
		}

	}
}

void Rysunek::DodajWarstwe(Rysunek& _rWarstwa) {
	if (_rWarstwa.iIloscWierszy != iIloscWierszy) {
		throw exception("Blad! Zla ilosc wierszy dla warstwy", 2);
	}


	for (int i = 0; i < iIloscWierszy; ++i)
	{
		svRysunek.push_back("");
	}

	++iIloscWarstw;

	for (int i = iIloscWierszy * iIloscWarstw; i < (iIloscWarstw + 1) * iIloscWierszy; ++i)
	{
		int iDlaWarstwy = i - iIloscWierszy * iIloscWarstw +_rWarstwa.iIloscWarstw*iIloscWierszy;
		int iDlaPoprzedniejWarstwy = i - iIloscWierszy;
		int length = svRysunek[iDlaPoprzedniejWarstwy].length();

		for (int j = 0; j < length; j++) {
			if (j < _rWarstwa[iDlaWarstwy].length() && _rWarstwa[iDlaWarstwy][j] != '.') {
				svRysunek[i].push_back(_rWarstwa[iDlaWarstwy][j]);
			}
			else {
				svRysunek[i].push_back(svRysunek[iDlaPoprzedniejWarstwy][j]);
			}
		}

	}
}

void Rysunek::ZastapWiersz(int _iNrWiersza, string nowyWiersz) {
	if (_iNrWiersza > iIloscWierszy || _iNrWiersza < 0) {
		throw exception("Blad! Niepoprawna ilosc wierszy.", 4);
	}

	svRysunek[_iNrWiersza] = nowyWiersz;
}

int Rysunek::GetLiczbaWarstw() {
	return iIloscWarstw;
}

void Rysunek::UsunWarstwe() {
	if (iIloscWarstw <= 0) {
		throw exception("Blad! Nie mozna usunac maski poniewaz rysunek nie posiada zadnej.", 3);
	}

	for (int i = 0; i < iIloscWierszy; ++i)
	{
		svRysunek.pop_back();
	}
	--iIloscWarstw;
}

void Rysunek::DodajDoRysunku(vector<string>& _svRysunek) {
	if ((int)(_svRysunek.size()) != iIloscWierszy) {
		throw exception("Blad! Rysunek ma niewlasciwa liczbe wierszy.", 1);
	}

	for(int i = 0; i < iIloscWierszy; ++i)	
	{
		svRysunek[i].append(_svRysunek[i]);
	}
}

void Rysunek::Rysuj(int _iWarstwa) {
	if (iIloscWarstw - _iWarstwa < 0 || iIloscWarstw - _iWarstwa > iIloscWarstw) {
		throw exception("Blad! Podano nieistniejaca warstwe.", 2);
	}
	for(int i  = (iIloscWarstw - _iWarstwa)*iIloscWierszy; i < (iIloscWarstw+1)*iIloscWierszy; ++i)
	{
		cout << svRysunek[i] << endl;
	}
}
