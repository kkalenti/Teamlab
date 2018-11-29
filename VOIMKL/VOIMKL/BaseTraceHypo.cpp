#include "stdafx.h"

using namespace std;

CBaseTraceHypo::CBaseTraceHypo()
{
	this->Nmiss = 0;
}

CBaseTraceHypo::~CBaseTraceHypo()
{

}

void CBaseTraceHypo::IncNmiss()
{
	this->Nmiss++;
}

void CBaseTraceHypo::NullNmiss()
{
	this->Nmiss = 0;
}

const int CBaseTraceHypo::GetNmiss()
{
	return this->Nmiss;
}

mat &CBaseTraceHypo::SetP()
{
	return this->P;
}

colvec &CBaseTraceHypo::SetState_X()
{
	return this->x;
}

mat &CBaseTraceHypo::SetQ()
{
	return this->Q;
}

CTrace::CTrace() :CBaseTraceHypo()
{
	this->ID = COPIES_COUNT;
	COPIES_COUNT++;
}

CTrace::CTrace(CHypo &&hypo)
{
	x = std::move(hypo.x);
	P = std::move(hypo.P);
	Q = std::move(hypo.Q);
	this->lastTime = hypo.lastTime;
	this->ID = COPIES_COUNT;
	COPIES_COUNT++;
	this->Nmiss = 0;
}

CTrace::~CTrace()
{

}

CHypo::CHypo(CMeasurements &newM) : CBaseTraceHypo()
{
	this->x(0) = newM.Coordinates.x;
	this->x(3) = newM.Coordinates.y;
	this->x(6) = newM.Coordinates.z;
	this->Napprove = 0;
	for (int i1 = 0, r1 = 0; r1 < M; i1 += 3, r1++)
	{
		for (int i2 = 0, r2 = 0; r2 < M; i2 += 3, r2++)
		{
			this->P(i1, i2) = newM.SetR()(r1, r2); //т.к. матрица R меньше P
		}
	}
	this->P(1, 1) = 1500 * 1500;
	this->P(4, 4) = 1500 * 1500;
	this->P(7, 7) = 1500 * 1500;
	this->P(2, 2) = 1000 * 1000;
	this->P(5, 5) = 1000 * 1000;
	this->P(8, 8) = 1000 * 1000;
	this->Q = constQ;
	this->lastTime = newM.DetectionTime;
	this->ID_hyp = COPIES_COUNT2;
	COPIES_COUNT2++;
}

CHypo::~CHypo()
{

}

const int CHypo::GetNapprove()
{
	return this->Napprove;
}

void CHypo::IncApprove()
{
	Napprove++;
}

void CHypo::NullNapprove()
{
	this->Napprove = 0;
}

CTrace CHypo::HypoToTrace()
{
	CTrace resTrace(std::move(*this));
	return resTrace;
}

double CBaseTraceHypo::GetlastTime(double time)
{
	return this->lastTime = time;
}

const double CBaseTraceHypo::SetlastTime()
{
	return this->lastTime;
}

const int CTrace::GetId()
{
	return this->ID;
}

const int CHypo::GetId_hyp()
{
	return this->ID_hyp;
}