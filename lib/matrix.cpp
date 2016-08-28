#include "matrix.h"

int Matrix::whereFirst(int count)
{
	for(int i=0; i<count ;++i)
		if(mainData[i][count])
			return i;	
	return -1;
}

//For Matrix Class~
Matrix Matrix::operator+(const Matrix& added)
{

	if(is_same_size(added))
		return Matrix();

	Matrix rt{this->colCount, this->rowCount};

	for(int i=0; i<added.rowCount ;++i)
		for(int i=0; i<added.colCount ;++i)
			rt[i][j] = *this[i][j] + added[i][j];

	return rt;
}


Matrix Matrix::operator-(const Matrix&)
{

	if(is_same_size(added))
		return Matrix();

	Matrix rt{this->colCount, this->rowCount};

	for(int i=0; i<added.rowCount ;++i)
		for(int i=0; i<added.colCount ;++i)
			rt[i][j] = *this[i][j] - added[i][j];

	return rt;

}


Matrix Matrix::operator*(const Matrix& mutiplied)
{

	if(this->rowCount != mutiplied.colCount)
		return Matrix();
	
	Matrix rt{this->colCount, mutiplied.rowCount};

	int count{0};

	for(int count; count<this->colCount;)
	{	

		for(int i=0; i<mutiplied.colCount ;++i)
		{
			for(int j=0; j<this->rowCount ;++j)
				rt[count][i] += *this[j][count] * mutiplied[i][j];
		}

	}

	return rt;

}

Matrix& Matrix::operator=(Matrix& designated)
{

	for(int i=0; i<this->rowCount ;++i)
	{
		for(int j=0; j<this->colCount ;++j)
			designated[i][j] = *this[i][j];
	}

	return *this;
}

bool Matrix::operator==(const Matrix& matched)
{

	if(this->rowCount != matched.rowCount ||
	   this->colCount != matched.colCount)
		return false;
	
	for(int i=0; i<this->rowCount ;++i)
	{
		for(int j=0; j<this->colCount ;++j)
			if(designated[i][j] != *this[i][j])
				return false;
	}
	return true;
}

Matrix& changeLine(int first, int second)
{

	auto buf = this->mainData[0];

	for(int i=0; i<rowCount ;++i)
		buf[i] = mainData[i][first];

	for(int i=0; i<rowCount ;++i)
		mainData[i][first] = mainData[i][second];

	for(int i=0; i<rowCount ;++i)
		mainData[i][second] = buf[i];
	
	return *this;
}

void Matrix::solution()
{

	while(true)
	{

		for(int i=0; i<colCount ;++i)
		{
			int status{whereFirst(i)};

			if(status == -1 || status == rowCount-1)
				return *this;
			//The status is illogical.			

			inlineOperate(i, 1/mainData[status][i], Matrix::operate::Mutiply);

			for(int i=0; i<colCount ;++j)
			{
				if(!mainData[status][j])
					continue;
				lnlOperate(j, i, Matrix::operate::Minus, mainData[status][j]);
			}

		}
	}

	descend_arrange();
	optimize();
}
