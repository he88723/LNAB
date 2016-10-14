#include "matrixOP.h"
#include <iostream>

using namespace std;
using namespace Math;

int main(void)
{

	MatrixOP<double> tt{{3,4},{5,1}};

	cout << tt.inverse()*tt <<endl;

	return 0;
}
