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
	int n = 9; // размерность вектора состояний
	int m = 3; // размерность вектора измерений
	double Dt = 0; // 
	double Dt_squared = 0;
	
	//mat::fixed<9, 9> P; //  ковариационная матрица ошибки оценки вектора состояния
	//mat::fixed<9, 9> F; // Матрица перехода между состояниями.
	//mat::fixed<1, 9> U; // матрица Г
	//mat::fixed<3, 3> S; // Матрица обновления
	//mat::fixed<3, 9> H; // Матрица наблюдения. Матрица отображающая отношение измерения и состояния
	//mat::fixed<9, 3> W; // Вессовая матрица. Матрица коэффициентов усиления.
	//mutable mat::fixed<3, 3> R; // Матрица шума измерения
	//mutable mat::fixed<9, 9> Q; // Матрица шума состояния 


	//mat P; //  ковариационная матрица ошибки оценки вектора состояния
	//mat F; // Матрица перехода между состояниями.
	//mat U; // матрица Г
	//mat S; // Матрица обновления
	//
	//mat H; // Матрица наблюдения. Матрица отображающая отношение измерения и состояния
	//mat W; // Вессовая матрица. Матрица коэффициентов усиления.
	//mutable mat R; // Матрица шума измерения
	//mutable mat Q; // Матрица шума состояния 

	mat P = zeros(9, 9); //  ковариационная матрица ошибки оценки вектора состояния
	mat F = zeros(9, 9); // Матрица перехода между состояниями.
	mat U = mat(9, 1); // матрица Г
	//mat U = zeros(9, 1);
	mat S = zeros(3, 3); // Матрица обновления
	mat H = zeros(3, 9); // Матрица наблюдения. Матрица отображающая отношение измерения и состояния
	mat W = zeros(9, 3); // Вессовая матрица. Матрица коэффициентов усиления.
	mutable mat R = eye(3,3); // Матрица шума измерения
	mutable mat Q = mat(1, 1); // Матрица шума состояния
	//mutable mat Q = zeros(1, 1);

	//mat Q_3; // Матрица Q размерности 3 на 3
	//mat Q_1; // Матрица Q размерности 1 на 1
	//mat U_9x3; // Матрица U размерности 9 на 3

	//Априорные данные
	mutable mat P_Const = zeros(9, 9); //	Начальная ковариационная матрица
	colvec x_0 = colvec(9); // Начальный вектор состояний. Вектор состояния динамической системы, который является случайным Гауссовским процессом

	colvec x_pred = zeros(9);  //Вектор в котором будет хранится предсказанное состояние.
	colvec z_pred; //
	colvec z; //Вектор пришедший с ПОИ. Измерения с РЛС.
	colvec v = zeros(3, 1); //Вектор рассогласования/невязки.

};

#endif FilterKalman_H