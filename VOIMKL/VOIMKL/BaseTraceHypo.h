#ifndef BaseTraceHypo_H
#define BaseTraceHypo_H
#include "stadfx.h"
#include "Measurements.h"

using namespace arma;
class CHypo;
class CMeasurements;
class CBaseTraceHypo{
protected:
	int Nmiss;
	//bool UpdateWithM = true; //��������� ������ ���������� ������ - ����� ��������� ��� ������������� �������� ����������� � ����������
	//mutable mat Pconst = zeros<mat>(N, N);
	mat P=zeros(N,N);
	colvec x=zeros(N);
	mat Q = zeros(N, N);
public:
	CBaseTraceHypo();
	~CBaseTraceHypo();
	void IncNmiss();
	void NullNmiss(); //��������� ��� ���������� 
	const int GetNmiss();
	mat &SetP();
	colvec &SetState_X();
	mat &SetQ();
	//void UpdateState(mat P, colvec x); //��� ���������� �� ������������� ��� ����������
	//bool GetUpdateWithM();
};

class CTrace: public CBaseTraceHypo{
private:	
	int ID;
public:
	CTrace();
	CTrace(CHypo &&hypo);
	~CTrace();
};

class CHypo : public CBaseTraceHypo{
	friend class CTrace;
private:
	int Napprove;
public:
	CHypo(CMeasurements &newM);
	~CHypo();
	const int GetNapprove();
	void IncApprove();
	void NullNapprove();//
	CTrace HypoToTrace();
};
#endif BaseTraceHypo_H