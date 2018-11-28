#ifndef HYPO2_H
#define HYPO2_H

class CHypo2 {
public:
	CHypo2(CVector coordinate, CVector speed, CVector acceleration, double time, int Nt);
	~CHypo2();

	CVector Coordinate;
	CVector Speed;
	CVector Acceleration;
	double DetectionTime;
	int NumberOfTarget;
private:
};

#endif HYPO2_H