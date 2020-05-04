#include "Figura.h"
#include "Rysunek.h"
#include "Plansza.h"
#include "Pole.h"
#include "Logger.h"
#include <iostream>
#include <SDL_mouse.h>

using namespace std;

int main() {
	try
	{
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

		int x, y;
		cin >> x;
		
		SDL_Window* window = SDL_GetMouseFocus();
		SDL_GetGlobalMouseState(&x, &y);
		//SDL_GetMouseState(&x, &y);
		cout << x << endl << y;
		int i;
		cin >> i;
		cout << endl;

		plansza.RysujPlansze();
		plansza[0][5].DodajMaske(warstwa);
		plansza["A5"].DodajMaske(warstwa);

		figura1.wczytajSymbol("symbole.txt");
		system("cls");

		Figura figura2(TypFigury::cPion, "symbole.txt");
		Figura figura3(TypFigury::bKrolowa, "symbole.txt");
		Figura figura4(TypFigury::bKrolowa, "symbole.txt");
		Figura figura5(TypFigury::cKrolowa, "symbole.txt");
		Figura figura6(TypFigury::bWieza, "symbole.txt");
		Figura figura7(TypFigury::cWieza, "symbole.txt");



		plansza[0][4].DodajFigure(figura2);
		plansza[1][4].DodajFigure(figura3);
		plansza[7][4].DodajFigure(figura4);
		plansza[2][4].DodajFigure(figura4);
		plansza[7][2].DodajFigure(figura5);
		plansza[0][0].DodajFigure(figura6);
		plansza.RysujPlansze();

		TypFigury ustawienie[8][8] = {
			TypFigury::cWieza, TypFigury::cKon,TypFigury::cHetman,TypFigury::cKrolowa, TypFigury::cKrol,TypFigury::cHetman,TypFigury::cKon,TypFigury::cWieza,
			TypFigury::cPion, TypFigury::cPion, TypFigury::cPion, TypFigury::cPion, TypFigury::cPion, TypFigury::cPion, TypFigury::cPion, TypFigury::cPion,
			TypFigury::Brak, TypFigury::Brak, TypFigury::Brak, TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,
			TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,
			TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,
			TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,TypFigury::Brak,
			TypFigury::bPion, TypFigury::bPion, TypFigury::bPion, TypFigury::bPion, TypFigury::bPion, TypFigury::bPion, TypFigury::bPion, TypFigury::bPion,
			TypFigury::bWieza, TypFigury::bKon,TypFigury::bHetman,TypFigury::bKrol,TypFigury::bKrolowa, TypFigury::bHetman,TypFigury::bKon,TypFigury::bWieza,
		};

		Plansza plansza2;
		plansza2.wczytajUstawienie(ustawienie);

		system("cls");
		plansza2["D2"].DodajMaske(warstwa);
		plansza2.RysujPlansze();

		cin >> i;
		system("cls");
		plansza2["D2"].UsunMaske();
		plansza2.RysujPlansze();
#//figura1.Rysuj(plansza[0][4]);
		defaultLogger.Log("aaaaaaaaabb");
		defaultLogger.ZapiszLogi();

	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}

	return EXIT_SUCCESS;
}