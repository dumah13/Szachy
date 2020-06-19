#include "AI.h"
#include "HandlerGry.h"
#include "DodatkoweFunkcje.h"

AI::AI(Plansza* _paPlansza, HandlerGry* _handlerGry, int _iKolor, int _iWartoscPlanszy, int _glebokoscPrzeszukiwania) : Bot(_paPlansza, _handlerGry, _iKolor, _iWartoscPlanszy, _glebokoscPrzeszukiwania) {
	const size_t inputs_number = 13;
	const size_t hidden_neurons_number = 64;
	const size_t outputs_number = 1;

	const vector<size_t> architecture = { inputs_number,hidden_neurons_number,outputs_number };

	vector<string> naglowek = { "atakowane","krolowe_dif", "wieze_dif", "gonce_dif", "konie_dif", "piony_dif" ,"przemieszczenie_x", "przemieszczenie_y", "zbicie", "typ_figury", "typ_zbitej", "specjalne" ,"wartosc_delta", "wynik" };
	string output_name = naglowek.back();
	naglowek.pop_back();
	siecNeuronowa.set_inputs_names(naglowek);
	siecNeuronowa.set_outputs_names({ output_name });
	siecNeuronowa.set(NeuralNetwork::ProjectType::Approximation, architecture);
}

AI::~AI() {
}

