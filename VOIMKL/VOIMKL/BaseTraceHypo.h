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
public:
	CBaseTraceHypo();
	~CBaseTraceHypo();
	void IncNmiss(); //инкремент счетчика пропусков
	void NullNmiss(); //зануление счетчика пропусков при обновлении 
	const int GetNmiss(); 
	mat &SetP();
	colvec &SetState_X();
	mat &SetQ();
	double GetlastTime(double time);
	const double SetlastTime();
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
	void IncApprove(); //инкремент счетчика подтверждения гипотезы
	void NullNapprove();//зануление счетчика подтверждения при обновлении 
	CTrace HypoToTrace(); //превращаем гипотезу в трассу
	const int GetId_hyp();
};
#endif BaseTraceHypo_H