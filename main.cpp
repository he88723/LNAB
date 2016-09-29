#include "matrixOP.h"
#include <iostream>

using namespace std;
using namespace Math;

int main(void)
{
	
	MatrixOP<double> trye{4,5};
	trye.rndSet(5.7, 11.9);

	MatrixOP<double> tttt{5,4};
	tttt.rndSet(5.7, 11.9);

	cout << trye*tttt;

	return 0;
}
