#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


class VectorProvider
{
	string name;
public:
	VectorProvider();
	~VectorProvider();
	virtual vector<double> loadDataVector(vector <double> Data);		
};

