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
	bool reservedForUpdate; //���� ���������� �� �������� - �.�. ������� ����� ������, ��� ������� ������ ������� �� ����������� ���������
	dcolvec z = zeros(M);
	int CurrentSector;
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
	void SetCurrentSector(int Sector);
	const int GetCurrentSector();
};
#endif Measurements_H