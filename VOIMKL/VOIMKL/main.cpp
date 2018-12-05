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
	cout << "\n\nIt was other version of Imitator\n";
	_getch();
	return 0;
}