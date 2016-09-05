#ifndef Matrix_H
#define Matrix_H

#include <initializer_list>
#include <iostream>

using namespace std;

void merge_recursive(int in[], int reg[], int start, int end);
void arrange(int in[], int len);

namespace Math
{

/*
template<class Type>
Type det(const Matrix&)
{}

template<class Type>
Type dot_Product(Matrix first, Matrix second)
{}
*/

enum operate{Add, Minus, Mutiply, Divide};

template<class Type>
class Matrix
{

public:

	Matrix(int col = 0, int row = 0) : rowCount{row} , colCount{col}
	{
		if(col && row)
		{
			this->mainData = new Type*[rowCount];

			for(int i=0; i<rowCount ;++i)
			{
				this->mainData[i] = new Type[colCount];
		
				for(int j=0; j<colCount ;++j)
					this->mainData[i][j] = 0;

			}
		}
		else
			this->mainData = nullptr;
		
	}

	Matrix(const Matrix<Type>& matrix) : rowCount{matrix.rowCount} , colCount{matrix.colCount}
	{
	
		this->mainData = new Type*[rowCount];

		for(int i=0; i<rowCount ;++i)
		{
		
			this->mainData[i] = new Type[colCount];

			for(int j=0; j<colCount ;++j)
				this->mainData[i][j] = matrix[i][j];
		
		}
	
	}

	Matrix(std::initializer_list<std::initializer_list<Type>> initList)
	   	: rowCount{(Type)initList.size()} , colCount{(Type)(*initList.begin() ).size()}
	{
		this->mainData = new Type*[rowCount];

		for(int i=0; i<rowCount ;++i)
		{
			this->mainData[i] = new Type[colCount];

			for(int j=0; j<colCount ;++j)
				this->mainData[i][j] = *(((initList.begin()+i)->begin()) + j);
		}
	
	}

	~Matrix()
	{
	
		for	(int i=0; i<rowCount ;++i)
			delete this->mainData[i];
		
		delete this->mainData;
	}

	inline bool set(int row, int col, Type val)
	{
		if(!(0 <= row < rowCount || 0 <= col < colCount))
			return false;
		this->mainData[row][col] = val;
		return true;
	}

	inline bool is_same_size(const Matrix<Type>& matched)
	{

		if(this->colCount != matched.colCount)
			return false;
		else if(this->rowCount != matched.rowCount)
			return false;
		
		return true;

	}

//Operator For Matrix======================================================

	Type* operator[](int row) const
	{
		if(row >= rowCount)
			return nullptr;
		return this->mainData[row];
	}

	Matrix<Type> operator+(const Matrix<Type>& added)
	{
		if(!is_same_size(added))
			return Matrix<Type>();

		Matrix rt{this->colCount, this->rowCount};

		for(int i=0; i<added.rowCount ;++i)
			for(int j=0; j<added.colCount ;++j)
				rt.set(i, j, this->mainData[i][j] + added[i][j]);
		return rt;
	}

	Matrix<Type>  operator-(const Matrix<Type>& minus)
	{
		if(!is_same_size(minus))
			return Matrix<Type>();

		Matrix rt{this->colCount, this->rowCount};

		for(int i=0; i<minus.rowCount ;++i)
			for(int j=0; j<minus.colCount ;++j)
				rt.set(i, j, this->mainData[i][j] - minus[i][j]);
		return rt;
	}

	Matrix<Type>  operator*(const Matrix<Type>& mutiplied)
	{
		if(this->rowCount != mutiplied.colCount)
			return Matrix<Type>();
	
		Matrix rt{this->colCount, mutiplied.rowCount};

		for(int count=0; count<this->colCount;++count)
			for(int i=0; i<mutiplied.colCount ;++i)
				for(int j=0; j<this->rowCount ;++j)
					rt.set(count, i,  this->mainData[j][count] * mutiplied[i][j]);
		return rt;
	}

//	Matrix<Type>  operator/(const Matrix<Type>& devided)
//	{return (*this)*reciprocal(devided);}
	//A/B = A*(1/B)
	
	Matrix<Type>& operator=(const Matrix<Type>& designated)
	{
		for(int i=0; i<this->rowCount ;++i)
			for(int j=0; j<this->colCount ;++j)
				this->mainData[i][j] = designated[i][j];
		return *this;
	}

