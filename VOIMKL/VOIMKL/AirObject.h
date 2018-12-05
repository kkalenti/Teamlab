// Дата: 02.11.18
// Автор: Пипчук А.А.
// Описание: описывается класс воздушного объекта и его вложенный класс состояний ускорения, созданный для возможности определять
// изменения траекторий полета в определенные моменты времени

#ifndef AirObject_H
#define AirObject_H

#include <random> 
#include "VOI.h"
class CAirObject {

public:

	class CAccelerationState  // параметры ускорения и время, в которое их необходимо применить
	{
	public:
		CVector Acceleration;
		double time;

		CAccelerationState();
		~CAccelerationState();
	private:
	};

	CAccelerationState* AccelerationStates; // массив переменных состояний ускорения
	int AccelerationStatesLen; // длина массива выше 
	CVector Coordinate; // m
	CVector Speed; // m/c
	CVector Acceleration; // m/c
	static double SkoX; // sko(ско) - среднеквадратическое отклонение, требуется нам для определения нормального распределения
	static double SkoY;
	static double SkoZ;
	static double accelerationSko;
	static double radialSko;
	static int fakeTargetIntensity;
	static int lostMeasurements;
	static int typeOfEmulation; // выбор конфигурации налета

	CAirObject();
	CAirObject(int fx, int fy, int fz, const CVector& station);
	~CAirObject();

	void Update(const double time, const double curTime, const CVector& station); // обновление параметров воздушного объекта
	void SendToVoi(CVOI &cvoi, const double curTime, const bool fake = false); // отправка данных на вторичную обработку
	void SendToDb(const int numTarget, const double curTime); // отправка данных в базу данных
	double GetBeta() { return beta; }
	double GetEpsion() { return epsilon; }

private:
	std::mt19937 gaussGenerator; // нормальное распределение. будем выбирать из него случайное значение для шумов
	double beta; // азимут
	double epsilon; // угол места
	double distance; // расстояние от станции до цели
	double radialSpeed; // радиальная скорость 
	double** CovMat; // ковариационная матрица
	int aChangesCounter; // показывает, какое состояние ускорения на данный момент, если имитатор работает по конфигурации с переменным ускорением

	double returnGaussRandom(double sko);
	double Round(int, double);
};
#endif AirObject_H