#include <vector>
#include <string>

using namespace std;
#pragma once
class Logger
{
private:
	vector<string> vsLista;
	int iterator = 0;
public:
	void Log(string _sWiadomosc);
	string GetOstatniLog();
	vector<string> GetLogi();
	void ZapiszLogi(string _sNazwaPliku = "\\logs\\log");
}  static defaultLogger;

