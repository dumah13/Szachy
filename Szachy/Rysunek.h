#include <string>
#include <vector>

using namespace std;

#pragma once
class Rysunek
{
private:
	vector<string> svRysunek;
	int iIloscWierszy;

	int iIloscWarstw;
public:
	Rysunek(int _IloscWierszy = 0);
	Rysunek(vector<string> _svObraz);
	int GetLiczbaWarstw();
	int GetLiczbaWierszy();

	void InitRysunek(int _iIloscWierszy);
	void DodajDoRysunku(vector<string>& _svRysunek);
	void DodajDoRysunku(Rysunek& _rRysunek);
	void Rysuj(int _iWarstwa = 0);
	void DodajWarstwe(vector<string>& _vsWarstwa);
	void DodajWarstwe(Rysunek& _rWarstwa);
	void UsunWarstwe();
	void ZastapWiersz(int _iNrWiersza, string nowyWiersz);

	string& operator[](int i) {
		if (i < 0 || i >= iIloscWierszy) {
			throw exception("Blad! Indeks poza zasiegiem tablicy", 1);
		}

		return svRysunek[i];
	}
};

