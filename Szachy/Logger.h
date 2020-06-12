#include <vector>
#include <string>

using namespace std;
#pragma once
class Logger
{
private:
	static vector<string> vsLista;
	static int iterator;
public:
	void Log(string _sWiadomosc);
	string GetOstatniLog();
	vector<string>& GetLogi();
	void ZapiszLogi(string _sNazwaPliku = ".\\logs\\log");
}  static defaultLogger;

