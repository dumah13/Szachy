#include "HandlerGry.h"
#include "DodatkoweFunkcje.h"
#include "UIHandler.h"

HandlerGry::HandlerGry(int _iIloscBotow, Plansza* _plansza) :
	gGracze{},
	pPlansza(_plansza),
	historiaRuchow{}
{
	int iloscLudzkichGraczy = 2;
	for (int i=0; i < iloscLudzkichGraczy; i++) {
		gGracze[i] = new Gracz(pPlansza, i);
	}
}

HandlerGry::~HandlerGry() {
	for (int i=0; i < 2; i++) {
		if (gGracze[i]) { delete gGracze[i]; }
	}
	if (pPlansza) {
		delete pPlansza;
	}
}

Wektor HandlerGry::WykonajRuch(Ruch* _pRuch)
{
	Ruch ruch = *(_pRuch);
	historiaRuchow.push_back(ruch);
	Wektor _do = ruch.GetDo();

	if (ruch.GetSpecjalne()) {

		//roszada
		if (abs((int)ruch.GetTypFigury()) == (int)TypFigury::bWieza) {
			Wektor kierunek(0, -sgn(ruch.GetDo().y - ruch.GetZ().y));
			_do = _do + kierunek;

			int x = ruch.GetDo().x;
			int y = ruch.GetDo().y;

			Figura* krol = (*pPlansza)[x][y].GetFigura();

			(*pPlansza)[x][y].ZdejmijFigure();

			Wektor pozKrola = _do + kierunek;

			(*pPlansza)[pozKrola.x][pozKrola.y].UstawFigure(krol);
			uiHandler.OdswiezPole(x, y);
			uiHandler.OdswiezPole(pozKrola.x, pozKrola.y);

		}

		//en passant
		else if (abs((int)ruch.GetTypFigury()) == (int)TypFigury::bPion && ruch.GetZbicie()) {
			int x = ruch.GetDo().x - sgn((int)ruch.GetTypFigury());
			int y = ruch.GetDo().y;
			enPassant = nullptr;

			(*pPlansza)[x][y].UsunFigure();
			uiHandler.OdswiezPole(x, y);
		}
	}
	else if (ruch.GetZbicie()) {
		int x = ruch.GetDo().x;
		int y = ruch.GetDo().y;

		(*pPlansza)[x][y].UsunFigure();
	}

	if (ruch.GetAwans()) {
		int x = ruch.GetZ().x;
		int y = ruch.GetZ().y;
		int kolor = (int)(*pPlansza)[x][y].GetFigura()->GetTyp();

		(*pPlansza)[x][y].UsunFigure();

		Figura figura((TypFigury)((int)TypFigury::bKrolowa * kolor), (*pPlansza).sSciezkaZasobow + "symbole.txt");

		(*pPlansza)[x][y].UstawFigure(figura);
	}

	int x = ruch.GetZ().x;
	int y = ruch.GetZ().y;
	Figura* figura = (*pPlansza)[x][y].GetFigura();

	(*pPlansza)[x][y].ZdejmijFigure();

	int xnowe = _do.x;
	int ynowe = _do.y;

	(*pPlansza)[xnowe][ynowe].UstawFigure(figura);
	uiHandler.OdswiezPole(x, y);
	uiHandler.OdswiezPole(xnowe, ynowe);

	if (enPassant != nullptr) {
		enPassant->SetPozycjaStartowa(0);
		enPassant = nullptr;
	}

	if ((*pPlansza)[xnowe][ynowe].GetFigura()->GetPozycjaStartowa()) {
		if (abs((int)ruch.GetTypFigury()) == (int)TypFigury::bPion && ruch.GetSpecjalne() && !ruch.GetZbicie()) {
			(*pPlansza)[xnowe][ynowe].GetFigura()->SetPozycjaStartowa(2);
			enPassant = (*pPlansza)[xnowe][ynowe].GetFigura();
		}
		else
		(*pPlansza)[xnowe][ynowe].GetFigura()->SetPozycjaStartowa(0);
	}

	return _do;
}


void HandlerGry::InicjalizujGre(int _iIloscBotow)
{
	for (int i=0; i < 2; i++) {
		if (gGracze[i]) { delete gGracze[i]; }
	}
	int iloscLudzkichGraczy = 2;
	if (pPlansza) {
		delete pPlansza;
	}

	system("cls");

	Plansza* ptr = new Plansza();
	pPlansza = ptr;
	pPlansza->wczytajUstawienie(ustawienieBialeDol);
	pPlansza->RysujPlansze();
	
	uiHandler.Init(pPlansza, true);

	for (int i=0; i < iloscLudzkichGraczy; i++) {
		gGracze[i] = new Gracz(pPlansza, i);
	}

	iLicznikTur = 0;
	iIloscBotow = 0;
	bSzach = false;
	iTuraGracza = 0;

	historiaRuchow.clear();
}


