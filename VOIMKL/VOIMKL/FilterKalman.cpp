#include "FilterKalman.h"



CKalmanFilter::CKalmanFilter()
{
	//P_Const << 100 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << endr
	//  << 0 << 100 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << endr
	//  << 0 << 0 << 100 << 0 << 0 << 0 << 0 << 0 << 0 << endr
	//  << 0 << 0 << 0 << 100 << 0 << 0 << 0 << 0 << 0 << endr
	//  << 0 << 0 << 0 << 0 << 100 << 0 << 0 << 0 << 0 << endr
	//  << 0 << 0 << 0 << 0 << 0 << 100 << 0 << 0 << 0 << endr
	//  << 0 << 0 << 0 << 0 << 0 << 0 << 100 << 0 << 0 << endr
	//  << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 100 << 0 << endr
	//  << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 100 << endr;

	/*P_Const <<  10000, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 10000, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 10000, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 10000, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 10000, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 10000, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 10000, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 10000, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 10000;*/
	//P_0.eye(n, n);
	makeMatrix_H();


}

CKalmanFilter::CKalmanFilter(int n_n, int m_m)
{
	n = n_n;
	m = m_m;
}

void CKalmanFilter::InitialVariableMatrix(colvec & x_0, mat P_01)
{
	this->x_0 = x_0;
	this->P_Const = P_01;

}

void CKalmanFilter::InitialNoiseMatrix(mat R, mat Q)
{
	this->R = R;
	this->Q = Q;
}

void CKalmanFilter::SetFKMatrix(mat U, mat F, mat H)
{
	//можно заменить на то что вообще задать Г H F, в самом начале.
	this->U = U;
	this->F = F;
	this->H = H;
}

void CKalmanFilter::Prediction(double dt)
{

	//setDt(0.2);
	//makeDt_squared();
	update_F(dt);
	update_U(dt);
	//makeMatrix_Q();

	if (flag / 3 > 0)
	{
		x_pred = F * x_pred;
		//x_pred.print("X_pred:");
	}
	else
	{
		this->x_pred = F * x_0;
		//x_pred.print("X_pred:");
	}

	this->P = F * P_Const * F.t() + U * Q * U.t();
	//P.print("P:");
	//this->P = F * P_0 * F.transpose() + U * Q * U.transpose();
	flag++;
}

void CKalmanFilter::Predict(CMeasurements &firstMeasure, CMeasurements &secondMeasure, mat & S_VOI, colvec & v_VOI)
{
	double dt = abs(firstMeasure.detectionTime - secondMeasure.detectionTime);
	update_F(dt);
	update_U(dt);

	P = F * P_Const * F.t() + U * Q * U.t();
	mat R_Meas = firstMeasure.GetR() + secondMeasure.GetR();
	S_VOI = R_Meas + H * P * H.t();
	//  v = firstMeasure.Coordinates - secondMeasure.Coordinates;
	v_VOI = firstMeasure.Setz() - secondMeasure.Setz();
}

colvec  CKalmanFilter::Predict(CBaseTraceHypo & TraceOrHypo, CMeasurements & Measure)
{
	//this->Dt = dt;
	double dt = abs(TraceOrHypo.SetlastTime() - Measure.detectionTime);
	update_F(dt);
	update_U(dt);

	x_pred = F * TraceOrHypo.SetState_X();
	//x_pred = F * x_0;
	z_pred = H * x_pred;
	//v = Measure.Coordinates - z_pred;


	P = F * TraceOrHypo.SetP() * F.t() + U * Q * U.t();
	S = R + H * P * H.t();

	return v;
}


void CKalmanFilter::Measurement()
{
	z_pred = H * x_pred;
	v = z - z_pred;
	S = R + H * P * H.t();
	flag++;
}

void CKalmanFilter::Measurement(colvec & new_z)
{
	this->z = new_z;
	//H.print("H:");
	z_pred = H * x_pred;
	//x_pred.print("xp:");
	//z_pred.print("zp:");
	v = z - z_pred;
	//v.print("v:");
	S = R + H * P * H.t();
	//S.print("s:");
	flag++;
}

