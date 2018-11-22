#include "stdafx.h"
#include <math.h>
#include <random>
#include <ctime>

CAirObject::CAirObject() 
{
	this->AccelerationStates = nullptr;
	this->beta = 0;
	this->epsilon = 0;
	this->distance = 0;
	this->aChangesCounter = 0;
	CovMat = new double*[3];
	for (int i = 0; i < 3; i++) {
		CovMat[i] = new double[3];
		for (int j = 0; j < 3; j++) {
			CovMat[i][j] = 0;
		}
	}
	CovMat[0][0] = CAirObject::distanceSko;
	CovMat[1][1] = CAirObject::betaSko;
	CovMat[2][2] = CAirObject::epsilonSko;
}

CAirObject::CAirObject(int fx, int fy, int fz, const CVector& station)
{
	Coordinate.x = fx;
	Coordinate.y = fy;
	Coordinate.z = fz;
	distance = sqrt(pow(Coordinate.x - station.x, 2) + pow(Coordinate.y - station.y, 2) + pow(Coordinate.z - station.z, 2)); // ���������� �� ����
	double katet = sqrt(pow(Coordinate.z - station.z, 2) + pow(Coordinate.x - station.x, 2)); // ������� ���������, ��� Y ��� Z, X ��� Y, � Z ��� X
	double katet2 = sqrt(pow(distance, 2) - pow(katet, 2));
	epsilon = katet2 / distance; // �������� �������
	// �������� ���� �����
	katet = Coordinate.x - station.x;
	katet2 = Coordinate.z - station.z;
	double projection = sqrt(pow(katet, 2) + pow(katet2, 2)); // �������� distance �� ��������� XZ
	beta = katet2 / projection; // �������� ���� �����
	std::random_device device;
	gaussGenerator.seed(device());
	CovMat = new double*[4];
	for (int i = 0; i < 3; i++) {
		CovMat[i] = new double[3];
		for (int j = 0; j < 3; j++) {
			CovMat[i][j] = 0;
		}
	}
	CovMat[0][0] = CAirObject::distanceSko;
	CovMat[1][1] = CAirObject::betaSko;
	CovMat[2][2] = CAirObject::epsilonSko;
}

CAirObject::~CAirObject() 
{
	if (AccelerationStates != nullptr) {
		delete[] AccelerationStates;
	}
}

double CAirObject::epsilonSko; // ��� ����������� �������������������� ���������� ��� �����
double CAirObject::betaSko;
double CAirObject::distanceSko;
double CAirObject::accelerationSko;
double CAirObject::radialSko;
int CAirObject::typeOfEmulation; 

void CAirObject::Update(const double time, const double curTime, const CVector& station) // time - ����� �����
{                
	// �������� ���������
	Coordinate.x += Speed.x * time + 0.5 * Acceleration.x * pow(time, 2);
	Coordinate.z += Speed.z * time + 0.5 * Acceleration.z * pow(time, 2);
	Coordinate.y += Speed.y * time + 0.5 * Acceleration.y * pow(time, 2);
	if (Coordinate.y <= 0) {
		exit(-1);
	}; // ������ ���� ��� �����

	// �������� ���������
	Speed.x += Acceleration.x * time;
	Speed.y += Acceleration.y * time;
	Speed.z += Acceleration.z * time;
	// �������� ���������� ��������
	// ������ ������-�������
	double radiusSize = sqrt(pow((Coordinate.x - station.x), 2) + pow((Coordinate.y - station.y), 2) + pow((Coordinate.z - station.z), 2));
	CVector normir; // ������������� ������ ������
	normir.x = (Coordinate.x - station.x) / radiusSize;
	normir.y = (Coordinate.y - station.y) / radiusSize;
	normir.z = (Coordinate.z - station.z) / radiusSize;
	radialSpeed = Speed.x * normir.x + Speed.y * normir.y + Speed.z * normir.z;
	// �������� ����� �� ��������� ���� ��� ����
	if( accelerationSko != 0 ) {
		Acceleration.x += returnGaussRandom(accelerationSko);
		Acceleration.z += returnGaussRandom(accelerationSko);
		Acceleration.y += returnGaussRandom(accelerationSko);
	}
	// �������� �������
	distance = sqrt(pow(Coordinate.x - station.x, 2) + pow(Coordinate.y - station.y, 2) + pow(Coordinate.z - station.z, 2)); // ���������� �� ����
	double katet = sqrt(pow(Coordinate.z - station.z, 2) + pow(Coordinate.x - station.x, 2)); // ������� ���������, ��� Y ��� Z, X ��� Y, � Z ��� X
	double katet2 = sqrt(pow(distance, 2) - pow(katet, 2));
	epsilon = katet2 / distance; // �������� �������
	// �������� ���� �����
	katet = Coordinate.x - station.x;
	katet2 = Coordinate.z - station.z;
	double projection = sqrt(pow(katet, 2) + pow(katet2, 2)); // �������� distance �� ��������� XZ
	beta = katet2 / projection; // �������� ���� �����

	if( AccelerationStates != nullptr && aChangesCounter < AccelerationStatesLen ) { // ���� �������� ���������� � ������������ � ���������� ����������
		if( AccelerationStates[aChangesCounter].time <= curTime ) { // ���� ����������� ����� ���������� ��������� ���������
			Acceleration.x = AccelerationStates[aChangesCounter].Acceleration.x;
			Acceleration.y = AccelerationStates[aChangesCounter].Acceleration.y;
			Acceleration.z = AccelerationStates[aChangesCounter].Acceleration.z;
			aChangesCounter++;
		}
	}
}

