#include "stdafx.h"
#include <conio.h>
#include <ctime>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv)
{
	srand(time(NULL));
	CImitator* imitator = new CImitator();
	imitator->Scan();
	delete imitator;
	_getch();
	return 0;
}