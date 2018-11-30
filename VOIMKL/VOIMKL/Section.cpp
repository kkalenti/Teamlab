#include "Section.h"

CSection:: CSection()
{
	this->AzimutMin = 0;
	this->AzimutMax = 0;
	this->Lasttime = 0;
}

CSection::~CSection()
{

}

const double CSection::GetLasttime()
{
	return this->Lasttime;
}

void CSection::SetLasttime(double lasttime)
{
	this->Lasttime = lasttime;
}

const double CSection::GetAzimutMin()
{
	return this->AzimutMin;
}

const double CSection::GetAzimutMax()
{
	return this->AzimutMax;
}

void  CSection::SetAzimutMin(double angle)
{
	this->AzimutMin = angle;
}

void  CSection::SetAzimutMax(double angle)
{
	this->AzimutMax = angle;
}