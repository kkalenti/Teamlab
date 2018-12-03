#include "stdafx.h"
#include <conio.h>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));
	createMatFile();
	
	CImitator* imitator = new CImitator();
	imitator->Scan();

	delete imitator;
	closeMat();
	_getch();
	return 0;
}