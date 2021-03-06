#ifndef VOI_H
#define VOI_H
#include "stdafx.h"
#include <vector>
#include <Hungarian.h>
#include "Section.h"
#include "FilterKalman.h"
#include "ResultOfScan.h"

class CSection;

class CVOI{
private:
	std::vector<CSection> BankOfSection; 
	bool FirstTry; // ������ �� ������ ����� - "��� ����������"
	mutable double Bmin, Bmax; // ������� ������, �� �������� ��������
	double FirstAngle;  // ������ ���� ����� �min
	int CurrentSector; // ������� ������, � ������� ���� ������ ������
	HungarianAlgorithm HungAlgo;
	CKalmanFilter KalmanFilter;
public:
	CVOI();
	~CVOI();
	void SetSizeZone(double bmin, double bmax); // ������������� �min � �max � ������ 
	void associate();
	int DetectSector(double azimutAngle); //���������� � ������ ������� ����������� ���� �� �����
	void pushMeasurements(CResultOfScan newres); // �������� ��������� � ���������� ������
	void pushSectorObserved(double time, double b); // �������� ����� ������� � �����
	void TimeToStartAssociation(double time);// ��������� �� ������ �� ����������
	double countNorma(colvec &v, mat &predictS);
};
#endif VOI_H