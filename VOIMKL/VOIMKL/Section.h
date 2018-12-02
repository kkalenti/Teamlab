#ifndef SECTION_H
#define SECTION_H
#include <vector>
#include "Measurements.h"
#include "BaseTraceHypo.h"
class CMeasurements;
class CHypo;
class CTrace;

class CSection{
private:
	double AzimutMin, AzimutMax; // ������� ����� �������
	double Lasttime; // ��������� �����, ����� ��������� ���� ������. �� ���� ��� ������� �����!!!
public:
	CSection();
	~CSection();
	const double GetLasttime();
	void SetLasttime(double lasttime); 
	const double GetAzimutMin(); 
	const double GetAzimutMax();
	void SetAzimutMin(double angle);
	void SetAzimutMax(double angle);
};
#endif // SECTION_H
