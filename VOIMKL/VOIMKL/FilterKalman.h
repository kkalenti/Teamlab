#ifndef FilterKalman_H
#define FilterKalman_H
#include "stadfx.h"
#include "BaseTraceHypo.h"
#include "Measurements.h"

using namespace std;
using namespace arma;


class CKalmanFilter
{
public:
	CKalmanFilter();
	CKalmanFilter(int n, int m);

	void InitialVariableMatrix(colvec & x_0, mat P_0);
	void SetFKMatrix(mat U, mat H, mat F);
	void InitialNoiseMatrix(mat R, mat Q);

	mat & getMatrix_P();
	void setMatrix_P(mat);
	colvec & getVector_x();
	void setDt(double);

	void makeMatrix_Q(mat, double);
	void makeMatrix_Q();
	void makeMatrix_R();
	void makeMatrix_U();
	void makeMatrix_F();
	void makeMatrix_H();
	void makeDt_squared();


	void update_F(double);
	void update_U(double);

	void Predict(CMeasurements &firstMeasure, CMeasurements &secondMeasure, mat &, colvec &);
	colvec Predict(CBaseTraceHypo &Trace, CMeasurements &Measure);

	void UpdateMeasure(CBaseTraceHypo&, CMeasurements&);
	void UpdatePredict(CBaseTraceHypo&, double);

	void Prediction(double);
	void Measurement(colvec & new_z);
	void Measurement();
	void Update();
	void UpdateEKF(const colvec &);
	mat &GetS();


	void print_coordinate();

protected:
	//CKalmanFilter() {}

	int flag = 0;
	int n = 9; // ����������� ������� ���������
	int m = 3; // ����������� ������� ���������
	double Dt = 0; // 
	double Dt_squared = 0;
	
	//mat::fixed<9, 9> P; //  �������������� ������� ������ ������ ������� ���������
	//mat::fixed<9, 9> F; // ������� �������� ����� �����������.
	//mat::fixed<1, 9> U; // ������� �
	//mat::fixed<3, 3> S; // ������� ����������
	//mat::fixed<3, 9> H; // ������� ����������. ������� ������������ ��������� ��������� � ���������
	//mat::fixed<9, 3> W; // �������� �������. ������� ������������� ��������.
	//mutable mat::fixed<3, 3> R; // ������� ���� ���������
	//mutable mat::fixed<9, 9> Q; // ������� ���� ��������� 


	//mat P; //  �������������� ������� ������ ������ ������� ���������
	//mat F; // ������� �������� ����� �����������.
	//mat U; // ������� �
	//mat S; // ������� ����������
	//
	//mat H; // ������� ����������. ������� ������������ ��������� ��������� � ���������
	//mat W; // �������� �������. ������� ������������� ��������.
	//mutable mat R; // ������� ���� ���������
	//mutable mat Q; // ������� ���� ��������� 

	mat P = zeros(9, 9); //  �������������� ������� ������ ������ ������� ���������
	mat F = zeros(9, 9); // ������� �������� ����� �����������.
	mat U = mat(9, 1); // ������� �
	//mat U = zeros(9, 1);
	mat S = zeros(3, 3); // ������� ����������
	mat H = zeros(3, 9); // ������� ����������. ������� ������������ ��������� ��������� � ���������
	mat W = zeros(9, 3); // �������� �������. ������� ������������� ��������.
	mutable mat R = eye(3,3); // ������� ���� ���������
	mutable mat Q = mat(1, 1); // ������� ���� ���������
	//mutable mat Q = zeros(1, 1);

	//mat Q_3; // ������� Q ����������� 3 �� 3
	//mat Q_1; // ������� Q ����������� 1 �� 1
	//mat U_9x3; // ������� U ����������� 9 �� 3

	//��������� ������
	mutable mat P_Const = zeros(9, 9); //	��������� �������������� �������
	colvec x_0 = colvec(9); // ��������� ������ ���������. ������ ��������� ������������ �������, ������� �������� ��������� ����������� ���������

	colvec x_pred = zeros(9);  //������ � ������� ����� �������� ������������� ���������.
	colvec z_pred; //
	colvec z; //������ ��������� � ���. ��������� � ���.
	colvec v = zeros(3, 1); //������ ���������������/�������.

};

#endif FilterKalman_H