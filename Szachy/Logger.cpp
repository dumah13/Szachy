#include "Logger.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <algorithm>

using namespace std;

void Logger::Log(string _sWiadomosc) {
	string bufor = ":   ";
	string log = to_string(++iterator) + bufor + _sWiadomosc;

	vsLista.push_back(log);
	cout << vsLista.back() << endl;
}

string Logger::GetOstatniLog() {
	return vsLista.back();
}

vector<string> Logger::GetLogi() {
	return vsLista;
}

void Logger::ZapiszLogi(string _sNazwaPliku) {
	time_t timer;
	time(&timer);
	char str[26];
	ctime_s(str, sizeof(str), &timer);
	string temp = str;
	replace(temp.begin(), temp.end(), ' ', '_');
	replace(temp.begin(), temp.end(), ':', '_');
	temp.erase(temp.find('\n'));

	string nazwa = _sNazwaPliku + temp.substr(3,16) + ".txt";
	ofstream plik;
	plik.open(nazwa);
	 
	for (int i = 0; i < (int)vsLista.size(); i++)
	{
		plik << vsLista[i] << endl;
	}

	plik.close();
}
