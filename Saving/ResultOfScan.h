#ifndef ResultOfScan_H
#define ResultOfScan_H

class CResultOfScan {
public:
	CResultOfScan(CVector coordinates, double vr, double time);
	~CResultOfScan();
	CVector Coordinates;
	double detectionTime;
	double Vr;
private:
};
#endif ResultOfScan_H