int HandlerGry::WykonajTure()
{
	for (int i = 0; i < pPlansza->iWymiaryPlanszy; i++) {
		for (int j = 0; j < pPlansza->iWymiaryPlanszy; j++) {
			if (!(*pPlansza)[i][j].Puste())
			{
				int poz[2] = { i,j };
				(*pPlansza)[i][j].GetFigura()->sprawdzRuchy(poz, *pPlansza);
			}
		}
	}

	iZwyciezca = 1 - iTuraGracza;

	SprawdzLegalneRuchyKrola(iTuraGracza);

	if (SprawdzSzach()) {
		SprawdzLegalneRuchy(iTuraGracza);
	}

	Ruch* ruch = gGracze[iTuraGracza]->WybierzRuch();

	

	if (ruch == nullptr) {
		return ZakonczGre();
	}

	if (SprawdzSzach()) {
		cout << "szach";
	}

	WykonajRuch(ruch);

	WyswietlInterfejs();

	iTuraGracza = iTuraGracza == 0 ? 1 : 0;

	return -1;
}


void HandlerGry::WyswietlInterfejs()
{
	// TODO: Dodaj kod implementacji w tym miejscu.
}


void HandlerGry::SprawdzLegalneRuchyKrola(int _iKolorGracza)
{
	int kolor = _iKolorGracza == 0 ? 1 : -1;
	int xKrola;
	int yKrola;
	vector<Wektor> mozPozKrola;


	for (int i = 0; i < pPlansza->iWymiaryPlanszy; i++) {
		for (int j = 0; j < pPlansza->iWymiaryPlanszy; j++) {
			if (!(*pPlansza)[i][j].Puste())
			{
				if ((int)(*pPlansza)[i][j].GetFigura()->GetTyp() == (int)TypFigury::bKrol * kolor) {
					xKrola = i;
					yKrola = j;
					for (int k = 0; k < (*pPlansza)[i][j].GetFigura()->GetRuchy().size(); k++) {
						mozPozKrola.push_back((*pPlansza)[i][j].GetFigura()->GetRuchy()[k].GetDo());
					}
					break;
				}
			}
		}
	}

	for (int i = 0; i < pPlansza->iWymiaryPlanszy; i++) {
		for (int j = 0; j < pPlansza->iWymiaryPlanszy; j++) {
			if (!(*pPlansza)[i][j].Puste() && sgn((int)(*pPlansza)[i][j].GetFigura()->GetTyp()) == kolor*(-1))
			{
				for (int k = 0; k < (*pPlansza)[i][j].GetFigura()->GetRuchy().size(); k++) {
					for (int l = 0; l < mozPozKrola.size(); l++)
					{
						if (abs((int)(*pPlansza)[i][j].GetFigura()->GetTyp()) == (int)TypFigury::bPion) {
							Wektor _do = (*pPlansza)[i][j].GetFigura()->GetRuchy()[0].GetZ();
							_do.x -= kolor;
							if (mozPozKrola[l].x == _do.x && (mozPozKrola[l].y == _do.y + 1 || mozPozKrola[l].y == _do.y - 1)) {
								(*pPlansza)[xKrola][yKrola].GetFigura()->GetRuchy().erase((*pPlansza)[xKrola][yKrola].GetFigura()->GetRuchy().begin() + l);
								mozPozKrola.erase(mozPozKrola.begin() + l--);
							}
						}
						else if ((*pPlansza)[i][j].GetFigura()->GetRuchy()[k] == mozPozKrola[l]) {
							(*pPlansza)[xKrola][yKrola].GetFigura()->GetRuchy().erase((*pPlansza)[xKrola][yKrola].GetFigura()->GetRuchy().begin() + l);
							mozPozKrola.erase(mozPozKrola.begin() + l--);
						}
					}
				}
			}
		}
	}
}

