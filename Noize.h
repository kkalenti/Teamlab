#ifndef Noize_H
#define Noize_H

class CNoize {
public:
	CNoize(CVector coordinates, double vr, double time);
	~CNoize();
	CVector Coordinates;
	double detectionTime;
	double Vr;
private:
};
#endif Noize_H