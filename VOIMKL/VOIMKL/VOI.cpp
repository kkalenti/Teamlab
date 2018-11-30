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
	if (!BankTrace.empty())
	{
		int sizeRow = BankTrace.size();
		int sizeCol = BankMeasurements.size();
		vector <vector<double>> MatrixSet(sizeRow, vector<double>(sizeCol, 0));
		for (int i = 0; i < sizeRow; i++)
		{
			for (int j = 0; j < sizeCol; j++)
			{
				KalmanFilter.Predict(BankTrace[i], BankMeasurements[j]);
				double D = countNorma(KalmanFilter.GetV(), KalmanFilter.GetS());
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
				KalmanFilter.Predict(BankTrace[i], BankMeasurements[assignment[i]]);
				KalmanFilter.UpdateMeasure(BankTrace[i], BankMeasurements[assignment[i]]);
				BankTrace[i].NullNmiss();
				ChangeSectorHypoTrace(BankTrace[i]);
				BankMeasurements[assignment[i]].SetReservedForUpdate();
			}
			else
			{
				KalmanFilter.Predict(BankTrace[i], BankOfSection[BankOfSection.size()-1].GetLasttime());
				KalmanFilter.UpdatePredict(BankTrace[i], BankOfSection[BankOfSection.size()-1].GetLasttime());
				BankTrace[i].IncNmiss();
				ChangeSectorHypoTrace(BankTrace[i]);
			}

			CVector ToVoi2Coordinate;
			ToVoi2Coordinate.x = BankTrace[i].SetState_X()[0];
			ToVoi2Coordinate.y = BankTrace[i].SetState_X()[3];
			ToVoi2Coordinate.z = BankTrace[i].SetState_X()[6];
			CVector ToVoi2Speed;
			ToVoi2Speed.x = BankTrace[i].SetState_X()[1];
			ToVoi2Speed.y = BankTrace[i].SetState_X()[4];
			ToVoi2Speed.z = BankTrace[i].SetState_X()[7];
			CVector ToVoi2Acceleration;
			ToVoi2Acceleration.x = BankTrace[i].SetState_X()[2];
			ToVoi2Acceleration.y = BankTrace[i].SetState_X()[5];
			ToVoi2Acceleration.z = BankTrace[i].SetState_X()[8];
			saveData(new CVoi2(ToVoi2Coordinate, ToVoi2Speed, ToVoi2Acceleration,
			BankTrace[i].SetlastTime(), BankTrace[i].GetId()));
		}
		this->DeletMeasurementsAfterUpdate();
	}
	
	// проверка наличия гипотез
	if (!BankHypo.empty())
	{
		int sizeRow = BankHypo.size();
		int sizeCol = BankMeasurements.size();
		vector <vector<double>> MatrixSet(sizeRow, vector<double>(sizeCol, 0));
		for (int i = 0; i < sizeRow; i++)
		{
			for (int j = 0; j < sizeCol; j++)
			{
				KalmanFilter.Predict(BankHypo[i], BankMeasurements[j]);
				double D = countNorma(KalmanFilter.GetV(), KalmanFilter.GetS());
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
				KalmanFilter.Predict(BankHypo[i], BankMeasurements[assignment[i]]);
				KalmanFilter.UpdateMeasure(BankHypo[i], BankMeasurements[assignment[i]]);
				BankHypo[i].IncApprove();
				BankHypo[i].NullNmiss();
				ChangeSectorHypoTrace(BankHypo[i]);
				BankMeasurements[assignment[i]].SetReservedForUpdate();
			}
			else
			{
				KalmanFilter.Predict(BankHypo[i], BankOfSection[BankOfSection.size() - 1].GetLasttime());
				KalmanFilter.UpdatePredict(BankHypo[i], BankOfSection[BankOfSection.size()-1].GetLasttime());
				BankHypo[i].IncNmiss();
				ChangeSectorHypoTrace(BankHypo[i]);
				BankHypo[i].NullNapprove();
			}
			
			/*CVector ToHypo2Coordinate;
			ToHypo2Coordinate.x = BankHypo[i].SetState_X()[0];
			ToHypo2Coordinate.y = BankHypo[i].SetState_X()[3];
			ToHypo2Coordinate.z = BankHypo[i].SetState_X()[6];
			CVector ToHypo2Speed;
			ToHypo2Speed.x = BankHypo[i].SetState_X()[1];
			ToHypo2Speed.y = BankHypo[i].SetState_X()[4];
			ToHypo2Speed.z = BankHypo[i].SetState_X()[7];
			CVector ToHypo2Acceleration;
			ToHypo2Acceleration.x = BankHypo[i].SetState_X()[2];
			ToHypo2Acceleration.y = BankHypo[i].SetState_X()[5];
			ToHypo2Acceleration.z = BankHypo[i].SetState_X()[8];
			saveData(new CHypo2(ToHypo2Coordinate, ToHypo2Speed, ToHypo2Acceleration,
				BankHypo[i].SetlastTime(), BankHypo[i].GetId_hyp()));*/
		}
		DeletMeasurementsAfterUpdate();
	}
	
	// проверка наличия измерений
	if (!BankMeasurements.empty())
	{
		int size = BankMeasurements.size();
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (i < j) //чтобы не сравнивать одинаковые пары 
				{
					colvec v = arma::zeros(3);
					mat S = arma::zeros(3, 3);
					KalmanFilter.Predict(BankMeasurements[i], BankMeasurements[j], S, v);	
					double D = countNorma(KalmanFilter.GetV(), S); 
					if (D <= constSimilarityRate)
					{
						CMeasurements mes = BankMeasurements[i];
						CHypo newHypo(std::move(mes));
						KalmanFilter.Predict(newHypo, BankMeasurements[j]);
						KalmanFilter.UpdateMeasure(newHypo, BankMeasurements[j]);
						BankHypo.push_back(newHypo);
						BankMeasurements[i].SetReservedForUpdate();
						BankMeasurements[j].SetReservedForUpdate();
					}
				}
			}
		}
		DeletMeasurementsAfterUpdate();
	}
	SectionHypoToTrace(); //переводим гипотезы в трассы
	removeOutdatedObjects(); //удаляем то, что слишком долго лежит в хранилище
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
	newmes.SetCurrentSector(CurrentSector);
	this->BankMeasurements.push_back(newmes);
}

