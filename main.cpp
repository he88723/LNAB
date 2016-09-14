#include "matrixOP.h"
#include <iostream>

using namespace std;
using namespace Math;

int main(void)
{
	
	MatrixOP<double> trye{{1,1},{2,-1}};
	
	MatrixOP<double> test{trye};

	test = trye.inverse();

	cout << trye*test << endl;

return 0;
}
