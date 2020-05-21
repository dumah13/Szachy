class Figura;
class Plansza;
enum class TypFigury;

#pragma once
struct Wektor {
	int x;
	int y;
	bool wersor;

	Wektor(int _x = 0, int _y = 0, bool _wersor = false): x(_x), y(_y), wersor(_wersor){}

	Wektor& operator=(const Wektor& _wektor)
	{
		x = _wektor.x;
		y = _wektor.y;
		wersor = _wektor.wersor;
		return *this;
	}

	Wektor operator*(const int _skalar) {
		int a = x * _skalar;
		int b = y * _skalar;
		Wektor nowy(a, b, this->wersor);
		return nowy;
	}

	Wektor& operator*=(const Wektor& _wektor) {
		x *= _wektor.x;
		y *= _wektor.y;
		return *this;
	}

	Wektor& operator*=(const int _skalar) {
		x *= _skalar;
		y *= _skalar;
		return *this;
	}

	Wektor operator+(const Wektor& _wektor) {
		int a = x + _wektor.x;
		int b = y + _wektor.y;
		Wektor nowy(a, b, this->wersor);
		return nowy;
	}

	Wektor operator+(const int _skalar) {
		int a = x + _skalar;
		int b = y + _skalar;
		Wektor nowy(a, b, this->wersor);
		return nowy;
	}

	Wektor& operator++() {
		x += x == 0 ? 0 : x < 0 ? -1 : 1;
		y += y == 0 ? 0 : y < 0 ? -1 : 1;
		return *this;
	}

	Wektor& operator++(int) {
		x += x == 0 ? 0 : x < 0 ? -1 : 1;
		y += y == 0 ? 0 : y < 0 ? -1 : 1;
		return *this;
	}

};

#pragma once
class Ruch
{
	Wektor ruchZ;
	Wektor ruchDo;

	//Maska ruchow
	bool czyZbicie;
	bool czyAwans;
	bool czySpecjalne;
	Plansza* plansza;
	Figura* figura;
	TypFigury zbitaFigura;
	bool kolor; //0 - biale, 1 - czarne

public:

	Ruch(Figura* _figura, Plansza* _plansza, int _z[2], int _do[2], bool _zbicie, bool _awans, bool _roszada, TypFigury _zbita);
	Ruch(Figura* _figura, Plansza* _plansza, Wektor _z, Wektor _do, bool _zbicie, bool _awans, bool _specjalne, TypFigury _zbita);

	bool GetZbicie() { return czyZbicie; }
	bool GetAwans() { return czyAwans; }
	bool GetSpecjalne() { return czySpecjalne; }
	bool GetKolor() { return kolor; }
	TypFigury GetZbita() { return zbitaFigura; }
	Wektor GetZ() { return ruchZ; }
	Wektor GetDo() { return ruchDo; }
};