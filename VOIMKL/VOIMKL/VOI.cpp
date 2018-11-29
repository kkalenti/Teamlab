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
	// проверка наличия трасс
	if (!BankOfSection[CurrentSector].GetBankTrace().empty())
	{
		int sizeRow = BankOfSection[CurrentSector].GetBankTrace().size();
		int sizeCol = BankOfSection[CurrentSector].GetBankMeasurements().size();
		vector <vector<double>> MatrixSet(sizeRow, vector<double>(sizeCol, 0));
		for (int i = 0; i < sizeRow; i++)
		{
			for (int j = 0; j < sizeCol; j++)
			{
				colvec v = arma::zeros(3);
				v = KalmanFilter.Predict(BankOfSection[CurrentSector].SetBankTrace()[i], BankOfSection[CurrentSector].SetBankMeasurements()[j]);
				double D = countNorma(v, KalmanFilter.GetS());
				if (D <= constSimilarityRate) MatrixSet[i][j] = D;
				else MatrixSet[i][j] = constBigNumber;
			}
		}
		vector<int> assignment;
		HungAlgo.Solve(MatrixSet, assignment);
		for (int i = 0; i < sizeRow; i++)
		{
			if ((assignment[i] != -1) && (MatrixSet[i][assignment[i]] != constBigNumber)) //венгерский алгоритм в любом случае найдет в каждой строке по числу, если кол-во столбцов позволяет,  -1 оно возвращает когда столбцов меньше строк
			{
				KalmanFilter.Predict(BankOfSection[CurrentSector].SetBankTrace()[i], BankOfSection[CurrentSector].SetBankMeasurements()[assignment[i]]);
				KalmanFilter.UpdateMeasure(BankOfSection[CurrentSector].SetBankTrace()[i], BankOfSection[CurrentSector].SetBankMeasurements()[assignment[i]]);
				(BankOfSection[CurrentSector].SetBankTrace())[i].GetlastTime(BankOfSection[CurrentSector].GetBankMeasurements()[assignment[i]].DetectionTime);
				BankOfSection[CurrentSector].SetBankTrace()[i].NullNmiss();
				BankOfSection[CurrentSector].SetBankMeasurements()[assignment[i]].SetReservedForUpdate();
			}
			else
			{
				KalmanFilter.Predict(BankOfSection[CurrentSector].SetBankTrace()[i], BankOfSection[CurrentSector].GetLasttime());	
				KalmanFilter.UpdatePredict(BankOfSection[CurrentSector].SetBankTrace()[i], BankOfSection[CurrentSector].GetLasttime());
				BankOfSection[CurrentSector].SetBankTrace()[i].GetlastTime(BankOfSection[CurrentSector].GetLasttime());
				BankOfSection[CurrentSector].SetBankTrace()[i].IncNmiss();
			}

			CVector ToVoi2Coordinate;
			ToVoi2Coordinate.x = BankOfSection[CurrentSector].SetBankTrace()[i].SetState_X()[0];
			ToVoi2Coordinate.y = BankOfSection[CurrentSector].SetBankTrace()[i].SetState_X()[3];
			ToVoi2Coordinate.z = BankOfSection[CurrentSector].SetBankTrace()[i].SetState_X()[6];
			CVector ToVoi2Speed;
			ToVoi2Speed.x = BankOfSection[CurrentSector].SetBankTrace()[i].SetState_X()[1];
			ToVoi2Speed.y = BankOfSection[CurrentSector].SetBankTrace()[i].SetState_X()[4];
			ToVoi2Speed.z = BankOfSection[CurrentSector].SetBankTrace()[i].SetState_X()[7];
			CVector ToVoi2Acceleration;
			ToVoi2Acceleration.x = BankOfSection[CurrentSector].SetBankTrace()[i].SetState_X()[2];
			ToVoi2Acceleration.y = BankOfSection[CurrentSector].SetBankTrace()[i].SetState_X()[5];
			ToVoi2Acceleration.z = BankOfSection[CurrentSector].SetBankTrace()[i].SetState_X()[8];
			saveData(new CVoi2(ToVoi2Coordinate, ToVoi2Speed, ToVoi2Acceleration,
			BankOfSection[CurrentSector].SetBankTrace()[i].SetlastTime(),
			BankOfSection[CurrentSector].SetBankTrace()[i].GetId()));
		}
		BankOfSection[CurrentSector].DeletMeasurementsAfterUpdate();
	}
	
	// проверка наличия гипотез
	if (!BankOfSection[CurrentSector].GetBankHypo().empty())
	{
		int sizeRow = BankOfSection[CurrentSector].GetBankHypo().size();
		int sizeCol = BankOfSection[CurrentSector].GetBankMeasurements().size();
		vector <vector<double>> MatrixSet(sizeRow, vector<double>(sizeCol, 0));
		for (int i = 0; i < sizeRow; i++)
		{
			for (int j = 0; j < sizeCol; j++)
			{
				colvec v=KalmanFilter.Predict(BankOfSection[CurrentSector].SetBankHypo()[i], BankOfSection[CurrentSector].SetBankMeasurements()[j]);
				double D = countNorma(v, KalmanFilter.GetS());
				if (D <= constSimilarityRate) MatrixSet[i][j] = D;
				else MatrixSet[i][j] = constBigNumber;
			}
		}
		vector<int> assignment;
		HungAlgo.Solve(MatrixSet, assignment);
		for (int i = 0; i < sizeRow; i++)
		{
			if ((assignment[i] != -1) && (MatrixSet[i][assignment[i]] != constBigNumber)) //венгерский алгоритм в любом случае найдет в каждой строке по числу, если кол-во столбцов позволяет,  -1 оно возвращает когда столбцов меньше строк
			{
				KalmanFilter.Predict(BankOfSection[CurrentSector].SetBankHypo()[i], BankOfSection[CurrentSector].SetBankMeasurements()[assignment[i]]);
				KalmanFilter.UpdateMeasure(BankOfSection[CurrentSector].SetBankHypo()[i], BankOfSection[CurrentSector].SetBankMeasurements()[assignment[i]]);
				BankOfSection[CurrentSector].SetBankHypo()[i].GetlastTime(BankOfSection[CurrentSector].GetBankMeasurements()[assignment[i]].DetectionTime);
				BankOfSection[CurrentSector].SetBankHypo()[i].IncApprove();
				BankOfSection[CurrentSector].SetBankHypo()[i].NullNmiss();
				BankOfSection[CurrentSector].SetBankMeasurements()[assignment[i]].SetReservedForUpdate();
			}
			else
			{
				KalmanFilter.UpdatePredict(BankOfSection[CurrentSector].SetBankHypo()[i], BankOfSection[CurrentSector].GetLasttime());
				BankOfSection[CurrentSector].SetBankHypo()[i].GetlastTime(BankOfSection[CurrentSector].GetLasttime());
				BankOfSection[CurrentSector].SetBankHypo()[i].IncNmiss();
				BankOfSection[CurrentSector].SetBankHypo()[i].NullNapprove();
			}
			
			CVector ToHypo2Coordinate;
			ToHypo2Coordinate.x = BankOfSection[CurrentSector].SetBankHypo()[i].SetState_X()[0];
			ToHypo2Coordinate.y = BankOfSection[CurrentSector].SetBankHypo()[i].SetState_X()[3];
			ToHypo2Coordinate.z = BankOfSection[CurrentSector].SetBankHypo()[i].SetState_X()[6];
			CVector ToHypo2Speed;
			ToHypo2Speed.x = BankOfSection[CurrentSector].SetBankHypo()[i].SetState_X()[1];
			ToHypo2Speed.y = BankOfSection[CurrentSector].SetBankHypo()[i].SetState_X()[4];
			ToHypo2Speed.z = BankOfSection[CurrentSector].SetBankHypo()[i].SetState_X()[7];
			CVector ToHypo2Acceleration;
			ToHypo2Acceleration.x = BankOfSection[CurrentSector].SetBankHypo()[i].SetState_X()[2];
			ToHypo2Acceleration.y = BankOfSection[CurrentSector].SetBankHypo()[i].SetState_X()[5];
			ToHypo2Acceleration.z = BankOfSection[CurrentSector].SetBankHypo()[i].SetState_X()[8];
			saveData(new CHypo2(ToHypo2Coordinate, ToHypo2Speed, ToHypo2Acceleration,
				BankOfSection[CurrentSector].SetBankHypo()[i].SetlastTime(),
				BankOfSection[CurrentSector].SetBankHypo()[i].GetId_hyp()));
		}
		BankOfSection[CurrentSector].DeletMeasurementsAfterUpdate();
	}
	
	// проверка наличия измерений
	if (!BankOfSection[CurrentSector].GetBankMeasurements().empty())
	{
		int size = BankOfSection[CurrentSector].GetBankMeasurements().size();
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (i < j) //чтобы не сравнивать одинаковые пары 
				{
					colvec v = arma::zeros(3);
					mat S = arma::zeros(3, 3);
					KalmanFilter.Predict(BankOfSection[CurrentSector].SetBankMeasurements()[i], BankOfSection[CurrentSector].SetBankMeasurements()[j], S, v);	
					double D = countNorma(v, S); 
					if (D <= constSimilarityRate)
					{
						CMeasurements mes = BankOfSection[CurrentSector].GetBankMeasurements()[i];
						CHypo newHypo(std::move(mes));
						KalmanFilter.UpdateMeasure(newHypo, BankOfSection[CurrentSector].SetBankMeasurements()[j]);
						BankOfSection[CurrentSector].SetBankHypo().push_back(newHypo);
						BankOfSection[CurrentSector].SetBankMeasurements()[i].SetReservedForUpdate();
						BankOfSection[CurrentSector].SetBankMeasurements()[j].SetReservedForUpdate();
					}
				}
			}
		}
		BankOfSection[CurrentSector].DeletMeasurementsAfterUpdate();
	}
	BankOfSection[CurrentSector].SectionHypoToTrace(); //переводим гипотезы в трассы
	BankOfSection[CurrentSector].removeOutdatedObjects(); //удаляем то, что слишком долго лежит в хранилище
}

int CVOI::DetectSector(double azimutAngle)
{
	for (int i = 0; i < this->BankOfSection.size(); i++)
	{
		if ((azimutAngle>this->BankOfSection[i].GetAzimutMin()) && (azimutAngle < this->BankOfSection[i].GetAzimutMax())) return i;
	}
	///отлов ошибки
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

double CVOI::countNorma(colvec &v, mat &predictS)
{
	return arma::as_scalar(v.t()*predictS.i()*v);
}