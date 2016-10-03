#include "matrixOP.h"
#include <iostream>

using namespace std;
using namespace Math;

int main(void)
{

	MatrixOP<double> t{{9},{18}};


	MatrixOP<double> tt{{1,2,3,4},{2,4,6,8}};

	tt.singleRowOP(t, operate::Divide, true);

	cout << tt <<endl;

	return 0;
}
