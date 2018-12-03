#ifndef VOI_H
#define VOI_H
#include "stdafx.h"
#include <vector>
#include <Hungarian.h>
#include "Section.h"
#include "FilterKalman.h"
#include "ResultOfScan.h"
#include "Measurements.h"
#include "BaseTraceHypo.h"

class CSection;
class CMeasurements;
class CHypo;
class CTrace;

class CVOI{
private:
	std::vector<CSection> BankOfSection; //банк секций
	std::vector<CTrace> BankTrace; //банк трасс
	std::vector<CHypo> BankHypo; //банк гипотез
	std::vector<CMeasurements> BankMeasurements; //банк измерений
	bool FirstTry; // флажок на первый обход - "без ассоциации"
	mutable double Bmin, Bmax; // границы обзора, по которому работаем
	double FirstAngle;  // первый угол после Вmin
	int CurrentSector; // текущий сектор, с которым идет работа сейчас
	HungarianAlgorithm HungAlgo; //венгерский алгоритм для рассчета подходящих пар трасса/гипотеза и измерение
	CKalmanFilter KalmanFilter; 
public:
	CVOI();
	~CVOI();
	void SetSizeZone(double bmin, double bmax); // Устанавливаем Вmin и Вmax в классе 
	void associate(); //основной метод, осуществляющий всю работу
	int DetectSector(double azimutAngle); //определяет к какому сектору принадлежит угол на входе
	void pushMeasurements(CResultOfScan newres); // получаем измерения в подходящий сектор
	void pushSectorObserved(double time, double b); // получаем метку времени с углом
	void TimeToStartAssociation(double b);// проверяем не начать ли ассоциацию
	double countNorma(colvec &v, mat &predictS); //считаем норму, на основании которой решаем провести ассоциацию
	void removeOutdatedObjects(); //удалить объекты, не обновлявшиеся на этом цикле
	void SectionHypoToTrace(); //перевод гипотезы в трассу
	void DeletMeasurementsAfterUpdate(); //удалить все измерения после окончания ассоциации
	//void ChangeSectorHypoTrace(CBaseTraceHypo &newbase); //изменить сектор, в котором предположительно находится объект
};
#endif VOI_H