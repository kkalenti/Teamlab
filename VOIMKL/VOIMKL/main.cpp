#include "stdafx.h"
#include <conio.h>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv)
{

	CKalmanFilter test;
	test.setDt_Dt_squared(0.24);
	test.makeMatrix_F();
	test.makeMatrix_U();

	/*srand(time(NULL));
	CImitator* imitator = new CImitator();
	imitator->Scan();
	delete imitator;*/
	_getch();
	return 0;
}