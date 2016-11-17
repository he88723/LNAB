#include "matrixOP.h"
#include <iostream>

using namespace std;
using namespace Math;

int main(void)
{

	MatrixOP<double> ss{{2,4},{5,6}};


	cout << ss.Gauss_solution() << endl;

	return 0;
}
