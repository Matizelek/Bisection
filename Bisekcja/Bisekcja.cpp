#include "Bisekcja.h"
#include <conio.h>	
#include <stdlib.h>  
#include <string>


Bisekcja::Bisekcja()				//konstruktor, gdzie wszystkie zmienne maja wareoœc pocz¹tkow¹
{
	k = 0;	l = 0; 	eps = 0;		//"k" i "l" s¹ granice przedzia³u, "eps" dok³adnoœæ obliczanej wartoœci pierwiastka
	y = 0; y1 = 0;					//"y" i "y1" zmienne potrzebne do przesuwania "x1" i "x2" podczas iteracji
	x = 0;	x1 = 0;	x2 = 0;			//"x1" i "x2" argumenty funkcji, które s¹ granicami, wykorzystywane do obliczenia "x", który póŸniej jest wykorzystywany jako argument funkcji
	degree = 0; iteration = 0; max = 0;		//"degree" przechowuje dane odnoœnie stopnia wspó³czynników, "iteration" mówi ile ju¿ zosta³o zrobionych iteracji,
											//	"max" o liczbie maksymalnej iteracji
	constantA.clear();					//vector "constantA"przechowuj¹cy wspó³czynniki wielomianu
}


Bisekcja::~Bisekcja()
{
}

void Bisekcja::MenuBox(){						//S³u¿y do wyœwietlenia menu 
	cout << "\n\nWitam w Menu programu do obliczania pierwiastków funkcji metod¹ bisekcji\n";
	cout << "Proszê wybraæ jedn¹ z opcji wprowadzenia wspó³czynników wielomianu: \n\n";
	cout << "1. Wprowadzenie za pomoca klawiatury \n\n";
	cout << "2. Za pomoca piku txt \n\n";



	cout << "\n\nESC. Wyjœcie z Programu \n";
}

double Bisekcja::function(double x, int stopien, vector<double> wiel)	//funkcja do obliczania f(x), która zwraca wynik, "solution"
{
	double solution = 0;						
	for (auto i : wiel) {			//przeprowadzanie iteracji po vectorze
		solution += i * pow(x, stopien);		//oblicznie wspó³czynników z x do potêgi
		stopien--;
	}
	return solution;
}


void Bisekcja::calculation()		//Dochodzi tu do g³ównych obliczeñ bisekcji
{
	iteration++;				//iteracja zwiêksza siê z ka¿dym uruchomieniem funkcji
	x = (x1 + x2) / 2;		
	y = function(x, degree, constantA);		//obliczanie f(x)
	if (abs(y) >= eps && max > iteration) {		//porównywanie y w wartoœci bezwzglêdnej z epsilonem i sprawdanie czy nie przekroczono limitu maksymalnej ilosci iteracji
		y1 = function(x1, degree, constantA);	
		if ((y * y1) < 0) {			//porównywanie, w któr¹ stronê przesun¹æ granicê
			x2 = x;
			calculation();		//po przesuniêciu granicy rekurencyjnie dochodzi do dalszych obliczeñ
		}
		else {
			x1 = x;
			calculation();
		}
	}
	else {					
		system("cls");
		cout << "Pierwiastek wynosi x = " << x << " \ny(x) = "<<y<<" \nIloœæ iteracji : "<< iteration << "\n";
		cin.ignore();
		cin.ignore();
	}
}

void Bisekcja::inputData(){			//opcja wczytywania danych z konsoli

	/////////////////////////////////////////////////      STOPIEN I WSPÓ£CZYNNIKI

	system("cls");
	double input;							//"input" sczytuje dane wpisywane na konsoli
	int amount;								//"amount" symbolizuje iloœæ wspó³czynników 
	cout << "Podaj stopieñ wspó³czynnika: \n";
	cin >> degree;							
	do {
		system("cls");
		amount = 0;
		cout << " Proszê wprowadziæ kolejne wspó³czynniki wielomianu: \n";
		for (auto i : constantA) {								//wyœwietlenie aktualnego vectora za pomoca iteracji
			cout << "a" << amount << " = " << i << "\n";
			amount++;
		}
		cin >> input;										
		constantA.push_back(input);						//dodawanie wspó³czynnika na koniec vektora
		
	} while (amount != degree);				//powtarzanie czynnoœci, do momentu, a¿ iloœæ wspó³czynników nie bêdzie równa ich stopniu
	

	///////////////////////////////////////////////////////////	GRANICE PRZEDZIA£U
	do {
		system("cls");
		cout << "Proszê podaæ granice przedzia³u \n" <<
			"Granica pocz¹tkowa: ";
		cin >> k;							
		cout << "\nGranica koñcowa: ";
		cin >> l;							
		if (k >= l) {						//w przypadku, gdy granica koñcowa jest mniejsza lub równa granicy pocz¹tkowej nastêpuje powrót do wspisywanie granic
			cout << "\nŸle podane granice, jeszcze raz.\n";
			cin.get();
		}
	} while (k >= l);			
	cin.get();

	////////////////////////////////////////////////////////////////EPSILON I MAKSIMUM ITERACJI
	system("cls");
	cout << "Proszê podaæ epsilon - dok³adnoœæ do której ma byæ obliczony pierwiastek funkcji:\n";
	cin >> eps;						

	system("cls");
	cout << "Maksimum dopuszczalnych iteracji:\n";
	cin >> max;						
}

vector <double> Bisekcja::assignData(vector <double> wielomian)		//funkcja przypisuje dane do zmiennych po odczytaniu ich z pliku .txt
{
	max = static_cast<int>(wielomian.back());		//przypisywanie ostatniej wartosci vectora zmiennej "max" i zrzutoeanie z double na int

	wielomian.pop_back();
	eps = wielomian.back();		

	wielomian.pop_back();
	l = wielomian.back();		

	wielomian.pop_back();
	k = wielomian.back();		

	wielomian.pop_back();

	degree = wielomian.size() - 1;		

	return wielomian;

}

void Bisekcja::bisekcja()		//metoda która ustawia granice do zmiennych "x1" i "x2", oraz inicjuje obliczenia
{
	x1 = k; x2 = l;
	calculation();
	constantA.clear();					//czyszczenie vectora ze zmiennych
	iteration = 0;
}

void Bisekcja::init()		//metoda rozpoczyna  i kontroluje dzia³anie funkcji i wybory u¿ytkownika 
{
	char sign = NULL;
	do {
		system("cls");
		MenuBox();					
		sign = _getch();			//taking first key without press enter;


		switch (sign)				
		{
		case '1':				//wybór wpisania danych z klawiatury
		{
			inputData();			
			bisekcja();				
			break;
		}
		case '2':					//wybór wczytania danych z pliku
		{
			constantA = (loadDataVector(constantA));	//skorzystanie z dziedziczonej metody, by wpisaæ do vectora otrzymane dane z pliku .txt
			
			if (!constantA.empty()) {			//sprawdzanie czy vector nie jest pusty, gdzie by³oby tak w przypadku, gdyby nie uda³o siê odczytaæ pliku
				constantA = (assignData(constantA));
				bisekcja();				
			}
			else {
				constantA.clear();					//czyszczenie vectora ze zmiennych
				iteration = 0;
			}
			break;
		}
		default:
			break;
		}
	} while (sign != 27);		//czekanie na wciœniêcie przycisku "ESC"
}