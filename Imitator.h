#ifndef Imitator_H
#define Imitator_H

#include "AirObject.h"
#include <vector>

class CImitator {
public:
	CImitator();
	~CImitator();
	void Scan();
private:
	CAirObject* targets;
	CVector StationCoordinates;
	int NumberOfTargets;
	int NumberOfSteps;  // äëèòåëüíîñòü ìîäåëè â òàêòàõ
	float CurrentTime;
	float TimeOfTakt; // â ñåêóíäàõ
	int widthOfAzimuth; // â ãðàäóñàõ
	int heightOfPlaceCorner; // â ãðàäóñàõ

	void GetConfig();
};

#endif Imitator_H