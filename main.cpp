#include "matrixOP.h"
#include <iostream>

using namespace std;
using namespace Math;

int main(void)
{
	
	MatrixOP<double> trye{{1,8},{13,7}};

	MatrixOP<double> test{trye};

	trye = trye.inverse();

	test = trye * test;

	cout << test << endl;

return 0;
}
