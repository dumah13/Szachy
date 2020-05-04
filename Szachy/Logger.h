#include <vector>
#include <string>

using namespace std;
#pragma once
static class Logger
{
private:
	vector<string> vsLista;
	int iterator = 0;
public:
	void Log(string _sWiadomosc);
	string GetOstatniLog();
	vector<string> GetLogi();
	void ZapiszLogi(string _sNazwaPliku = "\\logs\\log");
}  defaultLogger;

