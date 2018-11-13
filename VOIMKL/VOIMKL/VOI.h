#ifndef VOI_H
#define VOI_H
#include <vector>
#include <Hungarian.h>
#include "stadfx.h"
#include "Section.h"
class CSection;

class CVOI{
private:
	std::vector<CSection> BankOfSection; 
	bool FirstTry; // ������ �� ������ ����� - "��� ����������"
	mutable double Bmin, Bmax; // ������� ������, �� �������� ��������
	double FirstAngle;  // ������ ���� ����� �min
	int CurrentSector; // ������� ������, � ������� ���� ������ ������
	HungarianAlgorithm HungAlgo;
public:
	CVOI();
	~CVOI();
	void SetSizeZone(double bmin, double bmax); // ������������� �min � �max � ������ 
	void associate();
	int DetectSector(double azimutAngle); //���������� � ������ ������� ����������� ���� �� �����
	void pushMeasurements(CResultOfScan newres); // �������� ��������� � ���������� ������
	void pushSectorObserved(double time, double b); // �������� ����� ������� � �����
	void TimeToStartAssociation(double time);// ��������� �� ������ �� ����������
};
#endif VOI_H