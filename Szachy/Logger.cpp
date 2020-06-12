#include "Logger.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>

using namespace std;

int Logger::iterator = 0;
vector<string> Logger::vsLista = {};

void Logger::Log(string _sWiadomosc) {
	string bufor = ":   ";
	string log = to_string(++iterator) + bufor + _sWiadomosc;

	vsLista.push_back(log);
	//cout << vsLista.back() << endl;
}

string Logger::GetOstatniLog() {
	return vsLista.back();
}

vector<string>& Logger::GetLogi() {
	return vsLista;
}

void Logger::ZapiszLogi(string _sNazwaPliku) {
	time_t timer;
	time(&timer);
	char str[26];
	ctime_s(str, sizeof(str), &timer);
	string temp = str;
	//temp.erase(0, 1);
	replace(temp.begin(), temp.end(), ' ', '_');
	replace(temp.begin(), temp.end(), ':', '-');
	temp.erase(temp.find('\n'));

	//temp.erase(temp.size() - 2, 2);

	string nazwa = _sNazwaPliku + temp.substr(3,22) + ".txt";
	ofstream plik;
	plik.open(nazwa, ofstream::out);
	 
	for (int i = 0; i < (int)vsLista.size(); i++)
	{
		plik << vsLista[i] << endl;
	}

	plik.close();
}

