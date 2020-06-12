#include "HandlerGry.h"
#include "DodatkoweFunkcje.h"
#include "Bot.h"
#include "UIHandler.h"
#include <iomanip>

HandlerGry::HandlerGry(int _iIloscBotow, Plansza* _plansza, int kolorGracza) :
	gGracze{},
	pPlansza(_plansza),
	historiaRuchow{}
{
	int iloscLudzkichGraczy = 2 - _iIloscBotow;
	if (iloscLudzkichGraczy == 1) {
		gGracze[kolorGracza] = new Gracz(pPlansza, this, kolorGracza);
		gGracze[1 - kolorGracza] = new Bot(pPlansza, this, 1 - kolorGracza);
	}
	else {
		for (int i = 0; i < iloscLudzkichGraczy; i++) {
			gGracze[i] = new Gracz(pPlansza, this, i);
		}
		for (int i = 1; i >= iloscLudzkichGraczy; i--) {
			gGracze[i] = new Bot(pPlansza, this, i);
		}
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

Wektor HandlerGry::WykonajRuch(Ruch* _pRuch, bool _widoczne)
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
			if (_widoczne)
			{
				uiHandler.OdswiezPole(x, y);
				uiHandler.OdswiezPole(pozKrola.x, pozKrola.y);
			}

		}

		//en passant
		else if (abs((int)ruch.GetTypFigury()) == (int)TypFigury::bPion && ruch.GetZbicie()) {
			int x = ruch.GetDo().x - sgn((int)ruch.GetTypFigury());
			int y = ruch.GetDo().y;
			enPassant = {-1,-1};

			(*pPlansza)[x][y].UsunFigure();
			if (_widoczne)
			{
				uiHandler.OdswiezPole(x, y);
			}
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
	if (_widoczne)
	{
		uiHandler.OdswiezPole(x, y);
		uiHandler.OdswiezPole(xnowe, ynowe);
	}
	Wektor test = { -1,-1 };
	if (!(enPassant == test)) {
		(*pPlansza)[enPassant.x][enPassant.y].GetFigura()->SetPozycjaStartowa(0);
		enPassant = { -1,-1 };
	}

	if ((*pPlansza)[xnowe][ynowe].GetFigura()->GetPozycjaStartowa()) {
		if (abs((int)ruch.GetTypFigury()) == (int)TypFigury::bPion && ruch.GetSpecjalne() && !ruch.GetZbicie()) {
			(*pPlansza)[xnowe][ynowe].GetFigura()->SetPozycjaStartowa(2);
			enPassant = { xnowe,ynowe };
		}
		else
		(*pPlansza)[xnowe][ynowe].GetFigura()->SetPozycjaStartowa(0);
	}

	return _do;
}

void HandlerGry::SymulujRuch(Ruch* _pRuch, bool _sprawdzLegalnosc) {

	int kolor = _pRuch->GetKolor() == 0 ? 1 : -1;
	Wektor test = { -1,-1 };

	if (!(enPassant == test) && sgn((int)(*pPlansza)[enPassant.x][enPassant.y].GetFigura()->GetTyp()) == kolor) {
		enPassant = { -1,-1 };
	}

	WykonajRuch(_pRuch, false);

	


	if (_sprawdzLegalnosc)
	{
		iLiczbaRuchow = 0;
		iLiczbaRuchowPrzeciwnika = 0;

		for (int i = 0; i < pPlansza->iWymiaryPlanszy; i++) {
			for (int j = 0; j < pPlansza->iWymiaryPlanszy; j++) {
				if (!(*pPlansza)[i][j].Puste())
				{
					int poz[2] = { i,j };
					(*pPlansza)[i][j].GetFigura()->sprawdzRuchy(poz, *pPlansza);
				}
			}
		}


		SprawdzLegalneRuchy(iTuraGracza);
		
		//SprawdzLegalneRuchy(1 - iTuraGracza);

		dynamic_cast<Bot*>(gGracze[iTuraGracza])->GetRuchy().clear();

		for (int i = 0; i < pPlansza->iWymiaryPlanszy; i++) {
			for (int j = 0; j < pPlansza->iWymiaryPlanszy; j++) {
				if (!(*pPlansza)[i][j].Puste())
				{
					if (sgn((int)(*pPlansza)[i][j].GetFigura()->GetTyp()) == kolor)
					{
						iLiczbaRuchow += (*pPlansza)[i][j].GetFigura()->GetRuchy().size();
						for (int k = 0; k < (*pPlansza)[i][j].GetFigura()->GetRuchy().size(); k++) {
							dynamic_cast<Bot*>(gGracze[iTuraGracza])->GetRuchy().push_back(&(*pPlansza)[i][j].GetFigura()->GetRuchy()[k]);
						}
					}
					else {
						iLiczbaRuchowPrzeciwnika += (*pPlansza)[i][j].GetFigura()->GetRuchy().size();
					}
				}
			}
		}
	}

}

void HandlerGry::CofnijRuch(bool _sprawdzLegalnosc) {
	Ruch ruch = historiaRuchow.back();
	historiaRuchow.pop_back();
	//iLicznikTur--;
	//iTuraGracza = iTuraGracza == 0 ? 1 : 0;

	Wektor enPas = { -1, -1 };
	Wektor _do = ruch.GetDo();
	Wektor _z = ruch.GetZ();
	
	if (!(ruch.GetSpecjalne() && abs((int)ruch.GetTypFigury()) == (int)TypFigury::bWieza))
	{
		(*pPlansza)[_do.x][_do.y].UsunFigure();
	}

	if (ruch.GetSpecjalne()) {

		//roszada
		if (abs((int)ruch.GetTypFigury()) == (int)TypFigury::bWieza) {
			Wektor kierunek(0, -sgn(ruch.GetDo().y - ruch.GetZ().y));
			_do = _do + kierunek;

			int x = ruch.GetDo().x;
			int y = ruch.GetDo().y;

			(*pPlansza)[_do.x][_do.y].UsunFigure();

			Wektor pozKrola = _do + kierunek;

			Figura* krol = (*pPlansza)[pozKrola.x][pozKrola.y].GetFigura();
			krol->SetPozycjaStartowa(1);
			(*pPlansza)[pozKrola.x][pozKrola.y].ZdejmijFigure();


			(*pPlansza)[x][y].UstawFigure(krol);
		}

		//en passant
		else if (abs((int)ruch.GetTypFigury()) == (int)TypFigury::bPion && ruch.GetZbicie()) {
			int x = ruch.GetDo().x - sgn((int)ruch.GetTypFigury());
			int y = ruch.GetDo().y;
			Figura fig(ruch.GetZbita(), pPlansza->sSciezkaZasobow + "symbole.txt");

			fig.SetPozycjaStartowa(ruch.GetPozycjaStartowaZbitej());
			
			(*pPlansza)[x][y].UstawFigure(fig);
			enPas = { x,y };
		}
	}
	else if (ruch.GetZbicie())
	{
		Figura fig(ruch.GetZbita(), pPlansza->sSciezkaZasobow + "symbole.txt");

		fig.SetPozycjaStartowa(ruch.GetPozycjaStartowaZbitej());
		(*pPlansza)[_do.x][_do.y].UstawFigure(fig);
	}

	Figura fig(ruch.GetTypFigury(), pPlansza->sSciezkaZasobow + "symbole.txt");

	fig.SetPozycjaStartowa(ruch.GetPozycjaStartowa());

	(*pPlansza)[_z.x][_z.y].UstawFigure(fig);

	if (ruch.GetPozycjaStartowa() == 2) {
		enPas = _z;
	}

	enPassant = enPas;

	int kolor = iTuraGracza == 0 ? 1 : -1;

	if (!(gGracze[iTuraGracza])->CzyLudzki()) { dynamic_cast<Bot*>(gGracze[iTuraGracza])->GetRuchy().clear(); }

	if (_sprawdzLegalnosc)
	{
		iLiczbaRuchow = 0;
		iLiczbaRuchowPrzeciwnika = 0;

		for (int i = 0; i < pPlansza->iWymiaryPlanszy; i++) {
			for (int j = 0; j < pPlansza->iWymiaryPlanszy; j++) {
				if (!(*pPlansza)[i][j].Puste())
				{
					int poz[2] = { i,j };
					(*pPlansza)[i][j].GetFigura()->sprawdzRuchy(poz, *pPlansza);
				}
			}
		}


		//SprawdzLegalneRuchyKrola(iTuraGracza);
		SprawdzLegalneRuchy(iTuraGracza);
		//SprawdzLegalneRuchyKrola(1 - iTuraGracza);
		//SprawdzLegalneRuchy(1 - iTuraGracza);

		dynamic_cast<Bot*>(gGracze[iTuraGracza])->GetRuchy().clear();

		for (int i = 0; i < pPlansza->iWymiaryPlanszy; i++) {
			for (int j = 0; j < pPlansza->iWymiaryPlanszy; j++) {
				if (!(*pPlansza)[i][j].Puste())
				{
					if (sgn((int)(*pPlansza)[i][j].GetFigura()->GetTyp()) == kolor)
					{
						iLiczbaRuchow += (*pPlansza)[i][j].GetFigura()->GetRuchy().size();
						for (int k = 0; k < (*pPlansza)[i][j].GetFigura()->GetRuchy().size(); k++) {
							dynamic_cast<Bot*>(gGracze[iTuraGracza])->GetRuchy().push_back(&(*pPlansza)[i][j].GetFigura()->GetRuchy()[k]);
						}
					}
					else {
						iLiczbaRuchowPrzeciwnika += (*pPlansza)[i][j].GetFigura()->GetRuchy().size();
					}
				}
			}
		}
	}
}

void HandlerGry::InicjalizujGre(int _iIloscBotow, int _kolorGracza)
{
	for (int i=0; i < 2; i++) {
		if (gGracze[i]) { delete gGracze[i]; }
	}
	if (pPlansza) {
		delete pPlansza;
	}

	bWyswietlonyInterfejs = false;
	system("cls");

	Plansza* ptr = new Plansza();
	pPlansza = ptr;
	pPlansza->wczytajUstawienie(ustawienieBialeDol);
	pPlansza->RysujPlansze();
	
	uiHandler.Init(pPlansza);

	int iloscLudzkichGraczy = 2 - _iIloscBotow;
	if (iloscLudzkichGraczy == 1) {
		gGracze[_kolorGracza] = new Gracz(pPlansza, this, _kolorGracza);
		gGracze[1 - _kolorGracza] = new Bot(pPlansza, this, 1 - _kolorGracza);
	}
	else {
		for (int i = 0; i < iloscLudzkichGraczy; i++) {
			gGracze[i] = new Gracz(pPlansza, this, i);
		}
		for (int i = 1; i >= iloscLudzkichGraczy; i--) {
			gGracze[i] = new Bot(pPlansza, this, i);
		}
	}

	iLicznikTur = 1;
	iIloscBotow = 0;
	bSzach = false;
	iTuraGracza = 0;

	historiaRuchow.clear();
}

void HandlerGry::RysujPlansze() {
	if (pPlansza) {
		pPlansza->RysujPlansze();
	}
}

int HandlerGry::WykonajTure()
{
	int kolor = iTuraGracza == 0 ? 1 : -1;

	if (!(gGracze[iTuraGracza])->CzyLudzki()){ dynamic_cast<Bot*>(gGracze[iTuraGracza])->GetRuchy().clear(); }

	for (int i = 0; i < pPlansza->iWymiaryPlanszy; i++) {
		for (int j = 0; j < pPlansza->iWymiaryPlanszy; j++) {
			if (!(*pPlansza)[i][j].Puste())
			{
				int poz[2] = { i,j };
				(*pPlansza)[i][j].GetFigura()->sprawdzRuchy(poz, *pPlansza);

			}
		}
	}

	if (iLicznikTur >= 200) {
		iZwyciezca = -1;
		return ZakonczGre();
	}

	iZwyciezca = 1 - iTuraGracza;

	//SprawdzLegalneRuchyKrola(iTuraGracza);
	SprawdzLegalneRuchy(iTuraGracza);
	
	if (!gGracze[iTuraGracza]->CzyLudzki()) {
		for (int i = 0; i < pPlansza->iWymiaryPlanszy; i++) {
			for (int j = 0; j < pPlansza->iWymiaryPlanszy; j++) {
				if (!(*pPlansza)[i][j].Puste())
				{
					if (sgn((int)(*pPlansza)[i][j].GetFigura()->GetTyp()) == kolor)
					{
						for (int k = 0; k < (*pPlansza)[i][j].GetFigura()->GetRuchy().size(); k++) {
							dynamic_cast<Bot*>(gGracze[iTuraGracza])->GetRuchy().push_back(&(*pPlansza)[i][j].GetFigura()->GetRuchy()[k]);
						}
					}
				}
			}
		}


	}
	
	SprawdzSzach(iTuraGracza);

	if (SprawdzMat()) {
		return ZakonczGre();
	}

	gGracze[iTuraGracza]->EwaluujPlansze();

	if (bWyswietlonyInterfejs)
	{
		WyczyscInterfejs();
		bWyswietlonyInterfejs = false;
	}

	if (/*gGracze[iTuraGracza]->CzyLudzki()*/true)
	{
		WyswietlInterfejs();
		bWyswietlonyInterfejs = true;
	}

	Ruch* ruch = gGracze[iTuraGracza]->WybierzRuch();


	if (ruch == nullptr) {
		return ZakonczGre();
		//return -1;
	}

	if (SprawdzSzach(iTuraGracza) && gGracze[iTuraGracza]->CzyLudzki()) {
		cout << "szach";
	}

	WykonajRuch(ruch);

	iTuraGracza = iTuraGracza == 0 ? 1 : 0;
	iLicznikTur++;

	return -1;
}

void HandlerGry::WyczyscInterfejs() {
	uiHandler.PrzesunKursor(0, -1);
	cout << CZYSCLINIE;
	uiHandler.PrzesunKursor(0, -1);
	cout << CZYSCLINIE;
	uiHandler.PrzesunKursor(0, -1);
	cout << CZYSCLINIE;
	uiHandler.PrzesunKursor(0, -1);
	cout << CZYSCLINIE;
}

void HandlerGry::WyswietlInterfejs()
{
	cout << setw(pPlansza->getSzerokoscBuforu()) << "";
	cout << left << setw(15) << "Tura gracza: " << left << setw(pPlansza->iWymiaryPlanszy*pPlansza->getSzerokoscPola() - 35) << (iTuraGracza == 0 ? "bialy" : "czarny") << setw(15) << left << "Tura: " << setw(5) << right << iLicznikTur;
	cout << endl << setw(pPlansza->getSzerokoscBuforu()) << "";
	cout << left << setw(30) << "Liczba mozliwych ruchow: " << left << setw(pPlansza->iWymiaryPlanszy * pPlansza->getSzerokoscPola() - 50) << iLiczbaRuchow  << setw(15) << left << "Wartosc: " << setw(5) << right << gGracze[iTuraGracza]->GetWartosc();
	cout << endl << setw(pPlansza->getSzerokoscBuforu()) << "";
	cout << left << setw(15) << "Ostatni ruch: ";
	//cout << left << setw(pPlansza->iWymiaryPlanszy * pPlansza->getSzerokoscPola() - 35);
	if (!historiaRuchow.empty())
	{
		WypiszDaneRuchu(&historiaRuchow.back());
	}
	else {
		cout << "Historia ruchow jest pusta";
	}
	cout << endl << setw(pPlansza->getSzerokoscBuforu()) << "";
	cout << (bSzach ? "SZACH!" : "");
	cout << endl;
}

string HandlerGry::TypDoString(TypFigury _typ) {
	string nazwa;

	switch (_typ) {
	case TypFigury::bPion:
	case TypFigury::cPion:
		nazwa = "Pion";
		break;
	case TypFigury::bGoniec:
	case TypFigury::cGoniec:
		nazwa = "Goniec";
		break;
	case TypFigury::bKon:
	case TypFigury::cKon:
		nazwa = "Kon";
		break;
	case TypFigury::bKrol:
	case TypFigury::cKrol:
		nazwa = "Krol";
		break;
	case TypFigury::bKrolowa:
	case TypFigury::cKrolowa:
		nazwa = "Krolowa";
		break;
	case TypFigury::bWieza:
	case TypFigury::cWieza:
		nazwa = "Wieza";
		break;
	default:
		nazwa = "brak";
		break;
	}
	
	return nazwa;
}

void HandlerGry::WypiszDaneRuchu(Ruch* _ruch, ostream& _os) {
	string figura;
	figura;

	_os << KonwertujIndeks(_ruch->GetZ()) << " -> " << KonwertujIndeks(_ruch->GetDo()) << right << setw(5) << (_ruch->GetAwans() ? " Awans" : "");
	_os << right << setw(5) << TypDoString(_ruch->GetTypFigury()) << right << setw(5) << (_ruch->GetZbicie() ? " Zbija: " : "")<< setw(5) << (_ruch->GetZbicie() ? "-" + TypDoString(_ruch->GetZbita()) + "-" : "");

	_os << right << setw(5) << (_ruch->GetSpecjalne() ? abs((int)_ruch->GetTypFigury()) == (int)TypFigury::bWieza ? " Roszada" : _ruch->GetZbicie() ? " En Passant" : " Podwojny" : "");
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
	//iLiczbaRuchow = 0;
	int kolor = _iKolorGracza == 0 ? 1 : -1;


	for (int i = 0; i < pPlansza->iWymiaryPlanszy; i++) {
		for (int j = 0; j < pPlansza->iWymiaryPlanszy; j++) {
			if (!(*pPlansza)[i][j].Puste() && sgn((int)(*pPlansza)[i][j].GetFigura()->GetTyp()) == kolor)
			{

				for (int k = 0; k < (*pPlansza)[i][j].GetFigura()->GetRuchy().size(); k++) {
					vector<vector<Ruch>> stareRuchy;
					vector<Wektor> pozycjeFigur;
					stareRuchy.push_back((*pPlansza)[i][j].GetFigura()->GetRuchy());
					Ruch ruch = (*pPlansza)[i][j].GetFigura()->GetRuchy()[k];
					Wektor we = { i,j };
					pozycjeFigur.push_back(we);

					if (ruch.GetSpecjalne()) {

						//roszada
						if (abs((int)ruch.GetTypFigury()) == (int)TypFigury::bWieza) {
							stareRuchy.push_back((*pPlansza)[ruch.GetDo().x][ruch.GetDo().y].GetFigura()->GetRuchy());
							pozycjeFigur.push_back(ruch.GetDo());
						}

						//en passant
						else if (abs((int)ruch.GetTypFigury()) == (int)TypFigury::bPion && ruch.GetZbicie()) {
							int x = ruch.GetDo().x - sgn((int)ruch.GetTypFigury());
							int y = ruch.GetDo().y;
							Wektor w = { x, y };

							stareRuchy.push_back((*pPlansza)[x][y].GetFigura()->GetRuchy());
							pozycjeFigur.push_back(w);
						}
					}
					else if ((*pPlansza)[i][j].GetFigura()->GetRuchy()[k].GetZbicie()) {
						stareRuchy.push_back((*pPlansza)[ruch.GetDo().x][ruch.GetDo().y].GetFigura()->GetRuchy());
						pozycjeFigur.push_back(ruch.GetDo());
					}

					SymulujRuch(&(*pPlansza)[i][j].GetFigura()->GetRuchy()[k], false);
					

					for (int l = 0; l < pPlansza->iWymiaryPlanszy; l++) {
						for (int m = 0; m < pPlansza->iWymiaryPlanszy; m++) {
							if (!(*pPlansza)[l][m].Puste() && sgn((int)(*pPlansza)[l][m].GetFigura()->GetTyp()) == kolor*-1)
							{
								int poz[2] = { l,m };
								Wektor we = { l,m };
								stareRuchy.push_back((*pPlansza)[l][m].GetFigura()->GetRuchy());
								pozycjeFigur.push_back(we);
								(*pPlansza)[l][m].GetFigura()->sprawdzRuchy(poz, *pPlansza);
							}
						}
					}

					bool usunRuch = false;

					if (SprawdzSzach(_iKolorGracza)){
						usunRuch = true;
					}

					CofnijRuch(false);

					for (int l = 0; l < stareRuchy.size(); l++) {
						int pozN[2] = { pozycjeFigur[l].x, pozycjeFigur[l].y };

						(*pPlansza)[pozycjeFigur[l].x][pozycjeFigur[l].y].GetFigura()->SetRuchy(stareRuchy[l]);
					}

					if (usunRuch) {
						(*pPlansza)[i][j].GetFigura()->GetRuchy().erase((*pPlansza)[i][j].GetFigura()->GetRuchy().begin() + k--);
					}
				}
				//iLiczbaRuchow += (*pPlansza)[i][j].GetFigura()->GetRuchy().size();
			}
		}
	}
}

/*for (int k = 0; k < (*pPlansza)[i][j].GetFigura()->GetRuchy().size(); k++) {
					vector<Figura*> zaktualizowaneFigury;
					vector<Wektor> pozycjeFigur;
					Wektor pozKrola;
					int kolor = _iKolorGracza == 0 ? 1 : -1;

					Figura* figuraZ = (*pPlansza)[i][j].GetFigura();
					(*pPlansza)[i][j].ZdejmijFigure();

					Figura* figuraDo = nullptr;
					bool roszada = (figuraZ->GetRuchy()[k].GetSpecjalne() && abs((int)figuraZ->GetRuchy()[k].GetTypFigury()) == (int)TypFigury::bWieza);

					if (figuraZ->GetRuchy()[k].GetZbicie() || roszada) {
						int x = figuraZ->GetRuchy()[k].GetDo().x;
						int y = figuraZ->GetRuchy()[k].GetDo().y;

						//enPassant
						if (figuraZ->GetRuchy()[k].GetSpecjalne() && abs((int)figuraZ->GetTyp()) == (int)TypFigury::bPion) {
							x = figuraZ->GetRuchy()[k].GetDo().x - sgn((int)figuraZ->GetRuchy()[k].GetTypFigury());
						}
						figuraDo = (*pPlansza)[x][y].GetFigura();

						(*pPlansza)[x][y].ZdejmijFigure();

					}

					int x = figuraZ->GetRuchy()[k].GetDo().x;
					int y;

					if (!roszada)
					{


						y = figuraZ->GetRuchy()[k].GetDo().y;
						pozKrola = figuraZ->GetRuchy()[k].GetDo();
					}
					else {
						Wektor kierunek(0, -sgn(figuraZ->GetRuchy()[k].GetDo().y - figuraZ->GetRuchy()[k].GetZ().y));
	

						y = figuraZ->GetRuchy()[k].GetDo().y + kierunek.y;

						pozKrola = { x, y + kierunek.y };

						(*pPlansza)[pozKrola.x][pozKrola.y].UstawFigure(figuraDo);
					}

					int poz[2] = { x,y };

					(*pPlansza)[x][y].UstawFigure(figuraZ);


					for (int l = 0; l < pPlansza->iWymiaryPlanszy; l++) {
						for (int m = 0; m < pPlansza->iWymiaryPlanszy; m++) {
							if (!(*pPlansza)[l][m].Puste() && (*pPlansza)[l][m].GetFigura() != figuraZ && sgn((int)(*pPlansza)[l][m].GetFigura()->GetTyp()) == kolor*-1) {
								for (int n = 0; n < (*pPlansza)[l][m].GetFigura()->GetRuchy().size(); n++) {
									if ((*pPlansza)[l][m].GetFigura()->GetRuchy()[n] == figuraZ->GetRuchy()[k].GetZ() || (*pPlansza)[l][m].GetFigura()->GetRuchy()[n] == pozKrola || abs((int)(*pPlansza)[l][m].GetFigura()->GetRuchy()[n].GetZbita()) == (int)TypFigury::bKrol){
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

					
					int yDoceloweStare = figuraZ->GetRuchy()[k].GetDo().y;
					int xDoceloweStare = figuraZ->GetRuchy()[k].GetDo().x;

					if (figuraZ->GetRuchy()[k].GetSpecjalne() && abs((int)figuraZ->GetTyp()) == (int)TypFigury::bPion && figuraZ->GetRuchy()[k].GetZbicie()) {
						xDoceloweStare = figuraZ->GetRuchy()[k].GetDo().x - sgn((int)figuraZ->GetRuchy()[k].GetTypFigury());
					}

					if (SprawdzSzach()) {
						
						(*pPlansza)[x][y].GetFigura()->GetRuchy().erase((*pPlansza)[x][y].GetFigura()->GetRuchy().begin() + k--);
					}

					(*pPlansza)[x][y].ZdejmijFigure();

					if (figuraDo)
					{
						if (roszada) {
							(*pPlansza)[pozKrola.x][pozKrola.y].ZdejmijFigure();
						}
						
						(*pPlansza)[xDoceloweStare][yDoceloweStare].UstawFigure(figuraDo);
					}
					(*pPlansza)[i][j].UstawFigure(figuraZ);

					for (int l = 0; l < zaktualizowaneFigury.size(); l++) {
						int pozN[2] = { pozycjeFigur[l].x, pozycjeFigur[l].y };
						zaktualizowaneFigury[l]->sprawdzRuchy(pozN, *pPlansza);
					}
				}*/

int HandlerGry::SprawdzSzach(int _iKolorGracza)
{
	int kolor = _iKolorGracza == 0 ? 1 : -1;
	for (int i = 0; i < pPlansza->iWymiaryPlanszy; i++) {
		for (int j = 0; j < pPlansza->iWymiaryPlanszy; j++) {
			if (!(*pPlansza)[i][j].Puste() && sgn((int)(*pPlansza)[i][j].GetFigura()->GetTyp()) == kolor*-1)
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
	int kolor = iTuraGracza == 0 ? 1 : -1;
	int mat = 1;
	iLiczbaRuchowPrzeciwnika = iLiczbaRuchow;
	iLiczbaRuchow = 0;

	for (int i = 0; i < pPlansza->iWymiaryPlanszy; i++) {
		for (int j = 0; j < pPlansza->iWymiaryPlanszy; j++) {
			if (!(*pPlansza)[i][j].Puste() && sgn((int)(*pPlansza)[i][j].GetFigura()->GetTyp()) == kolor)
			{
				if (!(*pPlansza)[i][j].GetFigura()->GetRuchy().empty()) {
					mat = 0;
					iLiczbaRuchow += (*pPlansza)[i][j].GetFigura()->GetRuchy().size();
				}
			}
		}
	}

	if (iLicznikTur == 1) {
		iLiczbaRuchowPrzeciwnika = iLiczbaRuchow;
	}

	return mat;
}


int HandlerGry::ZakonczGre()
{
	string decyzja;
	string komunikat = "Wygrywaja ";
	komunikat += iZwyciezca == 1 ? "czarne! " : "biale! ";
	komunikat += gGracze[iZwyciezca]->CzyLudzki() ? "Gratulacje!" : "Na nastepnych zawodach go pokonasz!";
	if (iZwyciezca == -1) {
		komunikat = "Rozgrywka zakonczona remisem.";
	}
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

string HandlerGry::KonwertujIndeks(Wektor _we) {
	char c[3] = { _we.y + 65, _we.x + 49, '\0' };

	string s = c;
	return s;
}

Wektor HandlerGry::KonwertujIndeks(string _s) {
	ToLower(_s);
	Wektor we = { _s[0] - 97, _s[1] - 49 };

	return we;
}