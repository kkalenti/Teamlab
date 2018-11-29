#include "Section.h"

CSection:: CSection()
{
	this->AzimutMin = 0;
	this->AzimutMax = 0;
	this->Lasttime = 0;
}

CSection::~CSection()
{

}

const double CSection::GetLasttime()
{
	return this->Lasttime;
}

void CSection::SetLasttime(double lasttime)
{
	this->Lasttime = lasttime;
}

void CSection::removeOutdatedObjects()
{
	for (int i = 0; i < this->BankMeasurements.size(); i++)
	{
		if (this->BankMeasurements[i].GetNmiss() == MeasurMiss)
		{
			this->BankMeasurements.erase(this->BankMeasurements.cbegin() + i);
		}
	}
	for (int i = 0; i < this->BankHypo.size(); i++)
	{
		if (this->BankHypo[i].GetNmiss() == HypoMiss)
		{
			this->BankHypo.erase(this->BankHypo.cbegin() + i);
		}
	}
	for (int i = 0; i < this->BankTrace.size(); i++)
	{
		if (this->BankTrace[i].GetNmiss() == TraceMiss)
		{
			this->BankTrace.erase(this->BankTrace.cbegin() + i);
		}
	}
}

const double CSection::GetAzimutMin()
{
	return this->AzimutMin;
}

const double CSection::GetAzimutMax()
{
	return this->AzimutMax;
}

std::vector<CTrace> &CSection::SetBankTrace()
{
	return this->BankTrace;
}

const std::vector<CTrace> &CSection::GetBankTrace()
{
	return this->BankTrace;
}

std::vector<CHypo> &CSection::SetBankHypo()
{
	return this->BankHypo;
}

const std::vector<CHypo> &CSection::GetBankHypo()
{
	return this->BankHypo;
}

std::vector<CMeasurements> &CSection::SetBankMeasurements()
{
	return this->BankMeasurements;
}

const std::vector<CMeasurements> &CSection::GetBankMeasurements() 
{
	return this->BankMeasurements;
}

void CSection::SectionHypoToTrace()
{
	for (int i = 0; i < this->BankHypo.size(); i++)
	{
		if (BankHypo[i].GetNapprove() == HypoApprove)
		{
			CTrace newTrace = BankHypo[i].HypoToTrace();
			this->BankHypo.erase(this->BankHypo.cbegin() + i);
			i--;
			this->BankTrace.push_back(newTrace);
		}			
	}
}

void CSection::DeletMeasurementsAfterUpdate()
{
	int size= this->BankMeasurements.size();
	for (int i = 0; i < BankMeasurements.size(); i++)
	{
		if (BankMeasurements[i].GetReservedForUpdate()){
			this->BankMeasurements.erase(this->BankMeasurements.cbegin() + i);
			i--;
		}		
	}
}