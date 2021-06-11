#ifndef PSO_H
#define PSO_H

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <vector>

using namespace std;

class PSO{
public:

	int D, N, MAX;
	int TheBest = 0;

	double EvalGbest;
	vector<double> Pmin, Pmax;
	vector<double> Eval, EvalPbest, Gbest;
	vector<vector<double>> P, Pbest, V;

	PSO(
		int D,
		int N,
		int MAX,
		vector<double> Pmin,
		vector<double> Pmax,
		double (*func)(vector<double> X)
	);
	
	double (*cost_func)(vector<double> X);
	void fit();
};

#endif // PSO_H