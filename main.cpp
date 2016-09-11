#include "matrix.h"
#include <iostream>

using namespace std;
using namespace Math;

int main(void)
{

	Matrix<double> trye{{1,2,3},{2,0,-1}};
	Matrix<double> tt{{1,4},{2,3},{3,2}};

	Matrix<double> a{trye*tt};

return 0;
}
