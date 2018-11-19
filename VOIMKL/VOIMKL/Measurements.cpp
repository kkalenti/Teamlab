#include "Measurements.h"
using namespace std;

mat &get_Rconst() {
	static bool initialized = false;
	static colvec INIT_DIAG;
	static mat RCONST = zeros<mat>(M, M);
	if (!initialized) {
		INIT_DIAG << 0 << 0 << 0;
		RCONST.diag() = INIT_DIAG;
		initialized = true;
	}
	return RCONST;
}

CMeasurements::CMeasurements(CVector coordinates, double vr, double time):CResultOfScan(coordinates, vr, time)
{
	this->z[0] = coordinates.x;
	this->z[1] = coordinates.y;
	this->z[2] = coordinates.z;
	this->Nmiss = 0;
	this->R = get_Rconst();
	this->reservedForUpdate = false;
}

CMeasurements::CMeasurements(CResultOfScan &newres) :CResultOfScan(newres.Coordinates, newres.Vr, newres.detectionTime)
{
	this->z[0] = newres.Coordinates.x;
	this->z[1] = newres.Coordinates.y;
	this->z[2] = newres.Coordinates.z;
	this->Nmiss = 0;
	this->R = get_Rconst();
	this->reservedForUpdate = false;
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