void CKalmanFilter::Update()
{
	W = P * H.t() * S.i();
	//W.print("W:");
	x_pred = x_pred + W * v;
	x_pred.print("xp:");
	P = P - W * S * W.t();
	//P.print("P:");
	flag++;
	cout << "\n\nflag:" << flag << endl;

}

void CKalmanFilter::UpdateMeasure(CBaseTraceHypo &TraceOrHypo, CMeasurements &measurement)
{

	v = measurement.Getz() - x_pred;
	W = P * H.t() * S.t();
	P = P - W * S * W.i();
	x_pred = x_pred + W * v;

	//TraceOrHypo.NullNmiss();
}

//изменить функцию
void CKalmanFilter::UpdatePredict(CBaseTraceHypo &TraceOrHypo, double dt)
{
	update_F(dt);
	update_U(dt);

	this->x_pred = F * x_pred;//Хранить в трейсилигипотеза предсказанное значение было бы глупо
	this->P = F * P * F.t() + U * Q * U.t();

	//Trace.IncNmiss();
}

colvec DecartToPolar(const colvec &c)
{
	/*double x, y, z;
	double vx, vy, vz;
	double pr = sqrt(x * x + y * y);
	double pf = atan2(x, y);
	double pdot = (x * vx + y * vy) / pf;

	colvec polar_vector(3);
	polar_vector << pr, pf, pdot;*/
	colvec polar_vector(3);
	return polar_vector;
}

void CKalmanFilter::UpdateEKF(const colvec &z)
{
	// написать функцию конвертации из декартовых координат в полярные координаты
	//Measurement(z);

	W = P * H.t() * S.i();
	x_pred = x_pred + W * v;
	P = P - W * S * W.t();

}

void CKalmanFilter::makeMatrix_Q(mat G, double a)
{
	this->Q = U * U.t() * a * a;
}

void CKalmanFilter::makeMatrix_R()
{
	this->R << 1 << 0 << 0 << endr
		<< 0 << 1 << 0 << endr
		<< 0 << 0 << 1 << endr;
}

void CKalmanFilter::makeMatrix_F()
{
	//this->F <<
	//  1, 0, 0, Dt, 0, 0, Dt_squared, 0, 0,
	//  0, 1, 0, 0, Dt, 0, 0, Dt_squared, 0,
	//  0, 0, 1, 0, 0, Dt, 0, 0, Dt_squared,
	//  0, 0, 0, 1, 0, 0, Dt, 0, 0,
	//  0, 0, 0, 0, 1, 0, 0, Dt, 0,
	//  0, 0, 0, 0, 0, 1, 0, 0, Dt,
	//  0, 0, 0, 0, 0, 0, 1, 0, 0,
	//  0, 0, 0, 0, 0, 0, 0, 1, 0,
	//  0, 0, 0, 0, 0, 0, 0, 0, 1;

	/*this->F <<
	1, Dt, Dt_squared, 0, 0, 0, 0, 0, 0,
	0, 1, Dt, 0, 0, 0, 0, 0, 0,
	0, 0, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 1, Dt, Dt_squared, 0, 0, 0,
	0, 0, 0, 0, 1, Dt, 0, 0, 0,
	0, 0, 0, 0, 0, 1, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 1, Dt, Dt_squared,
	0, 0, 0, 0, 0, 0, 0, 1, Dt,
	0, 0, 0, 0, 0, 0, 0, 0, 1;*/
	this->F << 1 << Dt << Dt_squared << 0 << 0 << 0 << 0 << 0 << 0 << endr
		<< 0 << 1 << Dt << 0 << 0 << 0 << 0 << 0 << 0 << endr
		<< 0 << 0 << 1 << 0 << 0 << 0 << 0 << 0 << 0 << endr
		<< 0 << 0 << 0 << 1 << Dt << Dt_squared << 0 << 0 << 0 << endr
		<< 0 << 0 << 0 << 0 << 1 << Dt << 0 << 0 << 0 << endr
		<< 0 << 0 << 0 << 0 << 0 << 1 << 0 << 0 << 0 << endr
		<< 0 << 0 << 0 << 0 << 0 << 0 << 1 << Dt << Dt_squared << endr
		<< 0 << 0 << 0 << 0 << 0 << 0 << 0 << 1 << Dt << endr
		<< 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 1 << endr;
}