void CVOI::pushSectorObserved(double time, double b)
{
	if (FirstTry && (FirstAngle < 0.0))
	{
		int howmanysection = (Bmax - Bmin) / b;
		this->BankOfSection.resize(howmanysection);
		this->FirstAngle = b;
		for (int i = 0; i < howmanysection; i++)
		{
			BankOfSection[i].SetAzimutMin(i*b);
			BankOfSection[i].SetAzimutMax(i*b+b);
		}
	}
	this->BankOfSection[CurrentSector].SetLasttime(time);
	TimeToStartAssociation(b);
	if (FirstTry && (b==Bmax))
	{
		FirstTry = false;
	}
	if (b == Bmax) CurrentSector = 0;
	else (this->CurrentSector++); 	
}

void CVOI::TimeToStartAssociation(double b)
{
	if (FirstTry || (b != Bmax)) return; //проверяем, что обозрено все пространство и, как минимумЮ, второй раз
	associate();
}

double CVOI::countNorma(colvec &v, mat &predictS)
{
	return arma::as_scalar(v.t()*predictS.i()*v);
}

void CVOI::removeOutdatedObjects()
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

void CVOI::SectionHypoToTrace()
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

void CVOI::DeletMeasurementsAfterUpdate()
{
	for (int i = 0; i < BankMeasurements.size(); i++)
	{
		if (BankMeasurements[i].GetReservedForUpdate()){
			this->BankMeasurements.erase(this->BankMeasurements.cbegin() + i);
			i--;
		}
	}
}

void CVOI::ChangeSectorHypoTrace(CBaseTraceHypo &newbase)
{
	for (int in = 0; in < BankOfSection.size(); in++)
	{
		if ((newbase.FromDekartToAzimut()>BankOfSection[in].GetAzimutMin())&&(newbase.FromDekartToAzimut()<(BankOfSection[in].GetAzimutMax()+1)))
		{
			newbase.SetCurrentSector(in);
		}
	}
}