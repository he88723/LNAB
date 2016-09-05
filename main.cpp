#include "matrix.h"
#include <iostream>

using namespace std;
using namespace Math;

int main(void)
{

	Matrix<double> trye{{2,5},{7,9}};
	
	trye.solution();


	for(int i=0;i<trye.rowCount;++i)
		for(int j=0;j<trye.colCount;++j)
			cout << trye[i][j];	

	return 0;
}
