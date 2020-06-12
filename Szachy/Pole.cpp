#include "Pole.h"
#include "Plansza.h"

Pole::Pole() {
	bPuste = true;
	fFiguraNaPolu = nullptr;

	vector<string> svSymbol;

	svSymbol = {
				 "|           |",
				 "|           |",
				 "|           |",
				 "|           |",
				 "|           |",
				 "_____________"
	};
	iKolor = 0;
	iWysokosc = (int)svSymbol.size();
	iSzerokosc = (int)svSymbol[0].length();
	rSymbol = svSymbol;

	return;
}

Pole::~Pole() {
	if (fFiguraNaPolu) {
		delete fFiguraNaPolu;
	}
}

int Pole::GetKolor() {
	return iKolor;
}

void Pole::ZmienKolor() {
	vector<string> svSymbol;

	if (iKolor) {
		svSymbol = {
		"|           |",
		"|           |",
		"|           |",
		"|           |",
		"|           |",
		"_____________"
		};
		iKolor = 0;
	}
	else {
		svSymbol = {
				 "|###########|",
				 "|###########|",
				 "|###########|",
				 "|###########|",
				 "|###########|",
				 "_____________" };
		iKolor = 1;
	}



	iWysokosc = (int)svSymbol.size();
	iSzerokosc = (int)svSymbol[0].length();

	rSymbol = svSymbol;
}


int Pole::GetSzerokosc() {
	return iSzerokosc;
}

int Pole::GetIloscWarstw() {
	return rSymbol.GetLiczbaWarstw();
}

int Pole::GetWysokosc() {
	return iWysokosc;
}

bool Pole::Puste() {
	return bPuste;
}

Figura* Pole::GetFigura() {
	if (!fFiguraNaPolu) {
		throw exception("Blad! Brak figury na polu.", 1);
	}
	return fFiguraNaPolu;
}

void Pole::SetFigura(Figura* _fFigura) {
	fFiguraNaPolu = _fFigura;
}

void Pole::Rysuj(Rysunek& _rRysunek) {
	_rRysunek.DodajDoRysunku(rSymbol);

}

void Pole::DodajMaske(vector<string> _vsMaska) {
	rSymbol.DodajWarstwe(_vsMaska);
}

void Pole::DodajMaske(Rysunek _rMaska) {
	rSymbol.DodajWarstwe(_rMaska);
}

void Pole::UsunMaske() {
	rSymbol.UsunWarstwe();
}

void Pole::UsunFigure() {
	if (fFiguraNaPolu)
	{
		delete fFiguraNaPolu;
	}
	ZdejmijFigure();
}

void Pole::ZdejmijFigure() {
	fFiguraNaPolu = nullptr;
	bPuste = true;
	rSymbol.UsunWarstwe();
}

void Pole::UstawFigure(Figura& _fFigura) {
	if (bPuste == false) {
		UsunFigure();
	}
	bPuste = false;
	Figura* figura = new Figura(_fFigura);
	SetFigura(figura);
	figura->Rysuj(rSymbol);
};

void Pole::UstawFigure(Figura* _pFigura) {
	if (bPuste == false) {
		UsunFigure();
	}
	bPuste = false;
	SetFigura(_pFigura);
	_pFigura->Rysuj(rSymbol);
}

void Pole::Rysuj() {

	rSymbol.Rysuj();
}