#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include "VectorProvider.h"

using namespace std;

class Bisekcja : public VectorProvider			//dziedziczenie po klasie Plik, by korzystaæ z jej metody "wczytajPlik()"
{
	int iteration;				
	double	y, y1,
		x ,x1,x2;
	int degree, max;			
	double k, l, eps;
	vector <double> constantA;  
public:
	Bisekcja();
	~Bisekcja();
	void MenuBox();
	double function(double x, int stopien, vector <double> wiel);   
	void bisekcja();
	void calculation();			
	void init();		
	void inputData();		
	vector <double> assignData(vector <double> wielomian);		
};

