#include "Gracz.h"
#include "DodatkoweFunkcje.h"
#include "UIHandler.h"
#include <sstream>
#include <iomanip>
#include "HandlerGry.h"

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

int Gracz::EwaluujPlansze() {
	int H = 0;
	int G = 0;
	int S = 0;
	int W = 0;
	int P = 0;

	for (int i = 0; i < paPlansza->iWymiaryPlanszy; i++) {
		for (int j = 0; j < paPlansza->iWymiaryPlanszy; j++) {
			if (!(*paPlansza)[i][j].Puste())
			{
				switch ((*paPlansza)[i][j].GetFigura()->GetTyp()){
				case TypFigury::bPion:
					P++;
					break;
				case TypFigury::cPion:
					P--;
					break;
				case TypFigury::bGoniec:
					G++;
					break;
				case TypFigury::cGoniec:
					G--;
					break;
				case TypFigury::bKon:
					S++;
					break;
				case TypFigury::cKon:
					S--;
					break;
				case TypFigury::bKrolowa:
					H++;
					break;
				case TypFigury::cKrolowa:
					H--;
					break;
				case TypFigury::bWieza:
					W++;
					break;
				case TypFigury::cWieza:
					W--;
					break;
				}
			}
		}
	}

	int wartoscMaterialu = H * 9 + W * 5 + S * 3 + G * 3 + P;
	int kolor = handlerGry->GetTuraGracza() == 0 ? 1 : -1;
	int wartoscMobilnosci = wagaMobilnosci * (handlerGry->GetGracz(0)->GetRuchy().size() + handlerGry->GetGracz(1)->GetRuchy().size()*-1);

	iWartoscPlanszy = wartoscMaterialu*2 + wartoscMobilnosci;
	if (GetHandlerGry()->GetSzach()) {
		switch (GetHandlerGry()->GetLiczbaSzachujacych()) {
		case 0:
			break;
		case 1:
			iWartoscPlanszy += 0 * kolor * -1;
			break;
		case 2:
			iWartoscPlanszy += 20 * kolor * -1;
			break;
		case 3:
			iWartoscPlanszy += 30 * kolor * -1;
			break;
		case 4:
			iWartoscPlanszy += 33 * kolor * -1;
			break;
		case 5:
			iWartoscPlanszy += 37 * kolor * -1;
			break;
		case 6:
			iWartoscPlanszy += 39 * kolor * -1;
			break;
		case 7:
			iWartoscPlanszy += 40 * kolor * -1;
			break;
		}
	}
	if (GetHandlerGry()->GetMat()) {
		iWartoscPlanszy = INT16_MAX*kolor*-1;
	}
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
			cout << "Ktora figure chcesz ruszyc? Wpisz pole (np. 'A3', 'B3 B5'). Wpisz 'sur' aby poddac rozgrywke, 'cls' aby odswiezyc wyswietlanie i 'f' zeby przelaczyc pelny ekran." << endl;
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

				string decyzja;
				COORD poz = { paPlansza->getSzerokoscBuforu() + paPlansza->iWymiaryPlanszy / 2 * paPlansza->getSzerokoscPola(),paPlansza->iWymiaryPlanszy / 2 * paPlansza->getWysokoscPola() + 3 };

				do
				{
					decyzja = uiHandler.WyswietlZapytanie("Czy na pewno? (y/n)", 1, poz, true);
					ToLower(decyzja);
				} while (decyzja != "y" && decyzja != "yes" && decyzja != "n" && decyzja != "no");

				bool koniec = false;

				koniec = decyzja == "y" ? 1 : decyzja == "yes" ? 1 : 0;

				if (koniec)
				{
					return nullptr;
				}
				else {
					system("cls");
					handlerGry->RysujPlansze();
					handlerGry->WyswietlInterfejs();
					continue;
				}	
			}

			else if (indeksPola == "cls") {
				system("cls");
				handlerGry->RysujPlansze();
				handlerGry->WyswietlInterfejs();

				continue;
			}
			else if (indeksPola == "f") {
				uiHandler.PrzelaczFullscreen();
				cout << CZYSCLINIE;
				uiHandler.PrzesunKursor(0, -1);
				cout << CZYSCLINIE;
				uiHandler.PrzesunKursor(0, -1);
				continue;
			}
			else if (indeksPola == "c") {
				handlerGry->CofnijRuch(false);
				system("cls");
				handlerGry->RysujPlansze();
				handlerGry->WyswietlInterfejs();
				break;
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

			cout << CZYSCLINIE << setw(paPlansza->getSzerokoscBuforu()) << "" << "Na ktore pole chcesz sie udac? Wpisz pole (np. A3). Wpisz 'a' lub dowolny znak zeby anulowac." << endl;
			drugiTeksst = true;

			if (indeksPolaDo == "")
			{
				cout << setw(paPlansza->getSzerokoscBuforu()) << "";
				indeksPolaDo = wczytajWartosc<string>(cin);
				ToLower(indeksPolaDo);
				if (indeksPolaDo == "a")
				{
					throw exception("");
				}
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
