#include "stdafx.h"

CResultOfScan::CResultOfScan(CVector coordinates, double vr, double time)
{
	this->Coordinates.x = coordinates.x;
	this->Coordinates.y = coordinates.y;
	this->Coordinates.z = coordinates.z;
	this->Vr = vr;
	DetectionTime = time;
	CovMat = new double*[4];
	for( int i = 0; i < 4; i++ ) {
		CovMat[i] = new double[4];
		for ( int j = 0; j < 4; j++ ) {
			CovMat[i][j] = 0;
		}
	}
	CovMat[0][0] = CAirObject::distanceSko;
	CovMat[1][1] = CAirObject::accelerationSko;
	CovMat[2][2] = CAirObject::epsilonSko;
	CovMat[3][3] = CAirObject::radialSko;
}

CResultOfScan::~CResultOfScan()
{

}