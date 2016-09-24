#include "matrixOP.h"
#include <iostream>

using namespace std;
using namespace Math;

int main(void)
{
	
	MatrixOP<double> trye{{1,2,3},{0,-4,1}};


	cout << trye << "\n\n\n" << trye.transpose();

	return 0;
}
