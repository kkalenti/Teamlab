#include "stdafx.h"
#include <conio.h>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace arma;

int main(int argc, char** argv)
{
	srand(time(NULL));
	CImitator* imitator = new CImitator();
	
	imitator->Scan();

	/*mat P_Const;
	P_Const << 100 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << endr
	<< 0 << 100 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << endr
	<< 0 << 0 << 100 << 0 << 0 << 0 << 0 << 0 << 0 << endr
	<< 0 << 0 << 0 << 100 << 0 << 0 << 0 << 0 << 0 << endr
	<< 0 << 0 << 0 << 0 << 100 << 0 << 0 << 0 << 0 << endr
	<< 0 << 0 << 0 << 0 << 0 << 100 << 0 << 0 << 0 << endr
	<< 0 << 0 << 0 << 0 << 0 << 0 << 100 << 0 << 0 << endr
	<< 0 << 0 << 0 << 0 << 0 << 0 << 0 << 100 << 0 << endr
	<< 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 100 << endr;*/
		
	delete imitator;
	_getch();
	return 0;
}