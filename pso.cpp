#include "pso.h"
#include <iostream>
#include <ctime>
#include <math.h>
#include <vector>

using namespace std;

double r(){
	return (double)(rand()%1000)/1000;
}

PSO::PSO(
	int D,
	int N,
	int MAX,
	vector<double> Pmin,
	vector<double> Pmax,
	double (*func)(vector<double> X)
){
	this->D   = D;
	this->N   = N;
	this->MAX = MAX;
	cost_func = func;

	this->Pmin = Pmin;
	this->Pmax = Pmax;

	P        .resize(this->N, vector<double>(this->D, 0));
	V        .resize(this->N, vector<double>(this->D, 0));
	Pbest    .resize(this->N, vector<double>(this->D, 0));
	Eval     .resize(this->N, 0);
	EvalPbest.resize(this->N, 0);
	Gbest    .resize(this->D, 0);
}

void PSO::fit(){

	for (int i = 0; i < this->N; ++i)
	{
		for (int j = 0; j < this->D; ++j)
		{
			P[i][j] = (Pmax[j] - Pmin[j]) * r() + Pmin[j];
			Pbest[i][j] = P[i][j];
			V[i][j] = 0;
		}
		Eval[i] = cost_func(P[i]);
		EvalPbest[i] = Eval[i];
		if(Eval[i] < Eval[TheBest])
			TheBest = i;
	}

	for (int j = 0; j < D; ++j)
		Gbest[j] = P[TheBest][j];

	EvalGbest = Eval[TheBest];

	int Iter = 0;
	while(Iter<MAX){
		Iter++;
		TheBest = 0;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < D; ++j)
			{
				V[i][j] = V[i][j] + 2*r() * (Pbest[i][j] - P[i][j]) + 2 * r() * (Gbest[j] - P[i][j]);
				P[i][j] = P[i][j] + V[i][j];
				if(P[i][j]<Pmin[j])
					P[i][j] = Pmin[j];
				if(P[i][j]>Pmax[j])
					P[i][j] = Pmax[j];
			}
			Eval[i] = cost_func(P[i]);
			if (Eval[i]<EvalPbest[i])
				for (int j = 0; j < D; ++j)
					Pbest[i][j] = P[i][j];
			if (Eval[i] < Eval[TheBest])
				TheBest = i;
		}
		if (Eval[TheBest] < EvalGbest)
		{
			for (int j = 0; j < D; ++j)
				Gbest[j] = P[TheBest][j];
			EvalGbest = Eval[TheBest];
			
		}
		if(Iter % 1000 == 0)
			cout<<Iter
				<<" - EvalGbest = "
				<<EvalGbest
				<<endl;
	}
}
