#include "VectorProvider.h"



VectorProvider::VectorProvider(){
	name = "";
}


VectorProvider::~VectorProvider(){
}

vector<double> VectorProvider::loadDataVector(vector<double> Data)
{
	system("cls");
	cout << "Wz�r wczytywania kolejnych danych z pliku wyglada nast�puj�co:\n" <<		//Instrukcje odno�nie jak umieszcza� dane w pliku
		"a0,a1,a2,a3,k,l,eps,max\n\n" <<
		"W przyk�adzie wygl�da to tak:\n"
		"1,-3,-2,5,1,2,0.1,20\n\n" <<
		"Liczby w kolejno�ci: 1,-3,-2,5 - s� to wsp�czynniki\n\n" <<
		"Liczby kolejne 1,2 - s� to kolejno granice przedzia�u\n\n" <<
		"Dalej jest 0.1 - to epsilon\n\n" <<
		"Ostatnia liczba max - jest to maksumalna ilo�� literacji\n";
	cin.get();																	//funkcja czeka na enter, by przej�� dalej

	system("cls");
	cout << "Plik txt musi znajdowa� si� w folderze programu.\n" <<
		"Dane musz� znajdowa� si� w jednej linijce.\n"<<
		"Spacje mi�dzy przecinkami nie maj� znaczenia, ale nie mi�dzy znakiem i liczb�.\n"
		"Wprowadz nazwe pliku txt: \n";
	cin >> name;									//wprowadzenie nazwy pliku

	system("cls");

	name += ".txt";							//dodanie do nazwy ko�c�wki .txt

	ifstream inPlik;				//Tworzenie klasy ifstream, by m�c operowa� na pliku

	inPlik.open(name);				//otwarcie pliku

	if (inPlik.is_open()) {			//sprawdzenie, czy uda�o sie otworzy�plik

		string line;
		double num;

		while (inPlik)				//dop�ki plik si� nie sko�czy�, powtarzaj instrukcje
		{
			inPlik >> num;					//zczytywanie liczby double
			getline(inPlik, line, ',');		//przenoszenie kursora za przecinek

			if (!inPlik) {			//sprawdzanie czy plik si�, czasem nie sko�czy� i nie przechwytujemyjemy ponownie tej samej liczby
				break;
			}

			Data.push_back(num);			//wrzucanie liczby double na koniec vectora
		}
		inPlik.close();				//po sko�czeniu operacji zamkni�cie pliku
	}

	else {
		cout << "Nie mo�na otworzy� pliku: " << name << "\n";		//komunikat w przypadku nie powodzenia otwarcia pliku
		cin.get();
	}
	return Data;
}