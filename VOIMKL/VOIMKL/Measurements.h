#ifndef Measurements_H
#define Measurements_H
#include"ResultOfScan.h"
#include "stadfx.h"
using namespace arma;
static mat &get_Rconst();
class CMeasurements: public CResultOfScan{ 
private:
	int Nmiss;
	mat R=zeros<mat>(M,M); //double
	bool reservedForUpdate;
public:
	CMeasurements(CVector coordinates, double vr, double time);
	CMeasurements::CMeasurements(CResultOfScan &newres);
	~CMeasurements();
	void IncNmiss();
	const int GetNmiss();
	double FromDekartToAzimut();
	const mat &GetR();
	void SetReservedForUpdate();
	const bool GetReservedForUpdate();
};
#endif Measurements_H