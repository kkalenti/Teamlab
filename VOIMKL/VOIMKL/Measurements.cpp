
#include "stdafx.h"

using namespace std;

mat &get_Rconst() {
	static bool initialized = false;
	static colvec INIT_DIAG;
	static mat RCONST = zeros<mat>(M, M);
	if (!initialized) {
		INIT_DIAG << 1 << 2 << 3;
		RCONST.diag() = INIT_DIAG;
		initialized = true;
	}
	return RCONST;
}

mat &rewriteR(double **cov){
	static mat RCONST = zeros<mat>(M, M);
	for (int i = 0; i < M ; i++)
	{
		for (int j = 0; j < M + 1; j++)
		{
			if (j < M)
			{
				RCONST(i,j) = cov[i][j];
			}
		}
	}
	return RCONST;
}

CMeasurements::CMeasurements(CVector coordinates, double vr, double time, double **cov) :CResultOfScan(coordinates, vr, time, cov)
{
	this->z[0] = coordinates.x;
	this->z[1] = coordinates.y;
	this->z[2] = coordinates.z;
	this->Nmiss = 0;
	this->R = rewriteR(cov);
	this->reservedForUpdate = false;
	this->CurrentSector = 0;
}

CMeasurements::CMeasurements(CResultOfScan &newres) :CResultOfScan(newres.Coordinates, newres.Vr, newres.DetectionTime, newres.CovMat)
{
	this->z[0] = newres.Coordinates.x;
	this->z[1] = newres.Coordinates.y;
	this->z[2] = newres.Coordinates.z;
	this->Nmiss = 0;
	this->R = rewriteR(newres.CovMat);
	this->reservedForUpdate = false;
	this->CurrentSector = 0;
}

CMeasurements::~CMeasurements()
{

}

void CMeasurements::IncNmiss()
{
	this->Nmiss++;
}

const int CMeasurements::GetNmiss()
{
	return this->Nmiss;
}

double CMeasurements::FromDekartToAzimut()
{
	return (atan(this->z[2]/this->z[0]));
}

const mat &CMeasurements::GetR()
{
	return this->R;
}

mat &CMeasurements::SetR()
{
	return this->R;
}

void CMeasurements::SetReservedForUpdate()
{
	this->reservedForUpdate = true;
}

const bool CMeasurements::GetReservedForUpdate()
{
	return this->reservedForUpdate;
}

const dcolvec &CMeasurements::Getz()
{
	return this->z;
}

dcolvec &CMeasurements::Setz()
{
	return this->z;
}

void CMeasurements::SetCurrentSector(int Sector)
{
	this->CurrentSector = Sector;
}

const int CMeasurements::GetCurrentSector()
{
	return this->CurrentSector;
}