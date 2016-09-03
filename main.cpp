#include "matrix.h"
#include <iostream>

using namespace std;
using namespace Math;

int main(void)
{

	Matrix<int> trye{{2,5},{7,9}};

	Matrix<int> tttt{{1,1},{1,1}};

	trye = trye + tttt;

	cout << trye[0][0]<<endl;

	return 0;
}
