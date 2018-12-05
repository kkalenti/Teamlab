#include "stdafx.h"
#include <math.h>
#include <random>
#include <ctime>
#include "AirObject.h"

CAirObject::CAirObject() 
{
	this->AccelerationStates = nullptr;
	this->Coordinate.x = 0;
	this->Coordinate.y = 0;
	this->Coordinate.z = 0;
	this->aChangesCounter = 0;
	CovMat = new double*[3];
	for (int i = 0; i < 4; i++) {
		CovMat[i] = new double[4];
		for (int j = 0; j < 4; j++) {
			CovMat[i][j] = 0;
		}
	}
	CovMat[0][0] = pow(CAirObject::SkoX, 2);
	CovMat[1][1] = pow(CAirObject::SkoY, 2);
	CovMat[2][2] = pow(CAirObject::SkoZ, 2);
	CovMat[3][3] = pow(CAirObject::radialSko, 2);
}

CAirObject::CAirObject(int fx, int fy, int fz, const CVector& station)
{
	Coordinate.x = fx;
	Coordinate.y = fy;
	Coordinate.z = fz;
	std::random_device device;
	gaussGenerator.seed(device());
	CovMat = new double*[4];
	for (int i = 0; i < 4; i++) {
		CovMat[i] = new double[4];
		for (int j = 0; j < 4; j++) {
			CovMat[i][j] = 0;
		}
	}
	CovMat[0][0] = pow(CAirObject::SkoX, 2);
	CovMat[1][1] = pow(CAirObject::SkoY, 2);
	CovMat[2][2] = pow(CAirObject::SkoZ, 2);
	CovMat[3][3] = pow(CAirObject::radialSko, 2);
}

CAirObject::~CAirObject() 
{
	if (AccelerationStates != nullptr) {
		delete[] AccelerationStates;
	}
}

double CAirObject::SkoX; // все необходимые среднеквадратические отклонения для шумов
double CAirObject::SkoY;
double CAirObject::SkoZ;
double CAirObject::accelerationSko;
double CAirObject::radialSko;
int CAirObject::typeOfEmulation; 
int CAirObject::fakeTargetIntensity;
int CAirObject::lostMeasurements;

void CAirObject::Update(const double time, const double curTime, const CVector& station) // time - время такта
{                
	// пересчет координат
	Coordinate.x += Speed.x * time + 0.5 * Acceleration.x * pow(time, 2);
	Coordinate.z += Speed.z * time + 0.5 * Acceleration.z * pow(time, 2);
	Coordinate.y += Speed.y * time + 0.5 * Acceleration.y * pow(time, 2);
	if (Coordinate.y <= 0) {
		exit(-1);
	}; // объект ушел под землю

	// пересчет скоростей
	Speed.x += Acceleration.x * time;
	Speed.y += Acceleration.y * time;
	Speed.z += Acceleration.z * time;
	// пересчет радиальной скорости
	// модуль радиус-вектора
	double radiusSize = sqrt(pow((Coordinate.x - station.x), 2) + pow((Coordinate.y - station.y), 2) + pow((Coordinate.z - station.z), 2));
	CVector normir; // нормированный радиус вектор
	normir.x = (Coordinate.x - station.x) / radiusSize;
	normir.y = (Coordinate.y - station.y) / radiusSize;
	normir.z = (Coordinate.z - station.z) / radiusSize;
	radialSpeed = Speed.x * normir.x + Speed.y * normir.y + Speed.z * normir.z;
	// влиянеие шумов на ускорения если они есть
	if( accelerationSko != 0 ) {
		Acceleration.x += returnGaussRandom(accelerationSko);
		Acceleration.z += returnGaussRandom(accelerationSko);
		Acceleration.y += returnGaussRandom(accelerationSko);
	}
	// пересчет азимута
	distance = sqrt(pow(Coordinate.x - station.x, 2) + pow(Coordinate.y - station.y, 2) + pow(Coordinate.z - station.z, 2)); // расстояние до цели
	double katet = sqrt(pow(Coordinate.z - station.z, 2) + pow(Coordinate.x - station.x, 2)); // система координат, где Y это Z, X это Y, а Z это X
	double katet2 = sqrt(pow(distance, 2) - pow(katet, 2));
	epsilon = katet2 / distance; // пересчет азимута
	// пересчет угла места
	katet = Coordinate.x - station.x;
	katet2 = Coordinate.z - station.z;
	double projection = sqrt(pow(katet, 2) + pow(katet2, 2)); // проекция distance на плоскость XZ
	beta = katet2 / projection; // пересчет угла места

	if( AccelerationStates != nullptr && aChangesCounter < AccelerationStatesLen ) { // если имитатор рабаботает в конфигурации с переменным ускорением
		if( AccelerationStates[aChangesCounter].time <= curTime ) { // если закончилось время очередного состояния ускорения
			Acceleration.x = AccelerationStates[aChangesCounter].Acceleration.x;
			Acceleration.y = AccelerationStates[aChangesCounter].Acceleration.y;
			Acceleration.z = AccelerationStates[aChangesCounter].Acceleration.z;
			aChangesCounter++;
		}
	}
}

void CAirObject::SendToVoi(CVOI &voi, const double curtime, const bool fake)
{ 
	// наложение шумов на азимут/угол места/дистанцию/радиальную скорость
	radialSpeed += returnGaussRandom(radialSko);

	CVector coordinates;
	coordinates.x = Coordinate.x + returnGaussRandom(SkoX);
	coordinates.y = Coordinate.y + returnGaussRandom(SkoY);
	coordinates.z = Coordinate.z + returnGaussRandom(SkoZ);
	
	coordinates.x = this->Round(9, coordinates.x);
	coordinates.y = this->Round(9, coordinates.y);
	coordinates.z = this->Round(9, coordinates.z);

	CResultOfScan* packagedb = new CResultOfScan(coordinates, radialSpeed, curtime, CovMat); // формирование пакета данных для передачи на вои
	CResultOfScan package(coordinates, radialSpeed, curtime, CovMat);
	voi.pushMeasurements(package);
	
	if( fake == false ) {
		saveData(packagedb);
		cout << "\nNoised Coordinates     X=" << coordinates.x << "  Y=" << coordinates.y << "  Z=" << coordinates.z << "\n";
	}	else {
		CNoize* Noize = new CNoize(coordinates, radialSpeed, curtime);
		saveData(Noize);
	}

	delete packagedb;
}

void CAirObject::SendToDb(const int numTarget, const double curTime)
{
	cout << "\nTarget " << numTarget << ":\nPerfect Coordinates    X=" << Coordinate.x << "  Y=" << Coordinate.y << "  Z="
		<< Coordinate.z << " ---------------------- DetectionTime: " << curTime << "sec";
	cout << "\n      Accelerations    " << Acceleration.x << " / " << Acceleration.y << " / " << Acceleration.z << "      Speeds    "
		<< Speed.x << " / " << Speed.y << " / " << Speed.z;
	CReferenceState* RefPackage = new CReferenceState(Coordinate, Speed, Acceleration, curTime, numTarget); // формирование пакета данных для передачи в базу данных
	saveData(RefPackage);
	delete RefPackage;
}

double CAirObject::returnGaussRandom(double sko)
{
	if (sko == 0) {
		return 0;
	}
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

double CAirObject::Round(int pos, double val)
{
	string buf = std::to_string(val);
	return stod(buf);
}