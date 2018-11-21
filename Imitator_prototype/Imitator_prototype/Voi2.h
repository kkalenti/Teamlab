#ifndef VOI2_H
#define VOI2_H

class CVoi2 {
public:
	CVoi2(CVector coordinate, CVector speed, CVector acceleration, double time, int Nt);
	~CVoi2();

	CVector Coordinate;
	CVector Speed;
	CVector Acceleration;
	double DetectionTime;
	int NumberOfTarget;
private:
};

#endif VOI2_H