	bool 	  	  operator==(const Matrix<Type>& matched)
	{
		if(this->rowCount != matched.rowCount ||
		   this->colCount != matched.colCount)
			return false;
	
		for(int i=0; i<this->rowCount ;++i)
			for(int j=0; j<this->colCount ;++j)
				if(this->mainData[i][j] != matched[i][j])
					return false;
		return true;
	}

	bool		  operator!=(const Matrix<Type>& matched)
	{return !(*this == matched);}

//==================================================================

	void inlineOperate(int lineCount, Type value, operate op)
	{
		switch(op)
		{
			case operate::Add:
				for(int i=0; i<rowCount ;++i)
					this->mainData[i][lineCount] += value;
				break;

			case operate::Minus:
				for(int i=0; i<rowCount ;++i)
					this->mainData[i][lineCount] -= value;
				break;

			case operate::Mutiply:
				for(int i=0; i<rowCount ;++i)
					this->mainData[i][lineCount] *= value;
				break;

			case operate::Divide:
				for(int i=0; i<rowCount ;++i)
					this->mainData[i][lineCount] /= value;
				break;
		
			default:
				return;
		}
	}
	
	//Here
	void lnlOperate(int firstLine, int secondLine, operate op, Type rate = 1)
	{
		switch(op)
		{
			case operate::Add:
				for(int i=0; i<rowCount ;++i)
					this->mainData[i][firstLine] += this->mainData[i][secondLine]*rate;
				break;

			case operate::Minus:
				for(int i=0; i<rowCount ;++i)
					this->mainData[i][firstLine] += (this->mainData[i][secondLine]*rate*-1);
				break;

			case operate::Mutiply:
				for(int i=0; i<rowCount ;++i)
					this->mainData[i][firstLine] *= this->mainData[i][secondLine]*rate;
				break;

			case operate::Divide:
				for(int i=0; i<rowCount ;++i)
					this->mainData[i][firstLine] /= this->mainData[i][secondLine]*rate;
				break;

			default:
				return;
		}
	}

	void pp()
	{
		for(int i=0;i<rowCount;++i)
			for(int j=0;j<colCount;++j)
				cout << i << ',' << j << mainData[j][i] << endl;
	}

	inline int whereFirst(int count)
	{
		for(int i=0; i<=count ;++i)
			if(this->mainData[i][count] != 0)
				return i;	
		return -1;
	}

	void changeLine(int first, int second)
	{
		if(first == second)
			return;

		auto buf = this->mainData[0];

		for(int i=0; i<rowCount ;++i)
			buf[i] = this->mainData[i][first];

		for(int i=0; i<rowCount ;++i)
			this->mainData[i][first] = this->mainData[i][second];

		for(int i=0; i<rowCount ;++i)
			this->mainData[i][second] = buf[i];
	}

	void descend_arrange()
	{
		int lineRef[colCount];

		for(int i=0; i<colCount ;++i)
			lineRef[i] = whereFirst(i);

		arrange(lineRef, colCount);

		for(int i=0; i<colCount ;++i)
			changeLine(i,lineRef[i]);
	}

	void solution()
	{
		for(int i=0; i<colCount ;++i)
		{
			int status{whereFirst(i)};

			if(status == -1 || status >= rowCount)
				return;
			//The status is illogical.			

			inlineOperate(i, 1/this->mainData[status][i], Math::operate::Mutiply);
			//Care the type of int
			for(int j=0; j<colCount ;++j)
			{
				if(!this->mainData[status][j] || i==j)
					continue;
				lnlOperate(j, i, Math::operate::Minus, this->mainData[status][j]);
			}
		}

		descend_arrange();
	}

///////////////////////////////////////////////////////////////////////////////////////////////

	int colCount ,rowCount;

private:
	Type** mainData;
};

};

void merge_recursive(int in[], int reg[], int start, int end)
{

	cout << "start: "<<start << " end: " << end <<endl;

	if(start>=end)
		return;

	int start1{start};
	int start2{((end-start)>>1)+start};
	int end1{((end-start)>>1)+start+1};
	int end2{end};

	if(!(start1 == start2 || end1 == end2))
	{
		merge_recursive(in, reg, start1, end1);
		merge_recursive(in, reg, start2, end2);
	}

	int k{start};
	while(start1 <= end1 && start2 <= end2)
		reg[k++] = in[start1] < in[start2]?in[start1++]:in[start2++];
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

#	endif
