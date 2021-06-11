#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include "pso.h"

using namespace std;

double cost (vector<double> X);

int main(int argc, char const *argv[])
{
	int D = 20, N = 100, MAX = 100000;
	vector<double> P1 (D,-20), P2 (D, 20);

	PSO pso = PSO(
		D,
		N,
		MAX,
		P1,
		P2,
		&cost
	);
	
	pso.fit();

	cout<<"EvalGbest = "<<pso.EvalGbest<<endl;
	return 0;
}

double cost (vector<double> X){
	double val = 0;
	for (int i = 0; i < (int)X.size(); ++i) val += X[i] * X[i];
	return val;
}

// The commands line to compile this program in Linux
// g++ -c main.cpp pso.cpp
// g++ main.o pso.o -o out
// ./out