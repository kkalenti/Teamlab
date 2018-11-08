#ifndef AirObject_H
#define AirObject_H

struct CVector {
	double x, y, z;
};

class CAirObject {
public:
	CAirObject();
	~CAirObject();

	float beta; // àçèìóò
	float epsilon; // óãîë ìåñòà
	static float epsilonSKO; // sko(ñêî) - ñðåäíåêâàäðàòè÷åñêîå îòêëîíåíèå, òðåáóåòñÿ íàì äëÿ îïðåäåëåíèÿ íîðìàëüíîãî ðàñïðåäåëåíèÿ
	static float betaSKO;
	static float distanceSKO;
	static float accelerationSKO;
	static int typeOfEmulation;

	void Update(const float& time, const CVector& station);
	void SendToVoi(const float& time);
	void SendToDb(const int& Nt, const float& time);
private:
	int factualSpeed;
	float distance; // ðàññòîÿíèå îò ñòàíöèè äî öåëè
	CVector Coordinate; // m
	CVector Speed; // m/c
	CVector Acceleration; // m/c
};
#endif AirObject_H