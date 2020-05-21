#include <iostream>
#include <limits.h>
#pragma once

using namespace std;

inline void ToLower(string& _sNapis) {
	for (int i = 0; i < _sNapis.length(); i++)
	{
		_sNapis[i] = tolower(_sNapis[i]);
	}
}

inline void ToLower(char* _sNapis, int _dlugosc) {
	for (int i = 0; i < _dlugosc; i++)
	{
		_sNapis[i] = tolower(_sNapis[i]);
	}
}

//Zwraca losow¹ wartoœæ T spomiêdzy przedzia³ów _min a _max z dok³adnoœci¹ _iDok³adnoœæ miejsc po przecinku (je¿eli T jest liczb¹ rzeczywist¹) 
template <typename T>
T losowaPrzedzial(T _min, T _max, int _iDokladnosc = 2) {
	//Korzystam z templatek ¿eby mieæ losow¹ dystrybucjê niezale¿nie od typu zmiennej któr¹ tu wrzucam

	//Warunek - je¿eli T jest typem intowych (char, int) losujê wartoœæ normalnie,
	//a je¿eli T jest Typem zmiennoprzecinkowym to najpierw przesuwam wartoœæ o _iDok³adnoœ miejsc po przecinku w lewo, aby uzyskaæ wynik w postaci liczby rzeczywistej)
	//(je¿eli nie jest ¿adnym z tych dwóch typów to zachowanie jest niezdefiniowane, nie umiem jeszcze siê przed tym zabezpieczyæ)

	int min;
	int max;
	int mnoznik = (int)pow(10, _iDokladnosc);
	int wynik;
	if (std::is_floating_point<T>::value) {
		min = (int)((T)(mnoznik)* _min);
		max = (int)((T)(mnoznik)* _max);
	}
	else
	{
		min = (int)_min;
		max = (int)_max;
	}

	wynik = min + rand() % (max - min + 1);

	return std::is_floating_point<T>::value ? (T)(wynik / (double)mnoznik) : (T)wynik;
}

//Czyœci strumien _is po odczytaniu b³ednych danych
inline void czyscStrumienWejsciowy(istream& _is) {
	if (_is.fail() == true) {
		cout << "Blad strumienia wejsciowego. Nieprawidlowy typ danych.\n";
		_is.clear();
		_is.ignore(INT_MAX, '\n');
	}
}

//Wczytuje dane typu T ze strumienia _is
template <typename T>
T wczytajWartosc(istream& _is) {
	T dane;
	bool blad = true;

	//cout << "Typ: " << typeid(T).name() << endl;
	while (blad) {
		_is >> dane;

		if (!_is.fail()) {
			blad = false;
		}

		czyscStrumienWejsciowy(_is);
	}

	return dane;
}

//Wczytuje wartoœæ typu T ze strumienia _is która mieœci siê w przedziale _ograniczenieDolne <= x <= _ograniczenieGorne
template <typename T>
T wczytajWartosc(istream& _is, T _ograniczenieDolne, T _ograniczenieGorne) {
	T dane;

	bool blad = true;

	//cout << "Typ: " << typeid(T).name() << endl;
	cout << "Zakres: " << _ograniczenieDolne << " do " << _ograniczenieGorne << endl;
	do {
		_is >> dane;

		if (!_is.fail()) {
			if (dane < _ograniczenieDolne || dane > _ograniczenieGorne) {
				cout << "Wprowadzona wartosc nie miesci sie w podanym zakresie!\n";
			}
			else
				blad = false;
		}

		czyscStrumienWejsciowy(_is);
	} while (blad);

	return dane;
}

template <typename T>
void wczytajWartosc(istream& _is, T* _tablica, int _dlugoscTablicy) {
	if (_dlugoscTablicy < 0) {
		cout << "Dlugosc tablicy nie moze byc ujemna!\n";
	}

	T dane;

	bool blad = true;

	//cout << "Typ: " << typeid(T).name() << endl;
	cout << "Ilosc wczytywanych danych: " << _dlugoscTablicy << endl;
	for (int i = 0; i < _dlugoscTablicy; i++, blad = true)
	{
		if (_is.eof()) {
			cout << "Blad, koniec pliku" << endl;
			return;
		}
		do {
			_is >> dane;

			if (!_is.fail()) {
				blad = false;
			}

			czyscStrumienWejsciowy(_is);
		} while (blad);

		_tablica[i] = dane;
	}
}



