#ifndef Measurements_H
#define Measurements_H
#include "ResultOfScan.h"
#include "stdafx.h"

using namespace arma;
static mat &get_Rconst();
static mat &rewriteR(double **cov);
class CMeasurements :  public CResultOfScan{
private:
	int Nmiss;
	mat R=zeros<mat>(M,M); //double
	bool reservedForUpdate; //флаг помечающий на удаление - т.к. удалять сразу нельзя, это сдвинет вектор решений из венгерского алгоритма
	dcolvec z = zeros(M);
public:
	CMeasurements(CVector coordinates, double vr, double time, double **cov);
	CMeasurements::CMeasurements(CResultOfScan &newres);
	~CMeasurements();
	void IncNmiss(); 
	const int GetNmiss();
	double FromDekartToAzimut(); 
	const mat &GetR();
	mat &SetR();
	void SetReservedForUpdate();
	const bool GetReservedForUpdate();
	const dcolvec &Getz();
	dcolvec &Setz();
};
#endif Measurements_H