Ruch* AI::WybierzRuch() {
	
	size_t liczbaKolumn = 13;
	Matrix<double> macierzDanych(mozliweRuchy.size(), liczbaKolumn + 1);
	vector<string> naglowek = { "atakowane", "krolowe_dif", "wieze_dif", "gonce_dif", "konie_dif", "piony_dif","przemieszczenie_x", "przemieszczenie_y",  "zbicie", "typ_figury", "typ_zbitej", "specjalne" , "wartosc_delta", "wynik" };
	int kolor = GetKolor() == 1 ? -1 : 1;
	macierzDanych.set_header(naglowek);
	//macierzDanych.set(0,liczbaKolumn);
	for (int i = 0; i < mozliweRuchy.size(); i++) {
		vector<double> wiersz;
		int atakowane = 0;
		int H = 0;
		int G = 0;
		int S = 0;
		int W = 0;
		int P = 0;

		Plansza* plansza = GetPlansza();
		Ruch ruch = *mozliweRuchy[i];

		double wartoscPrzed = EwaluujPlansze() * (GetKolor() == 1 ? -1 : 1);

		GetHandlerGry()->SymulujRuch(mozliweRuchy[i]);

		double wartoscPo = EwaluujPlansze() * (GetKolor() == 1 ? -1 : 1);

		for (int k = 0; k < plansza->iWymiaryPlanszy; k++) {
			for (int j = 0; j < plansza->iWymiaryPlanszy; j++) {
				if (!(*plansza)[k][j].Puste())
				{
					switch ((*plansza)[k][j].GetFigura()->GetTyp()) {
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
					if (!atakowane && sgn((int)(*plansza)[k][j].GetFigura()->GetTyp()) == kolor*-1)
					{
						for (int l = 0; l < (*plansza)[k][j].GetFigura()->GetRuchy().size(); l++) {
							atakowane = (*plansza)[k][j].GetFigura()->GetRuchy()[l] == ruch.GetDo() ? 1 : 0;
							if (atakowane)
							{
								break;
							}
						}
					}
				}
			}
		}
		GetHandlerGry()->CofnijRuch();

		wiersz.push_back(atakowane);
		wiersz.push_back(H * (GetKolor() ? -1 : 1));
		wiersz.push_back(W * (GetKolor() ? -1 : 1));
		wiersz.push_back(G * (GetKolor() ? -1 : 1));
		wiersz.push_back(S * (GetKolor() ? -1 : 1));
		wiersz.push_back(P * (GetKolor() ? -1 : 1));

		
		wiersz.push_back((ruch.GetDo().x - ruch.GetZ().x)* (GetKolor() == 1 ? -1 : 1));
		wiersz.push_back((ruch.GetDo().y-ruch.GetZ().y)* (GetKolor() == 1 ? -1 : 1));

		wiersz.push_back(ruch.GetZbicie());

		wiersz.push_back(abs((double)ruch.GetTypFigury()));
		wiersz.push_back(abs((double)ruch.GetZbita()));

		wiersz.push_back(ruch.GetSpecjalne());

		wiersz.push_back(wartoscPo - wartoscPrzed);

		Tensor<double> inputs(vector<size_t>{1,liczbaKolumn}, 0.0);
		for (int j = 0; j < liczbaKolumn; j++) {
			inputs[j] = wiersz[j];
		}

		Tensor<double> outputs(Vector<size_t>{1}, 0.0);
		outputs = siecNeuronowa.calculate_outputs(inputs);
		wiersz.push_back(outputs[0]);

		macierzDanych.set_row(i,wiersz);

	}
	
	double maksimum = INT16_MIN;
	int ruch = 0;
	for (int j = 0; j < mozliweRuchy.size(); j++) {
		if (macierzDanych.get_column("wynik")[j] > maksimum) {
			ruch = j;
			maksimum = macierzDanych.get_column("wynik")[j];
		}
	}



	return mozliweRuchy[ruch];
}


void AI::SzkolSiec(int _wybranyRuch) {
	size_t liczbaKolumn = 13;
	Matrix<double> macierzDanych(mozliweRuchy.size(), liczbaKolumn + 1);
	vector<string> naglowek = { "atakowane", "krolowe_dif", "wieze_dif", "gonce_dif", "konie_dif", "piony_dif","przemieszczenie_x", "przemieszczenie_y",  "zbicie", "typ_figury", "typ_zbitej", "specjalne" , "wartosc_delta", "wynik" };
	int kolor = GetKolor() == 1 ? -1 : 1;

	macierzDanych.set_header(naglowek);
	//macierzDanych.set(0,liczbaKolumn);
	for (int i = 0; i < mozliweRuchy.size(); i++) {
		vector<double> wiersz;
		int atakowane = 0;
		Ruch ruch = *mozliweRuchy[i];
		int H = 0;
		int G = 0;
		int S = 0;
		int W = 0;
		int P = 0;

		Plansza* plansza = GetPlansza();
		double wartoscPrzed = EwaluujPlansze() * (GetKolor() == 1 ? -1 : 1);

		GetHandlerGry()->SymulujRuch(mozliweRuchy[i]);

		double wartoscPo = EwaluujPlansze() * (GetKolor() == 1 ? -1 : 1);

		for (int k = 0; k < plansza->iWymiaryPlanszy; k++) {
			for (int j = 0; j < plansza->iWymiaryPlanszy; j++) {
				if (!(*plansza)[k][j].Puste())
				{
					switch ((*plansza)[k][j].GetFigura()->GetTyp()) {
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
					
					if (!atakowane && sgn((int)(*plansza)[k][j].GetFigura()->GetTyp()) == kolor*-1)
					{
						for (int l = 0; l < (*plansza)[k][j].GetFigura()->GetRuchy().size(); l++) {
							atakowane = (*plansza)[k][j].GetFigura()->GetRuchy()[l] == ruch.GetDo() ? 1 : 0;
							if (atakowane)
							{
								break;
							}
						}
					}
				}
			}
		}

		GetHandlerGry()->CofnijRuch();
		mozliweRuchy.clear();

		for (int j = 0; j < GetHandlerGry()->GetGracz(GetHandlerGry()->GetTuraGracza())->GetRuchy().size(); j++) {
			mozliweRuchy.push_back(GetHandlerGry()->GetGracz(GetHandlerGry()->GetTuraGracza())->GetRuchy()[j]);
		}

		wiersz.push_back(atakowane);

		wiersz.push_back(H * (GetKolor() ? -1 : 1));
		wiersz.push_back(W * (GetKolor() ? -1 : 1));
		wiersz.push_back(G * (GetKolor() ? -1 : 1));
		wiersz.push_back(S * (GetKolor() ? -1 : 1));
		wiersz.push_back(P * (GetKolor() ? -1 : 1));

		wiersz.push_back((ruch.GetDo().x - ruch.GetZ().x) * (GetKolor() == 1 ? -1 : 1));
		wiersz.push_back((ruch.GetDo().y - ruch.GetZ().y) * (GetKolor() == 1 ? -1 : 1));

		wiersz.push_back(ruch.GetZbicie());

		wiersz.push_back(abs((double)ruch.GetTypFigury()));
		wiersz.push_back(abs((double)ruch.GetZbita()));

		wiersz.push_back(ruch.GetSpecjalne());

		wiersz.push_back(wartoscPo - wartoscPrzed);

		double wynik = _wybranyRuch == i ? 1 : 0;

		wiersz.push_back(wynik);

		macierzDanych.set_row(i, wiersz);
		
	}
	macierzDanych.save_csv("dane.csv", ',');

	DataSet dataSet("dane.csv", ',', true);
	dataSet.set_columns_names(naglowek);
	dataSet.set_training();

	TrainingStrategy training_strategy(&siecNeuronowa, &dataSet);
	training_strategy.set_loss_method(TrainingStrategy::MEAN_SQUARED_ERROR);
	training_strategy.set_optimization_method(TrainingStrategy::OptimizationMethod::ADAPTIVE_MOMENT_ESTIMATION);
	training_strategy.get_adaptive_moment_estimation_pointer()->set_maximum_epochs_number(2);

	training_strategy.set_display(false);

	OptimizationAlgorithm::Results results = training_strategy.perform_training();
}

void AI::ZapiszWagiDoPliku(string _nazwa) {
	siecNeuronowa.save(_nazwa);
	return;
}

void AI::WczytajWagiZPliku(string _nazwa) {
	try { siecNeuronowa.load(_nazwa); 
	}
	catch(std::exception& e) {
		cout << "Brak pliku z wagami o podanej nazwie.\n";
		Sleep(1000);
	}
	return;
}