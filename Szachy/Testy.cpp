#include "Figura.h"
#include "Rysunek.h"
#include "Plansza.h"
#include "Pole.h"
#include "Logger.h"
#include <iostream>
#include <windows.h>
#include "UIHandler.h"

using namespace std;

int main(int argc, char* argv[])
{
	try
	{
		int i = 0;

		LPCWSTR tytul = L"Szachy :))))))))))))))";
		SetConsoleTitle(tytul);

		Rysunek rysunek;
		rysunek.InitRysunek(5);
		vector<string> obrazek = { "----------",
			"|        |",
			"|        |",
			"|        |",
			"----------"
		};

		for (int i = 0; i < 10; i++)
		{
			rysunek.DodajDoRysunku(obrazek);
		}

		vector<string> warstwa = { ".\\........./.",
							       "...\\...../...",
							       ".....-|-.....",
								   ".../.....\\...",
								   "./.........\\.",
								   ".............",
		};

		defaultLogger.Log("aaaaaaaaabb");

		rysunek.Rysuj();
		cout << endl;

		//rysunek.UsunWarstwe();
		rysunek.Rysuj();

		Figura figura1;

		Plansza plansza;

		plansza.RysujPlansze();
		plansza[0][5].DodajMaske(warstwa);
		string str = "A5";
		plansza[str].DodajMaske(warstwa);

		figura1.wczytajSymbol("symbole.txt");
		system("cls");

		Figura* figura2 = new Figura(TypFigury::cPion, "symbole.txt");
		Figura* figura3 = new Figura(TypFigury::bKrolowa, "symbole.txt");
		Figura* figura4 = new Figura(TypFigury::bKrolowa, "symbole.txt");
		Figura* figura5 = new Figura(TypFigury::cKrol, "symbole.txt");
		Figura* figura6 = new Figura(TypFigury::bWieza, "symbole.txt");
		Figura* figura7 = new Figura(TypFigury::cKrolowa, "symbole.txt");

		figura2->sprawdzWektoryRuchu();
		figura7->sprawdzWektoryRuchu();

		plansza[0][4].UstawFigure(*figura2);
		plansza[1][4].UstawFigure(*figura3);
		plansza[7][4].UstawFigure(*figura4);
		plansza[7][2].UstawFigure(*figura5);
		plansza[0][0].UstawFigure(*figura6);
		plansza.RysujPlansze();



		Plansza plansza2;
		plansza2.wczytajUstawienie(ustawienieCzarneDol);

		system("cls");
		plansza2["D2"].DodajMaske(warstwa);
		plansza2.RysujPlansze();

		system("cls");
		plansza2["D2"].UsunMaske();
		plansza2.RysujPlansze();
//figura1.Rysuj(plansza[0][4]);
		defaultLogger.Log("aaaaaaaaabb");
		defaultLogger.ZapiszLogi();

		string temp = uiHandler.WyswietlZapytanie("Testowy komunikat ASDADADDAADADADSDS", 2, {25,10});

	}

	catch (const std::exception& e)
	{
		cout << e.what();
	}

	return EXIT_SUCCESS;
}
