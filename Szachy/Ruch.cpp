#include "Ruch.h"
#include "Plansza.h"
#include "Figura.h"

Ruch::Ruch(Figura* _figura, Plansza* _plansza, int _z[2], int _do[2], bool _zbicie, bool _awans, bool _roszada, TypFigury _zbita) :
	ruchZ{ _z[0], _z[1] },
	ruchDo{ _do[0], _do[1] },
	czyZbicie(_zbicie),
	czyAwans(_awans),
	czySpecjalne(_roszada),
	figura(_figura),
	plansza(_plansza),
	zbitaFigura(_zbita)
{
	kolor = (int)figura->GetTyp() >= 0 ? true : false;
}

Ruch::Ruch(Figura* _figura, Plansza* _plansza, Wektor _z, Wektor _do, bool _zbicie, bool _awans, bool _specjalne, TypFigury _zbita) :
	ruchZ(_z),
	ruchDo(_do),
	czyZbicie(_zbicie),
	czyAwans(_awans),
	czySpecjalne(_specjalne),
	figura(_figura),
	plansza(_plansza),
	zbitaFigura(_zbita)
{
	kolor = (int)figura->GetTyp() >= 0 ? false : true;
}