#include "Gracz.h"
#include "DodatkoweFunkcje.h"
#include "UIHandler.h"
#include <sstream>
#include <iomanip>

vector<string> Warstwa1 =
{ ".\\........./.",
  "...\\...../...",
  ".....-|-.....",
  ".../.....\\...",
  "./.........\\.",
  ".............",
};

vector<string> Warstwa2 =
{ ">>>>>>^<<<<<<",
  ">...........<",
  ">...........<",
  ">...........<",
  ">...........<",
  ">>>>>>^<<<<<<",
};

int Gracz::GetKolor()
{
	return iKolor;
}


int Gracz::GetWartosc()
{
	return iWartoscPlanszy;
}


Ruch* Gracz::WybierzRuch()
{
	bool prawidlowyRuch = false;
	bool drugiTeksst = false;
	bool wyswietlonoUI = false;
	string indeksPola;

	while (!prawidlowyRuch)
	{
		try
		{
			cout << setw(paPlansza->getSzerokoscBuforu()) << "";
			cout << "Ktora figure chcesz ruszyc? Wpisz pole (np. 'A3', 'B3 B5'). Mozesz tez wpisac 'sur' aby poddac rozgrywke i 'cls' aby odswiezyc wyswietlanie." << endl;
			wyswietlonoUI = false;
			stringstream ss;

			cout << setw(paPlansza->getSzerokoscBuforu()) << "";
			ss = wczytajWartosc<stringstream>(cin);
			string indeksPolaDo = "";

			indeksPola = wczytajWartosc<string>(ss);
			ToLower(indeksPola);

			if (indeksPola == "sur") {
				cout << CZYSCLINIE;
				uiHandler.PrzesunKursor(0, -1);
				cout << CZYSCLINIE;
				uiHandler.PrzesunKursor(0, -1);
				return nullptr;
			}

			else if (indeksPola == "cls") {
				uiHandler.OdswiezPlansze();
				cout << CZYSCLINIE;
				uiHandler.PrzesunKursor(0, -1);
				cout << CZYSCLINIE;
				uiHandler.PrzesunKursor(0, -1);
				continue;
			}

			indeksPolaDo = wczytajWartosc<string>(ss);

			if ((*paPlansza)[indeksPola].Puste()) {
				throw exception("Na danym polu nie ma zadnej figury. Wybierz inne pole.");
			}

			Figura* figura = (*paPlansza)[indeksPola].GetFigura();
			int kolorFigury = (int)figura->GetTyp() < 0 ? 1 : 0;

			if (kolorFigury != iKolor) {
				throw exception("Na danym polu stoi figura przeciwnika. Wybierz inne pole.");
			}

			uiHandler.DodajWarstweUI(Warstwa2, indeksPola);
			uiHandler.OdswiezPole(indeksPola);
			vector<Ruch>& ruchy = figura->GetRuchy();

			for (int i = 0; i < figura->GetRuchy().size(); i++) {
				uiHandler.DodajWarstweUI(Warstwa1, ruchy[i].GetDo().x, ruchy[i].GetDo().y);
				uiHandler.OdswiezPole(ruchy[i].GetDo().x, ruchy[i].GetDo().y);
			}

			wyswietlonoUI = true;

			cout << CZYSCLINIE << setw(paPlansza->getSzerokoscBuforu()) << "" << "Na ktore pole chcesz sie udac? Wpisz pole (np. A3)." << endl;
			drugiTeksst = true;


			if (indeksPolaDo == "")
			{
				cout << setw(paPlansza->getSzerokoscBuforu()) << "";
				indeksPolaDo = wczytajWartosc<string>(cin);
			}
			else {
				uiHandler.PrzesunKursor(0, 1);
			}
			Ruch* wybranyRuch = nullptr;

			for (int i = 0; i < ruchy.size(); i++) {
				if (ruchy[i] == indeksPolaDo) {
					wybranyRuch = &ruchy[i];
					break;
				}
			}

			if (!wybranyRuch) {
				throw exception("Ruch na dane pole jest niemozliwy dla wybranej figury.");
			}

			for (int i = 0; i < ruchy.size(); i++) {
				uiHandler.UsunWarsteUI(ruchy[i].GetDo().x, ruchy[i].GetDo().y);
				uiHandler.OdswiezPole(ruchy[i].GetDo().x, ruchy[i].GetDo().y);
			}

			uiHandler.UsunWarsteUI(indeksPola);
			uiHandler.OdswiezPole(indeksPola);

			cout << CZYSCLINIE;
			uiHandler.PrzesunKursor(0, -1);
			cout << CZYSCLINIE;
			uiHandler.PrzesunKursor(0, -1);
			cout << CZYSCLINIE;
			uiHandler.PrzesunKursor(0, -1);
			cout << CZYSCLINIE;
			uiHandler.PrzesunKursor(0, -1);
			cout << CZYSCLINIE;

			prawidlowyRuch = true;
			return wybranyRuch;
		}
		catch (const std::exception& e)
		{
			if (drugiTeksst) {
				cout << CZYSCLINIE;
				uiHandler.PrzesunKursor(0, -1);
				cout << CZYSCLINIE;
				uiHandler.PrzesunKursor(0, -1);
			}
			cout << CZYSCLINIE;

			cout << setw(paPlansza->getSzerokoscBuforu()) << "";
			cout << e.what() << endl;
			uiHandler.PrzesunKursor(0, -2);
			cout << CZYSCLINIE;
			uiHandler.PrzesunKursor(0, -1);
			drugiTeksst = false;

			if (wyswietlonoUI) {
				vector<Ruch>& ruchy = (*paPlansza)[indeksPola].GetFigura()->GetRuchy();

				for (int i = 0; i < ruchy.size(); i++) {
					uiHandler.UsunWarsteUI(ruchy[i].GetDo().x, ruchy[i].GetDo().y);
					uiHandler.OdswiezPole(ruchy[i].GetDo().x, ruchy[i].GetDo().y);
				}

				uiHandler.UsunWarsteUI(indeksPola);
				uiHandler.OdswiezPole(indeksPola);
			}

			continue;
		}
	}
	return nullptr;
}
