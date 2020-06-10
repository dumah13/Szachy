#include "Figura.h"
#include "Rysunek.h"
#include "Plansza.h"
#include "Pole.h"
#include "Logger.h"
#include "Gracz.h"
#include "HandlerGry.h"
#include <iostream>
#include <windows.h>
#include "UIHandler.h"

using namespace std;

int main(int argc, char* argv[])
{
	try
	{


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

		Plansza* plansza = new Plansza();

		plansza->RysujPlansze();
		//plansza[0][5].DodajMaske(warstwa);
		string str = "A5";
		//plansza[str].DodajMaske(warstwa);

		figura1.wczytajSymbol("symbole.txt");
		system("cls");

		Figura figura2(TypFigury::bPion, "symbole.txt");
		Figura figura3(TypFigury::bPion, "symbole.txt");
		Figura figura4(TypFigury::cKon, "symbole.txt");
		Figura figura5(TypFigury::bKrol, "symbole.txt");
		Figura figura6(TypFigury::bWieza, "symbole.txt");
		Figura figura7(TypFigury::cKrolowa, "symbole.txt");

		HandlerGry handlerGry(0,plansza);

		figura2.sprawdzWektoryRuchu();
		figura7.sprawdzWektoryRuchu();
		int tab[2] = { 3, 4 };

		figura2.sprawdzRuchy(tab, *plansza);
		for (int i = 0; i < figura2.GetRuchy().size(); i++) {
			//(*plansza)[figura2.GetRuchy()[i].GetDo().x][figura2.GetRuchy()[i].GetDo().y].DodajMaske(warstwa);
		}


		int tab2[2] = { 0, 0 };


		figura6.sprawdzRuchy(tab2, *plansza);
		//plansza[3][4].UstawFigure(*figura2);
		(*plansza)[5][3].UstawFigure(figura3);
		(*plansza)[6][5].UstawFigure(figura4);
		(*plansza)[0][3].UstawFigure(figura6);


		Gracz graczTest(plansza, 0);

		/*for (size_t i = 0; i < 1;)
		{
			(*plansza)[tab2[0]][tab2[1]].GetFigura()->sprawdzRuchy(tab2, *plansza);
			Wektor nowa = handlerGry.WykonajRuch(handlerGry.GetGracz(0)->WybierzRuch());
			tab2[0] = nowa.x;
			tab2[1] = nowa.y;
		}*/

		/*uiHandler.DodajWarstweUI(warstwa, 3, 4);
		uiHandler.OdswiezPole(3, 4);
		uiHandler.UsunWarsteUI(3, 4);
		uiHandler.OdswiezPole(3, 4);
		uiHandler.OdswiezPole("E4");
		uiHandler.OdswiezPole("A1");
		uiHandler.OdswiezPole("G8");
		//uiHandler.OdswiezPole("J2");
		//return 0;
		*/
		Plansza plansza2;
		plansza2.wczytajUstawienie(ustawienieBialeDol);

		handlerGry.InicjalizujGre(0);

		while (true) {
			handlerGry.WykonajTure();
			//handlerGry.ZakonczGre();
		}

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

