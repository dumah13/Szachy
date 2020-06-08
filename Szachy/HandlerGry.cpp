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


void HandlerGry::WykonajTure()
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

	Ruch* ruch = gGracze[iTuraGracza]->WybierzRuch();
	WykonajRuch(ruch);

	WyswietlInterefejs();

	iTuraGracza = iTuraGracza == 0 ? 1 : 0;
}


void HandlerGry::WyswietlInterefejs()
{
	// TODO: Dodaj kod implementacji w tym miejscu.
}


void HandlerGry::SprawdzLegalneRuchy(int _iKolorGracza)
{
	// TODO: Dodaj kod implementacji w tym miejscu.
}


int HandlerGry::SprawdzSzach()
{
	// TODO: Dodaj kod implementacji w tym miejscu.
	return 0;
}


int HandlerGry::ZakonczGre()
{
	// TODO: Dodaj kod implementacji w tym miejscu.
	return 0;
}
