#include "matrix.h"

using namespace Math;

void merge_recursive(int in[], int reg[], int start, int end)
{

	if(start>=end)
		return;

	int start1{start};
	int start2{(end-start)>>1+start};
	int end1{(end-start)>>1+start};
	int end2{end};

	merge_recursive(in, reg, start1, end1);
	merge_recursive(in, reg, start2, end2);

	int k{start};
	while(start1 <= end1 && start2 <= end2)
		reg[k++] = in[start1] < in[start2]?in[start1++]:in[start2];
	while(start1 <= end1)
		reg[k++] = in[start1++];
	while(start2 <= end2)
		reg[k++] = in[start2++];

	for(k=start; k<end ; ++k)
		in[k] = reg[k];
}

void arrange(int in[], int len)
{

	int reg[len];
	merge_recursive(in, reg, 0, len-1);
}

///////////////////////////////////////////////////Matrix Class

template <class Type>
int Matrix<Type>::whereFirst(int count)
{
	for(int i=0; i<count ;++i)
		if(this -> mainData[i][count])
			return i;	
	return -1;
}

template <class Type>
Matrix<int> Matrix<int>::operator+(const Matrix<int>& added)
{

	if(is_same_size(added))
		return Matrix();

	Matrix rt{this->colCount, this->rowCount};

	for(int i=0; i<added.rowCount ;++i)
		for(int j=0; j<added.colCount ;++j)
			rt[i][j] = *this[i][j] + added[i][j];

	return rt;
}

template <class Type>
Matrix<Type> Matrix<Type>::operator-(const Matrix<Type>& minus)
{

	if(is_same_size(minus))
		return Matrix();

	Matrix rt{this->colCount, this->rowCount};

	for(int i=0; i<minus.rowCount ;++i)
		for(int j=0; j<minus.colCount ;++j)
			rt[i][j] = *this[i][j] - minus[i][j];

	return rt;

}


template <class Type>
Matrix<Type> Matrix<Type>::operator*(const Matrix<Type>& mutiplied)
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

template <class Type>
Matrix<int>& Matrix<int>::operator=(const Matrix<int>& designated)
{

	for(int i=0; i<this->rowCount ;++i)
	{
		for(int j=0; j<this->colCount ;++j)
			designated[i][j] = *this[i][j];
	}

	return *this;
}

template <class Type>
bool Matrix<Type>::operator==(const Matrix<Type>& matched)
{

	if(this->rowCount != matched.rowCount ||
	   this->colCount != matched.colCount)
		return false;
	
	for(int i=0; i<this->rowCount ;++i)
	{
		for(int j=0; j<this->colCount ;++j)
			if(mainData[i][j] != *this[i][j])
				return false;
	}
	return true;
}

template <class Type>
void Matrix<Type>::changeLine(int first, int second)
{
	if(first == second)
		return;

	auto buf = this->mainData[0];

	for(int i=0; i<rowCount ;++i)
		buf[i] = mainData[i][first];

	for(int i=0; i<rowCount ;++i)
		mainData[i][first] = mainData[i][second];

	for(int i=0; i<rowCount ;++i)
		mainData[i][second] = buf[i];
}

template <class Type>
void Matrix<Type>::descend_arrange()
{

	int lineRef[colCount];

	for(int i=0; i<colCount ;++i)
		lineRef[i] = whereFirst(i);

	arrange(lineRef, colCount);

	for(int i=0; i<colCount ;++i)
		changeLine(i,lineRef[i]);
}

template <class Type>
void Matrix<Type>::solution()
{

	while(true)
	{

		for(int i=0; i<colCount ;++i)
		{
			int status{whereFirst(i)};

			if(status == -1 || status == rowCount-1)
				return *this;
			//The status is illogical.			

			inlineOperate(i, 1/mainData[status][i], Math::operate::Mutiply);

			for(int j=0; j<colCount ;++j)
			{
				if(!mainData[status][j])
					continue;
				lnlOperate(j, i, Math::operate::Minus, mainData[status][j]);
			}

		}
	}

	descend_arrange();
}