void CKalmanFilter::update_F(double dt)
{
	double ddt = dt * dt;
	this->Dt = dt;
	this->Dt_squared = (dt * dt) / 2;

	/*this->F <<
	1, 0, 0, dt, 0, 0, ddt, 0, 0,
	0, 1, 0, 0, dt, 0, 0, ddt, 0,
	0, 0, 1, 0, 0, dt, 0, 0, ddt,
	0, 0, 0, 1, 0, 0, dt, 0, 0,
	0, 0, 0, 0, 1, 0, 0, dt, 0,
	0, 0, 0, 0, 0, 1, 0, 0, dt,
	0, 0, 0, 0, 0, 0, 1, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 1, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 1;*/

	this->F << 1 << Dt << Dt_squared << 0 << 0 << 0 << 0 << 0 << 0 << endr
		<< 0 << 1 << Dt << 0 << 0 << 0 << 0 << 0 << 0 << endr
		<< 0 << 0 << 1 << 0 << 0 << 0 << 0 << 0 << 0 << endr
		<< 0 << 0 << 0 << 1 << Dt << Dt_squared << 0 << 0 << 0 << endr
		<< 0 << 0 << 0 << 0 << 1 << Dt << 0 << 0 << 0 << endr
		<< 0 << 0 << 0 << 0 << 0 << 1 << 0 << 0 << 0 << endr
		<< 0 << 0 << 0 << 0 << 0 << 0 << 1 << Dt << Dt_squared << endr
		<< 0 << 0 << 0 << 0 << 0 << 0 << 0 << 1 << Dt << endr
		<< 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 1 << endr;

}
void CKalmanFilter::makeMatrix_H()
{

	this->H << 1 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << endr
		<< 0 << 0 << 0 << 1 << 0 << 0 << 0 << 0 << 0 << endr
		<< 0 << 0 << 0 << 0 << 0 << 0 << 1 << 0 << 0 << endr;
}

void CKalmanFilter::makeMatrix_Q()
{
	Q = U * Q * U.t();
}

//void CKalmanFilter::makeMatrix_Q()
//{
//  Q = U * Q_1 * U.t();
//}

void CKalmanFilter::makeMatrix_U()
{
	//this->U << Dt_squared, Dt_squared, Dt_squared, Dt, Dt, Dt, 1, 1, 1;
	this->U << Dt_squared << endr << Dt << endr << 1 << endr << Dt_squared << endr
		<< Dt << endr << 1 << endr << Dt_squared << endr << Dt << endr << 1;
}

void CKalmanFilter::update_U(double dt)
{
	double dt_squared = (dt * dt) / 2;
	//this->U << dt_squared, dt_squared, dt_squared, dt, dt, dt, 1, 1, 1;
	this->U << dt_squared << endr << dt << endr << 1 << endr << dt_squared << endr
		<< dt << endr << 1 << endr << dt_squared << endr << dt << endr << 1;
}

mat & CKalmanFilter::getMatrix_P()
{
	return this->P;
}

void CKalmanFilter::makeDt_squared()
{
	this->Dt_squared = (this->Dt * this->Dt) / 2;

}

void CKalmanFilter::setMatrix_P(mat  new_P)
{
	this->P = new_P;
}

colvec&  CKalmanFilter::getVector_x()
{
	return this->x_pred;
}

mat &CKalmanFilter::GetS()
{
	return this->S;
}

void CKalmanFilter::setDt(double Dt)
{
	this->Dt = Dt;
}

void CKalmanFilter::print_coordinate()
{
	x_pred.print("X_PRED:");
}

//
//mat & CKalmanFilter::GetS()
//{
//	return this->S;
//}

//void CKalmanFilter::print_coordinate()
//{
//	x_pred.print("X_PRED:");
//}