void HandlerGry::SprawdzLegalneRuchy(int _iKolorGracza){

	for (int i = 0; i < pPlansza->iWymiaryPlanszy; i++) {
		for (int j = 0; j < pPlansza->iWymiaryPlanszy; j++) {
			if (!(*pPlansza)[i][j].Puste())
			{
				for (int k = 0; k < (*pPlansza)[i][j].GetFigura()->GetRuchy().size(); k++) {
					vector<Figura*> zaktualizowaneFigury;
					vector<Wektor> pozycjeFigur;
					int kolor = _iKolorGracza == 0 ? 1 : -1;

					Figura* figuraZ = (*pPlansza)[i][j].GetFigura();
					(*pPlansza)[i][j].ZdejmijFigure();

					Figura* figuraDo = nullptr;

					if (figuraZ->GetRuchy()[k].GetZbicie() || (figuraZ->GetRuchy()[k].GetSpecjalne() && abs((int)figuraZ->GetRuchy()[k].GetTypFigury()) == (int)TypFigury::bWieza)) {
						int x = figuraZ->GetRuchy()[k].GetDo().x;
						int y = figuraZ->GetRuchy()[k].GetDo().y;
						figuraDo = (*pPlansza)[x][y].GetFigura();

						(*pPlansza)[x][y].ZdejmijFigure();

					}

					int x = figuraZ->GetRuchy()[k].GetDo().x;
					int y = figuraZ->GetRuchy()[k].GetDo().y;
					int poz[2] = { x,y };

					(*pPlansza)[x][y].UstawFigure(figuraZ);

					for (int l = 0; l < pPlansza->iWymiaryPlanszy; l++) {
						for (int m = 0; m < pPlansza->iWymiaryPlanszy; m++) {
							if (!(*pPlansza)[l][m].Puste() && (*pPlansza)[l][m].GetFigura() != figuraZ && sgn((int)(*pPlansza)[l][m].GetFigura()->GetTyp()) == kolor*-1) {
								for (int n = 0; n < (*pPlansza)[l][m].GetFigura()->GetRuchy().size(); n++) {
									if ((*pPlansza)[l][m].GetFigura()->GetRuchy()[n] == figuraZ->GetRuchy()[k].GetDo()) {
										int poz2[2] = { l,m };
										(*pPlansza)[l][m].GetFigura()->sprawdzRuchy(poz2, *pPlansza);
										zaktualizowaneFigury.push_back((*pPlansza)[l][m].GetFigura());

										Wektor wek = { l,m };
										pozycjeFigur.push_back(wek);
										break;
									}
								}
							}
						}
					}

					if (SprawdzSzach()) {
						(*pPlansza)[x][y].GetFigura()->GetRuchy().erase((*pPlansza)[x][y].GetFigura()->GetRuchy().begin() + k--);
					}

					(*pPlansza)[x][y].ZdejmijFigure();
					if (figuraDo)
					{
						(*pPlansza)[x][y].UstawFigure(figuraDo);
					}
					(*pPlansza)[i][j].UstawFigure(figuraZ);

					for (int l = 0; l < zaktualizowaneFigury.size(); l++) {
						int pozN[2] = { pozycjeFigur[l].x, pozycjeFigur[l].y };
						zaktualizowaneFigury[l]->sprawdzRuchy(pozN, *pPlansza);
					}
				}
			}
		}
	}
}

int HandlerGry::SprawdzSzach()
{
	for (int i = 0; i < pPlansza->iWymiaryPlanszy; i++) {
		for (int j = 0; j < pPlansza->iWymiaryPlanszy; j++) {
			if (!(*pPlansza)[i][j].Puste())
			{
				for (int k = 0; k < (*pPlansza)[i][j].GetFigura()->GetRuchy().size(); k++) {
					if (abs((int)(*pPlansza)[i][j].GetFigura()->GetRuchy()[k].GetZbita()) == (int)TypFigury::bKrol) {
						bSzach = true;
						return 1;
					}
				}
			}
		}
	}
	bSzach = false;
	return 0;
}

int HandlerGry::SprawdzMat() {
	return 1;
}


int HandlerGry::ZakonczGre()
{
	string decyzja;
	string komunikat = "Wygrywaja ";
	komunikat += iZwyciezca == 1 ? "czarne! " : "biale! ";
	komunikat += gGracze[iZwyciezca]->CzyLudzki() ? "Gratulacje!" : "Na nastepnych zawodach go pokonasz!";
	komunikat += " Czy chcesz zagrac ponownie z tym samym przeciwnikiem? (y/n)";

	COORD poz = { pPlansza->getSzerokoscBuforu() + pPlansza->iWymiaryPlanszy / 2 * pPlansza->getSzerokoscPola(),pPlansza->iWymiaryPlanszy / 2 * pPlansza->getWysokoscPola() + 3 };

	do
	{
		decyzja = uiHandler.WyswietlZapytanie(komunikat, 1, poz, true);
		ToLower(decyzja);
	} while (decyzja != "y" && decyzja != "yes" && decyzja != "n" && decyzja != "no");

	int powtorz = false;

	powtorz = decyzja == "y" ? 1 : decyzja == "yes" ? 1 : 0;

	return powtorz;
}
