#include "Bisekcja.h"
#include <conio.h>	
#include <stdlib.h>  
#include <string>


Bisekcja::Bisekcja()				//konstruktor, gdzie wszystkie zmienne maja wareo�c pocz�tkow�
{
	k = 0;	l = 0; 	eps = 0;		//"k" i "l" s� granice przedzia�u, "eps" dok�adno�� obliczanej warto�ci pierwiastka
	y = 0; y1 = 0;					//"y" i "y1" zmienne potrzebne do przesuwania "x1" i "x2" podczas iteracji
	x = 0;	x1 = 0;	x2 = 0;			//"x1" i "x2" argumenty funkcji, kt�re s� granicami, wykorzystywane do obliczenia "x", kt�ry p�niej jest wykorzystywany jako argument funkcji
	degree = 0; iteration = 0; max = 0;		//"degree" przechowuje dane odno�nie stopnia wsp�czynnik�w, "iteration" m�wi ile ju� zosta�o zrobionych iteracji,
											//	"max" o liczbie maksymalnej iteracji
	constantA.clear();					//vector "constantA"przechowuj�cy wsp�czynniki wielomianu
}


Bisekcja::~Bisekcja()
{
}

void Bisekcja::MenuBox(){						//S�u�y do wy�wietlenia menu 
	cout << "\n\nWitam w Menu programu do obliczania pierwiastk�w funkcji metod� bisekcji\n";
	cout << "Prosz� wybra� jedn� z opcji wprowadzenia wsp�czynnik�w wielomianu: \n\n";
	cout << "1. Wprowadzenie za pomoca klawiatury \n\n";
	cout << "2. Za pomoca piku txt \n\n";



	cout << "\n\nESC. Wyj�cie z Programu \n";
}

double Bisekcja::function(double x, int stopien, vector<double> wiel)	//funkcja do obliczania f(x), kt�ra zwraca wynik, "solution"
{
	double solution = 0;						
	for (auto i : wiel) {			//przeprowadzanie iteracji po vectorze
		solution += i * pow(x, stopien);		//oblicznie wsp�czynnik�w z x do pot�gi
		stopien--;
	}
	return solution;
}


void Bisekcja::calculation()		//Dochodzi tu do g��wnych oblicze� bisekcji
{
	iteration++;				//iteracja zwi�ksza si� z ka�dym uruchomieniem funkcji
	x = (x1 + x2) / 2;		
	y = function(x, degree, constantA);		//obliczanie f(x)
	if (abs(y) >= eps && max > iteration) {		//por�wnywanie y w warto�ci bezwzgl�dnej z epsilonem i sprawdanie czy nie przekroczono limitu maksymalnej ilosci iteracji
		y1 = function(x1, degree, constantA);	
		if ((y * y1) < 0) {			//por�wnywanie, w kt�r� stron� przesun�� granic�
			x2 = x;
			calculation();		//po przesuni�ciu granicy rekurencyjnie dochodzi do dalszych oblicze�
		}
		else {
			x1 = x;
			calculation();
		}
	}
	else {					
		system("cls");
		cout << "Pierwiastek wynosi x = " << x << " \ny(x) = "<<y<<" \nIlo�� iteracji : "<< iteration << "\n";
		cin.ignore();
		cin.ignore();
	}
}

void Bisekcja::inputData(){			//opcja wczytywania danych z konsoli

	/////////////////////////////////////////////////      STOPIEN I WSPӣCZYNNIKI

	system("cls");
	double input;							//"input" sczytuje dane wpisywane na konsoli
	int amount;								//"amount" symbolizuje ilo�� wsp�czynnik�w 
	cout << "Podaj stopie� wsp�czynnika: \n";
	cin >> degree;							
	do {
		system("cls");
		amount = 0;
		cout << " Prosz� wprowadzi� kolejne wsp�czynniki wielomianu: \n";
		for (auto i : constantA) {								//wy�wietlenie aktualnego vectora za pomoca iteracji
			cout << "a" << amount << " = " << i << "\n";
			amount++;
		}
		cin >> input;										
		constantA.push_back(input);						//dodawanie wsp�czynnika na koniec vektora
		
	} while (amount != degree);				//powtarzanie czynno�ci, do momentu, a� ilo�� wsp�czynnik�w nie b�dzie r�wna ich stopniu
	

	///////////////////////////////////////////////////////////	GRANICE PRZEDZIA�U
	do {
		system("cls");
		cout << "Prosz� poda� granice przedzia�u \n" <<
			"Granica pocz�tkowa: ";
		cin >> k;							
		cout << "\nGranica ko�cowa: ";
		cin >> l;							
		if (k >= l) {						//w przypadku, gdy granica ko�cowa jest mniejsza lub r�wna granicy pocz�tkowej nast�puje powr�t do wspisywanie granic
			cout << "\n�le podane granice, jeszcze raz.\n";
			cin.get();
		}
	} while (k >= l);			
	cin.get();

	////////////////////////////////////////////////////////////////EPSILON I MAKSIMUM ITERACJI
	system("cls");
	cout << "Prosz� poda� epsilon - dok�adno�� do kt�rej ma by� obliczony pierwiastek funkcji:\n";
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

void Bisekcja::bisekcja()		//metoda kt�ra ustawia granice do zmiennych "x1" i "x2", oraz inicjuje obliczenia
{
	x1 = k; x2 = l;
	calculation();
	constantA.clear();					//czyszczenie vectora ze zmiennych
	iteration = 0;
}

void Bisekcja::init()		//metoda rozpoczyna  i kontroluje dzia�anie funkcji i wybory u�ytkownika 
{
	char sign = NULL;
	do {
		system("cls");
		MenuBox();					
		sign = _getch();			//taking first key without press enter;


		switch (sign)				
		{
		case '1':				//wyb�r wpisania danych z klawiatury
		{
			inputData();			
			bisekcja();				
			break;
		}
		case '2':					//wyb�r wczytania danych z pliku
		{
			constantA = (loadDataVector(constantA));	//skorzystanie z dziedziczonej metody, by wpisa� do vectora otrzymane dane z pliku .txt
			
			if (!constantA.empty()) {			//sprawdzanie czy vector nie jest pusty, gdzie by�oby tak w przypadku, gdyby nie uda�o si� odczyta� pliku
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
	} while (sign != 27);		//czekanie na wci�ni�cie przycisku "ESC"
}