//void CAirObject::SendToVoi(CVOI &voi,const double curTime, const bool fake)
//{ 
//	// ��������� ����� �� ������/���� �����/���������/���������� ��������
//	radialSpeed += returnGaussRandom(radialSko);
//	double ep = this->epsilon + returnGaussRandom(epsilonSko);
//	double bt = this->beta + returnGaussRandom(betaSko);
//	double di = this->distance + returnGaussRandom(distanceSko);
//	// ���������� �������������� �������
//
//	//CovMat[0][0] = pow(CAirObject::distanceSko, 2);
//	//CovMat[1][1] = pow(di, 2) + pow(CAirObject::betaSko, 2);
//	//CovMat[2][2] = pow(di, 2) + pow(CAirObject::epsilonSko, 2);
//
//	/*double b1 = exp(pow(-CAirObject::betaSko, 2) / 2);
//	double b2 = exp(pow(-CAirObject::epsilonSko, 2) / 2);
//	CovMat[0][0] = (pow((b1 * b2), -2) - 2) * di * pow(cos(bt), 2) * pow(cos(ep), 2) + (1 / 4) * (pow(di, 2) + CAirObject::distanceSko)
//		* (1 + pow(b1, 4) * cos(2 * bt)) * (1 + pow(b2, 4) * cos(2 * ep));
//	CovMat[1][1] = (pow((b1 * b2), -2) - 2) * di * pow(sin(bt), 2) * pow(cos(ep), 2) + (1 / 4) * (pow(di, 2) + CAirObject::distanceSko)
//		* (1 - pow(b1, 4) * cos(2 * bt)) * (1 + pow(b2, 4) * cos(2 * ep));
//	CovMat[2][2] = (pow((b2), -2) - 2) * pow(di, 2) * pow(sin(ep), 2) + (1 / 2) * (pow(di, 2) + CAirObject::distanceSko)
//		* (1 - pow(b2, 4) * cos(2 * ep));*/
//
//    // ���������� ��������� � ������ ����
//	CVector coordinates;
//	coordinates.y = ep * di;   // ����� ����� 
//	double katet = sqrt(pow(di, 2) - pow(coordinates.y, 2));  // ������� ��������
//	coordinates.z = bt * katet; // ����� �����
//	coordinates.x = sqrt(pow(katet, 2) - pow(coordinates.z, 2));  // ������� ��������
//	
//
//	CResultOfScan* packageDb = new CResultOfScan(coordinates, radialSpeed, curTime /* cov*/); // ������������ ������ ������ ��� �������� �� ���
//	CResultOfScan package(coordinates, radialSpeed, curTime /* cov*/);
//	//voi.pushMeasurements(package);
//	
//	if( fake == false ) {
//		saveData(packageDb);
//	}	else {
//		CNoize* noize = new CNoize(coordinates, radialSpeed, curTime);
//		saveData(noize);
//	}
//
//	delete packageDb;
//}

void CAirObject::SendToDb(const int numTarget, const double curTime)
{
	cout << "\NumberOfTarget number " << numTarget << " found!\nCoordinates without noise    X=" << Coordinate.x << " / Y=" << Coordinate.y << " / Z="
		<< Coordinate.z << "      after " << curTime << "sec";
	cout << "\nacceleration " << Acceleration.x << " / " << Acceleration.y << " / " << Acceleration.z << "  speed " << Speed.x << " / " << Speed.y << " / " << Speed.z;
	CReferenceState* RefPackage = new CReferenceState(Coordinate, Speed, Acceleration, curTime, numTarget); // ������������ ������ ������ ��� �������� � ���� ������
	saveData(RefPackage);
	delete RefPackage;
}

double CAirObject::returnGaussRandom(double sko)
{
	std::normal_distribution<double> range(0, sko);
	return range(gaussGenerator);
}

CAirObject::CAccelerationState::CAccelerationState()
{
	time = 0;
}

CAirObject::CAccelerationState::~CAccelerationState()
{
	
}