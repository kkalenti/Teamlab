#ifndef BaseTraceHypo_H
#define BaseTraceHypo_H
#include <armadillo>
#include "Measurements.h"

using namespace arma;
class CHypo;
class CMeasurements;
class CBaseTraceHypo{
protected:
	int Nmiss;
	mat P = zeros(N,N);
	colvec x = zeros(N); 
	mat Q = zeros(N, N);
	double lastTime;
	//double CurrentSector;
public:
	CBaseTraceHypo();
	~CBaseTraceHypo();
	void IncNmiss(); //��������� �������� ���������
	void NullNmiss(); //��������� �������� ��������� ��� ���������� 
	const int GetNmiss(); 
	mat &SetP();
	void GetP(mat &ppred);
	colvec &SetState_X();
	void GetState_X(colvec &xpred);
	mat &SetQ();
	double GetlastTime(double time);
	const double SetlastTime();
	double FromDekartToAzimut();
	//void SetCurrentSector(int Sector);
	//const int GetCurrentSector();
};

class CTrace: public CBaseTraceHypo{
private:	
	int ID;
public:
	CTrace();
	CTrace(CHypo &&hypo);
	~CTrace();
	const int GetId();
};

class CHypo : public CBaseTraceHypo{
	friend class CTrace;
private:
	int Napprove;
	int ID_hyp;
public:
	CHypo(CMeasurements &newM);
	~CHypo();
	const int GetNapprove();
	void IncApprove(); //��������� �������� ������������� ��������
	void NullNapprove();//��������� �������� ������������� ��� ���������� 
	CTrace HypoToTrace(); //���������� �������� � ������
	const int GetId_hyp();
};
#endif BaseTraceHypo_H