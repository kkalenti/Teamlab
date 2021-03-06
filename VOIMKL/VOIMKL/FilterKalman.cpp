#include "stdafx.h"

CKalmanFilter::CKalmanFilter()
{
	
	
	P_Const << 100<< 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << endr
		<< 0 << 1500*1500 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << endr
		<< 0 << 0 << 1000 << 0 << 0 << 0 << 0 << 0 << 0 << endr
		<< 0 << 0 << 0 << 100 << 0 << 0 << 0 << 0 << 0 << endr
		<< 0 << 0 << 0 << 0 << 1500 * 1500 << 0 << 0 << 0 << 0 << endr
		<< 0 << 0 << 0 << 0 << 0 << 1000 << 0 << 0 << 0 << endr
		<< 0 << 0 << 0 << 0 << 0 << 0 << 100 << 0 << 0 << endr
		<< 0 << 0 << 0 << 0 << 0 << 0 << 0 << 1500 * 1500 << 0 << endr
		<< 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 1000 << endr;

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
	//����� �������� �� �� ��� ������ ������ � H F, � ����� ������.
	this->U = U;
	this->F = F;
	this->H = H;
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

colvec CKalmanFilter::Predict(CMeasurements &firstMeasure, CMeasurements &secondMeasure)
{
	double dt = abs(firstMeasure.DetectionTime - secondMeasure.DetectionTime);
	update_F(dt);
	update_U(dt);

	P = F * P_Const * F.t() + U * Q * U.t();
	mat R_Meas = firstMeasure.GetR() + secondMeasure.GetR();

	if (firstMeasure.DetectionTime > secondMeasure.DetectionTime)
		this->v = firstMeasure.Setz() - secondMeasure.Setz();
	else
		this->v = secondMeasure.Setz() - firstMeasure.Setz();

	return v;
}
// update with measurement
colvec  CKalmanFilter::Predict(CBaseTraceHypo & TraceOrHypo, CMeasurements & Measure)
{
	//this->Dt = dt;
	double dt = abs(TraceOrHypo.SetlastTime() - Measure.DetectionTime);
	update_F(dt);
	update_U(dt);

	x_pred = F * TraceOrHypo.SetState_X(); //9991
	//x_pred = F * x_0;
	z_pred = H * x_pred; //3991
	v = Measure.Getz() - z_pred;
	//v = Measure.Coordinates - z_pred;


	P = F * TraceOrHypo.SetP() * F.t() + U * Q * U.t(); //99 = 99*99*99+91*1*19
	S = R + H * P * H.t(); // 33+39*99*93

	return v;
}
// update with measurement
colvec  CKalmanFilter::Predict(CBaseTraceHypo & TraceOrHypo, double CurrentTime)
{
	//this->Dt = dt;
	//double dt = abs(TraceOrHypo.SetlastTime() - Measure.DetectionTime);
	double dt = abs(CurrentTime - TraceOrHypo.SetlastTime());
	update_F(dt);
	update_U(dt);

	x_pred = F * TraceOrHypo.SetState_X(); //9991
	////x_pred = F * x_0;
	//z_pred = H * x_pred; //3991
	//v = Measure.Getz() - z_pred;
	////v = Measure.Coordinates - z_pred;


	P = F * TraceOrHypo.SetP() * F.t() + U * Q * U.t(); //99 = 99*99*99+91*1*19
	//S = R + H * P * H.t(); // 33+39*99*93

	return v;
}

void CKalmanFilter::Predict(CMeasurements &firstMeasure, CMeasurements &secondMeasure, mat & S_VOI, colvec & v_VOI)
{
	double dt = abs(firstMeasure.DetectionTime - secondMeasure.DetectionTime);
	//dt = 0.1; // ������������ ���� ������ �� ����� �������� ������ �� �������
	//dt = 2;
	update_F(dt);
	update_U(dt);
	//double w1 = P_Const(0, 0);
	//double w2 = P_Const(0, 1);
	//double w3 = P_Const(0, 2);
	//double w4 = P_Const(1, 0);
	//double w5 = P_Const(1, 1);
	//double w6 = P_Const(1, 2);
	//double w7 = P_Const(2, 0);
	//double w8 = P_Const(2, 1);
	//double w9 = P_Const(2, 2);
	//F.print("F:");
	//U.print("U:");
	//P_Const.print("P:");

	Q(0, 0) = 6;
	P = F * P_Const * F.t() + U * Q * U.t();
	//P.print("P which i need:");
	mat R_Meas = firstMeasure.GetR() + secondMeasure.GetR();
	/*mat R_Meas = zeros(3, 3);
	R_Meas << 0.001 << 0.001 << 0.001 << endr
		<< 0.001 << 0.001 << 0.001 << endr
		<< 0.001 << 0.001 << 0.001 << endr;*/
	S_VOI = R_Meas + H * P * H.t();
	//S_VOI.print("S_VOI:");
	//  v = firstMeasure.Coordinates - secondMeasure.Coordinates;
	dcolvec first = firstMeasure.Setz();
	//first.print("first:");
	dcolvec second = secondMeasure.Setz();
	//second(2) = 2976;
	//second.print("second:");

	//v_VOI = firstMeasure.Setz() - secondMeasure.Setz();
	v_VOI = first - second;
	//v_VOI.print("v_VOI:");

	this->v = v_VOI;
	this->S = S_VOI;
}



void CKalmanFilter::UpdateMeasure(CBaseTraceHypo &TraceOrHypo, CMeasurements &measurement)
{
	//colvec x_pred = zeros(9);
	//v = measurement.Getz() - x_pred;
	/*x_pred(0) = 10000;
	x_pred(3) = 999;
	x_pred(6) = 21;*/
	v(0) = measurement.Getz()(0) - x_pred(0);
	v(1) = measurement.Getz()(1) - x_pred(3);
	v(2) = measurement.Getz()(2) - x_pred(6);
	///*x_pred.print("x_pred:");
	//v.print("v:");
	//S.print("S:");
	//P.print("P:");
	//*/H.print("H:");
	W = P * H.t() * S.t();//93 = 99*93*33
	//W.print("W:");
	P = P - W * S * W.t();//99 = 99 - 93*33*39
	//P.print("P:");
	x_pred = x_pred + W * v;
	//x_pred.print("x_pred:");
	//TraceOrHypo.NullNmiss();
}

//�������� �������
void CKalmanFilter::UpdatePredict(CBaseTraceHypo &TraceOrHypo, double CurrentTime)
{
	double dt = CurrentTime - TraceOrHypo.SetlastTime();
	update_F(dt);
	update_U(dt);

	this->x_pred = F * x_pred;//������� � ���������������� ������������� �������� ���� �� �����
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
	// �������� ������� ����������� �� ���������� ��������� � �������� ����������
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
	//double ddt = dt * dt;
	/*this->Dt = dt;
	this->Dt_squared = (dt * dt) / 2;*/

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
	double dt_squared = (dt * dt) / 2;
	//this->U << dt_squared, dt_squared, dt_squared, dt, dt, dt, 1, 1, 1;
	/*this->U << dt_squared << endr << dt << endr << 1 << endr << dt_squared << endr
		<< dt << endr << 1 << endr << dt_squared << endr << dt << endr << 1;*/


	this->F << 1 << dt << dt_squared << 0 << 0 << 0 << 0 << 0 << 0 << endr
		<< 0 << 1 << dt << 0 << 0 << 0 << 0 << 0 << 0 << endr
		<< 0 << 0 << 1 << 0 << 0 << 0 << 0 << 0 << 0 << endr
		<< 0 << 0 << 0 << 1 << dt << dt_squared << 0 << 0 << 0 << endr
		<< 0 << 0 << 0 << 0 << 1 << dt << 0 << 0 << 0 << endr
		<< 0 << 0 << 0 << 0 << 0 << 1 << 0 << 0 << 0 << endr
		<< 0 << 0 << 0 << 0 << 0 << 0 << 1 << dt << dt_squared << endr
		<< 0 << 0 << 0 << 0 << 0 << 0 << 0 << 1 << dt << endr
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

colvec &CKalmanFilter::GetV()
{
	return this->v;
}

void CKalmanFilter::print_coordinate()
{
	x_pred.print("X_PRED:");
}

