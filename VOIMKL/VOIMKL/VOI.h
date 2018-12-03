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
	std::vector<CSection> BankOfSection; //���� ������
	std::vector<CTrace> BankTrace; //���� �����
	std::vector<CHypo> BankHypo; //���� �������
	std::vector<CMeasurements> BankMeasurements; //���� ���������
	bool FirstTry; // ������ �� ������ ����� - "��� ����������"
	mutable double Bmin, Bmax; // ������� ������, �� �������� ��������
	double FirstAngle;  // ������ ���� ����� �min
	int CurrentSector; // ������� ������, � ������� ���� ������ ������
	HungarianAlgorithm HungAlgo; //���������� �������� ��� �������� ���������� ��� ������/�������� � ���������
	CKalmanFilter KalmanFilter; 
public:
	CVOI();
	~CVOI();
	void SetSizeZone(double bmin, double bmax); // ������������� �min � �max � ������ 
	void associate(); //�������� �����, �������������� ��� ������
	int DetectSector(double azimutAngle); //���������� � ������ ������� ����������� ���� �� �����
	void pushMeasurements(CResultOfScan newres); // �������� ��������� � ���������� ������
	void pushSectorObserved(double time, double b); // �������� ����� ������� � �����
	void TimeToStartAssociation(double b);// ��������� �� ������ �� ����������
	double countNorma(colvec &v, mat &predictS); //������� �����, �� ��������� ������� ������ �������� ����������
	void removeOutdatedObjects(); //������� �������, �� ������������� �� ���� �����
	void SectionHypoToTrace(); //������� �������� � ������
	void DeletMeasurementsAfterUpdate(); //������� ��� ��������� ����� ��������� ����������
	//void ChangeSectorHypoTrace(CBaseTraceHypo &newbase); //�������� ������, � ������� ���������������� ��������� ������
};
#endif VOI_H