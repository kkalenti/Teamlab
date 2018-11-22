	// ����: 02.11.18
// �����: ������ �.�.
// ��������: ����������� �������� ����� - ��������, ������� ����� �����, ���������������� �� ������ �� ������ ������ � ������� �������
// getConfig() - ����� ������ ����, init(char* path, bool withStates) - ������� ������ ����. ����� Scan() ��������� ��������.

#ifndef Imitator_H
#define Imitator_H

#include "AirObject.h"
#include <vector>
#include <random> 
#include "VOI.h"
#include "stdafx.h"

class CImitator {
public:
	CImitator();
	~CImitator();
	void Scan();
private:
	
	CVector stationCoordinates;
	CAirObject* targets;
//	CVOI *GeneralVoi;

	int numberOfTargets;
	int numberOfSteps;  // ������������ ������ � ������
	double currentTime;
	double timeOfTakt; // � ��������
	int minBeta; // � ��������
	int maxBeta; 
	int minEpsilon; // � ��������
	int maxEpsilon;
	std::mt19937 eqGenerator;
	std::mt19937 poGenerator; // ��������� ����������� ��� ����������� ������ ��������

	void getConfig(); // ������������� ��������� �������� ������ ������
	void init(char* path, bool withStates);  // ������������� ����� ������� ������ ������
	int returnUniformRandom(int max);
	int returnPoissonRandom(int lambda);
};

#endif Imitator_H