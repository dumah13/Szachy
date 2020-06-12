#include "Ruch.h"
#include "Plansza.h"
#include "Figura.h"
#include "DodatkoweFunkcje.h"

Ruch::Ruch(Figura* _figura, Plansza* _plansza, int _z[2], int _do[2], bool _zbicie, bool _awans, bool _roszada, int _pozycjaStartowa, int _pozycjaStartowaZbitej, TypFigury _zbita) :
	ruchZ{ _z[0], _z[1] },
	ruchDo{ _do[0], _do[1] },
	czyZbicie(_zbicie),
	czyAwans(_awans),
	czySpecjalne(_roszada),
	figura(_figura),
	plansza(_plansza),
	zbitaFigura(_zbita),
	pozycjaStartowa(_pozycjaStartowa),
	pozycjaStartowaZbitej(_pozycjaStartowaZbitej)
{
	typFigury = _figura->GetTyp();
	kolor = (int)figura->GetTyp() >= 0 ? true : false;
}

Ruch::Ruch(Figura* _figura, Plansza* _plansza, Wektor _z, Wektor _do, bool _zbicie, bool _awans, bool _specjalne, int _pozycjaStartowa, int _pozycjaStartowaZbitej, TypFigury _zbita) :
	ruchZ(_z),
	ruchDo(_do),
	czyZbicie(_zbicie),
	czyAwans(_awans),
	czySpecjalne(_specjalne),
	figura(_figura),
	plansza(_plansza),
	zbitaFigura(_zbita),
	pozycjaStartowa(_pozycjaStartowa),
	pozycjaStartowaZbitej(_pozycjaStartowaZbitej)
{
	typFigury = _figura->GetTyp();
	kolor = (int)figura->GetTyp() >= 0 ? false : true;
}

bool Ruch::operator==(string _indeksDo) {

	if (_indeksDo.size() != 2) {
		throw exception("Indeks pola jest nieprawidlowy. Prawidlowy format: 'B6'.");
	}

	ToLower(_indeksDo);
	int x;
	int y;

	if (_indeksDo[0] > _indeksDo[1]) {
		y = _indeksDo[0] - 97;
		x = _indeksDo[1] - 48 - 1;
	}
	else {
		y = _indeksDo[1] - 97;
		x = _indeksDo[0] - 48 - 1;
	}

	if (ruchDo.x == x && ruchDo.y == y) {
		return true;
	}
	else {
		return false;
	}
}

bool Ruch::operator==(int _pos[2]) {

	int x = _pos[0];
	int y = _pos[1];

	if (ruchDo.x = x && ruchDo.y == y) {
		return true;
	}
	else {
		return false;
	}
}

bool Ruch::operator==(Wektor poz) {

	int x = poz.x;
	int y = poz.y;

	if (ruchDo.x == x && ruchDo.y == y) {
		return true;
	}
	else {
		return false;
	}
}