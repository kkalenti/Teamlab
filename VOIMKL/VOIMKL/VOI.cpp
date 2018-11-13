#include "VOI.h"
using namespace std;

CVOI::CVOI() : BankOfSection(1)
{
	this->Bmin = 0;
	this->Bmax = 0;
	this->FirstTry = true;
	this->FirstAngle = -1;
	this->CurrentSector = 0;
}

CVOI::~CVOI()
{

}

void CVOI::SetSizeZone(double bmin, double bmax)
{
	this->Bmin = bmin;
	this->Bmax = bmax;
}

void CVOI::associate()
{
	if (!BankOfSection[CurrentSector].GetBankTrace().empty())
	{
		int sizeRow = BankOfSection[CurrentSector].GetBankTrace().size();
		int sizeCol = BankOfSection[CurrentSector].GetBankMeasurements().size();
		vector <vector<double>> MatrixSet(sizeRow, vector<double>(sizeCol, 0));
		for (int i = 0; i < sizeRow; i++)
		{
			for (int j = 0; j < sizeCol; j++)
			{
				///FK - ����/���������
			}
		}
		vector<int> assignment;
		HungAlgo.Solve(MatrixSet, assignment);
		for (int i = 0; i < sizeRow; i++)
		{
			if ((assignment[i] != -1) && (MatrixSet[i][assignment[i]] != constBigNumber)) //���������� �������� � ����� ������ ������ � ������ ������ �� �����, ���� ���-�� �������� ���������,  -1 ��� ���������� ����� �������� ������ �����
			{
				//FK ������� ��� i ������ ���������� �� assigment[i]
				BankOfSection[CurrentSector].SetBankTrace()[i].NullNmiss();
			}
			else
			{
				//��������� � ������� �������������� ���������
				BankOfSection[CurrentSector].SetBankTrace()[i].IncNmiss();
			}
		}
	}

	if (!BankOfSection[CurrentSector].GetBankHypo().empty())
	{
		int sizeRow = BankOfSection[CurrentSector].GetBankHypo().size();
		int sizeCol = BankOfSection[CurrentSector].GetBankMeasurements().size();
		vector <vector<double>> MatrixSet(sizeRow, vector<double>(sizeCol, 0));
		for (int i = 0; i < sizeRow; i++)
		{
			for (int j = 0; j < sizeCol; j++)
			{
					///FK - ����/���������
			}
		}
		vector<int> assignment;
		HungAlgo.Solve(MatrixSet, assignment);
		for (int i = 0; i < sizeRow; i++)
		{
			if ((assignment[i] != -1) && (MatrixSet[i][assignment[i]] != constBigNumber)) //���������� �������� � ����� ������ ������ � ������ ������ �� �����, ���� ���-�� �������� ���������,  -1 ��� ���������� ����� �������� ������ �����
			{
				//FK ������� ��� i �������� ���������� �� assigment[i]
				BankOfSection[CurrentSector].SetBankHypo()[i].IncApprove();
				BankOfSection[CurrentSector].SetBankHypo()[i].NullNmiss();
			}
			else
			{
				//��������� � ������� �������������� ���������
				BankOfSection[CurrentSector].SetBankHypo()[i].IncNmiss();
				BankOfSection[CurrentSector].SetBankHypo()[i].NullNapprove();
			}
		}
	}

	if (!BankOfSection[CurrentSector].GetBankMeasurements().empty())
	{
		int size = BankOfSection[CurrentSector].GetBankMeasurements().size();
		vector <vector<double>> MatrixSet(size, vector<double>(size, 0));
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (i>=j) MatrixSet[i][j] = constBigNumber; //��������� ��� ��� ������ ���������, ����� �� ������� ��� ����������
				else
				{
					///FK - ������� ���������
				}
			}
		}
		vector<int> assignment;
		HungAlgo.Solve(MatrixSet, assignment);
		for (int i = 0; i < size; i++)
		{
			if ((assignment[i] != -1) && (MatrixSet[i][assignment[i]] != constBigNumber)) //���������� �������� � ����� ������ ������ � ������ ������ �� �����, ���� ���-�� �������� ���������,  -1 ��� ���������� ����� �������� ������ �����
			{
				CMeasurements mes = BankOfSection[CurrentSector].GetBankMeasurements()[i];
				CHypo newHypo(std::move(mes));
				//FK ������� ��� �������� ���������� �� assigment[i]
				BankOfSection[CurrentSector].SetBankHypo().push_back(newHypo);
				//for (int j = 0; j < size; j++)
				//{
				//	MatrixSet[i][j] = constBigNumber; //����� ��������� ��������� ������ ��� ������������� ���������
				//	MatrixSet[j][i] = constBigNumber;
				//}
				//BankOfSection[CurrentSector].SetBankHypo().erase(BankOfSection[CurrentSector].SetBankHypo().cbegin() + i);
				//BankOfSection[CurrentSector].SetBankHypo().erase(BankOfSection[CurrentSector].SetBankHypo().cbegin() + assignment[i]);
				//��� �� ����� ��������, ������ ��� ��� ������� ������������� �������, ��� ��� � ��������� ��������� �����
			}
		}
	}
	BankOfSection[CurrentSector].SectionHypoToTrace(); //��������� �������� � ������
	BankOfSection[CurrentSector].removeOutdatedObjects(); //������� ��, ��� ������� ����� ����� � ���������
}

int CVOI::DetectSector(double azimutAngle)
{
	for (int i = 0; i < this->BankOfSection.size(); i++)
	{
		if ((azimutAngle>this->BankOfSection[i].GetAzimutMin()) && (azimutAngle < this->BankOfSection[i].GetAzimutMax())) return i;
	}
	///����� ������
}

void CVOI::pushMeasurements(CResultOfScan newres)
{
	CMeasurements newmes(newres);
	this->BankOfSection[CurrentSector].SetBankMeasurements().push_back(newmes);
}

void CVOI::pushSectorObserved(double time, double b)
{
	if (FirstTry && (FirstAngle < 0.0))
	{
		int howmanysection = (Bmax - Bmin) / b;
		this->BankOfSection.resize(howmanysection);
		this->FirstAngle = b;
	}
	TimeToStartAssociation(time);
	if (FirstTry && (b==Bmax))
	{
		FirstTry = false;
	}
	
	if (b == Bmax) CurrentSector = 0;
	else (this->CurrentSector++); 

	this->BankOfSection[CurrentSector].SetLasttime(time);
}

//void CVOI::TimeToStartAssociation(double time)
//{
//	if (FirstTry||(CurrentSector==0)) return;
//	if (BankOfSection[CurrentSector - 1].GetLasttime() > BankOfSection[CurrentSector].GetLasttime())
//	{
//		associate();
//		if (CurrentSector == BankOfSection.size()) associate_one();
//	}
//}

void CVOI::TimeToStartAssociation(double time)
{
	if (FirstTry) return;
	associate();
}
