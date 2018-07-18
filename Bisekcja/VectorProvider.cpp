#include "VectorProvider.h"



VectorProvider::VectorProvider(){
	name = "";
}


VectorProvider::~VectorProvider(){
}

vector<double> VectorProvider::loadDataVector(vector<double> Data)
{
	system("cls");
	cout << "Wzór wczytywania kolejnych danych z pliku wyglada nastêpuj¹co:\n" <<		//Instrukcje odnoœnie jak umieszczaæ dane w pliku
		"a0,a1,a2,a3,k,l,eps,max\n\n" <<
		"W przyk³adzie wygl¹da to tak:\n"
		"1,-3,-2,5,1,2,0.1,20\n\n" <<
		"Liczby w kolejnoœci: 1,-3,-2,5 - s¹ to wspó³czynniki\n\n" <<
		"Liczby kolejne 1,2 - s¹ to kolejno granice przedzia³u\n\n" <<
		"Dalej jest 0.1 - to epsilon\n\n" <<
		"Ostatnia liczba max - jest to maksumalna iloœæ literacji\n";
	cin.get();																	//funkcja czeka na enter, by przejœæ dalej

	system("cls");
	cout << "Plik txt musi znajdowaæ siê w folderze programu.\n" <<
		"Dane musz¹ znajdowaæ siê w jednej linijce.\n"<<
		"Spacje miêdzy przecinkami nie maj¹ znaczenia, ale nie miêdzy znakiem i liczb¹.\n"
		"Wprowadz nazwe pliku txt: \n";
	cin >> name;									//wprowadzenie nazwy pliku

	system("cls");

	name += ".txt";							//dodanie do nazwy koñcówki .txt

	ifstream inPlik;				//Tworzenie klasy ifstream, by móc operowaæ na pliku

	inPlik.open(name);				//otwarcie pliku

	if (inPlik.is_open()) {			//sprawdzenie, czy uda³o sie otworzyæplik

		string line;
		double num;

		while (inPlik)				//dopóki plik siê nie skoñczy³, powtarzaj instrukcje
		{
			inPlik >> num;					//zczytywanie liczby double
			getline(inPlik, line, ',');		//przenoszenie kursora za przecinek

			if (!inPlik) {			//sprawdzanie czy plik siê, czasem nie skoñczy³ i nie przechwytujemyjemy ponownie tej samej liczby
				break;
			}

			Data.push_back(num);			//wrzucanie liczby double na koniec vectora
		}
		inPlik.close();				//po skoñczeniu operacji zamkniêcie pliku
	}

	else {
		cout << "Nie mo¿na otworzyæ pliku: " << name << "\n";		//komunikat w przypadku nie powodzenia otwarcia pliku
		cin.get();
	}
	return Data;
}