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
#include "DodatkoweFunkcje.h"
#include <iomanip>

using namespace std;

int main(int argc, char* argv[])
{
	
	int krokProgramu = 0;
	bool kontynuuj = true;
	LPCWSTR tytul = L"conChess";
	SetConsoleTitle(tytul);
	HandlerGry handlerGry;
	int blad = 0;

	while (kontynuuj)
	{
		try
		{
			vector<string> napis =
			{
				"                    ________   ___  ___   _______    ________    ________      ",
				"                   |\\   ____\\ |\\  \\|\\  \\ |\\  ___ \\  |\\   ____\\  |\\   ____\\     ",
				"                   \\ \\  \\___| \\ \\  \\\\\\  \\\\ \\   __/| \\ \\  \\___|_ \\ \\  \\___|_    ",
				"                    \\ \\  \\     \\ \\   __  \\\\ \\  \\_|/__\\ \\_____  \\ \\ \\_____  \\   ",
				"  / __|/ _ \\ | '_ \\  \\ \\  \\____ \\ \\  \\ \\  \\\\ \\  \\_|\\ \\\\|____|\\  \\ \\|____|\\  \\  ",
				" | (__| (_) || | | |  \\ \\_______\\\\ \\__\\ \\__\\\\ \\_______\\ ____\\_\\  \\  ____\\_\\  \\ ",
				"  \\___|\\___/ |_| |_|   \\|_______| \\|__|\\|__| \\|_______||\\_________\\|\\_________\\",
				"                                                        \\|_________|\\|_________|"
			};

			Rysunek rNapis(napis);
			int rodzajGry = 0;
			int iloscBotow = 0;
			int stanTury;
			int kolorGracza = 0;
			stringstream komunikat;
			stringstream tekst;
			COORD punkt = { 40,10 };
			string sKomunikat;
			int nowaGlebokosc;

			while (kontynuuj) {

				switch (krokProgramu) {

				case 0:
					system("cls");
					rNapis.Rysuj();
					cout << "Autor: Oliwer Sobolewski" << endl << endl;;

					cout << setw(30) << "" << "Witaj!" << endl << endl << setw(30) << "" << "Wpisz:" << endl;
					cout << setw(20) << "" << "1 - aby rozpoczac gre" << endl;
					cout << setw(20) << "" << "2 - aby przelaczyc pelny ekran" << endl;
					cout << setw(20) << "" << "3 - aby zmienic glebokosc przeszukiwania bota" << endl;
					cout << setw(20) << "" << "4 - aby wyjsc z programu" << endl;


					krokProgramu = wczytajWartosc<int>(cin, 1, 4);
					break;
				case 1:
					system("cls");

					rodzajGry = 0;
					cout << endl << endl << endl << endl;
					cout << setw(30) << "" << "Wybierz rodzaj gry:" << endl;
					cout << setw(20) << "" << "1 - Czlowiek vs Bot" << endl;
					cout << setw(20) << "" << "2 - Czlowiek vs Czlowiek" << endl;
					cout << setw(20) << "" << "3 - Bot vs Bot" << endl;

					rodzajGry = wczytajWartosc<int>(cin, 1, 3);

					iloscBotow = 0;

					switch (rodzajGry) {
					case 1:
						iloscBotow = 1;

						cout << setw(30) << "" << "Wybierz kolor:" << endl;
						cout << setw(20) << "" << "1 - Biale" << endl;
						cout << setw(20) << "" << "2 - Czarne" << endl;

						kolorGracza = wczytajWartosc<int>(cin, 1, 2) - 1;
						break;
					case 2:

						iloscBotow = 0;
						break;
					case 3:
						iloscBotow = 2;
						break;
					}

					do
					{
						handlerGry.InicjalizujGre(iloscBotow, kolorGracza);

						do {
							stanTury = handlerGry.WykonajTure();
						} while (stanTury == -1);



					} while (stanTury == 1);

					krokProgramu = 0;
					break;
				case 2:
					uiHandler.PrzelaczFullscreen();
					krokProgramu = 0;
					break;
				case 3:
					komunikat.clear();
					tekst.clear();
					komunikat << "Obecna glebokosc przeszukiwania: ";
					komunikat << handlerGry.GetGlebokoscPrzeszukiwania();
					komunikat << ". Podaj nowa glebokosc z zakresu od 1 do 10";
					nowaGlebokosc = -1;
					do
					{
						tekst.clear();
						getline(komunikat, sKomunikat);
						tekst << uiHandler.WyswietlZapytanie(sKomunikat, 1,punkt, true);
						tekst >> nowaGlebokosc;

					} while (nowaGlebokosc > 10 || nowaGlebokosc < 1);

					handlerGry.SetGlebokosc(nowaGlebokosc);
					krokProgramu = 0;
					break;
				case 4:
				case 100:
					kontynuuj = false;
					break;
				default:
					blad = 1;
					krokProgramu = 0;
					break;

				}
			}
		}

		catch (const std::exception& e)
		{
			cout << e.what();
		}
	}

	return EXIT_SUCCESS;
}

