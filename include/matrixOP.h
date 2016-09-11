#ifndef MATRIXOP
#define MATRIXOP

#include "matrix.h"

namespace Math
{

template<class Type>
class MatrixOP : public Matrix<Type>
{

public:

	MatrixOP(int row,int col) : Matrix<Type>{row, col}
	{}

	MatrixOP(std::initializer_list<std::initializer_list<Type>> initList) : Matrix<Type>{initList}
	{}

	~MatrixOP()
	{}

	void inlineOperate(int lineCount, Type value, operate op)
	{
		switch(op)
		{
			case operate::Add:
				for(int i=0; i< Matrix<Type>::rowCount ;++i)
					this->mainData[lineCount][i] += value;
				break;

			case operate::Minus:
				for(int i=0; i< Matrix<Type>::rowCount ;++i)
					this->mainData[lineCount][i] -= value;
				break;

			case operate::Mutiply:
				for(int i=0; i< Matrix<Type>::rowCount ;++i)
					this->mainData[lineCount][i] *= value;
				break;

			case operate::Divide:
				for(int i=0; i< Matrix<Type>::rowCount ;++i)
					this->mainData[lineCount][i] /= value;
				break;
		
			default:
				return;
		}
	}
	
	void lnlOperate(int firstLine, int secondLine, operate op, Type rate = 1)
	{
		switch(op)
		{
			case operate::Add:
				for(int i=0; i< Matrix<Type>::rowCount ;++i)
					this->mainData[firstLine][i] += this->mainData[secondLine][i]*rate;
				break;

			case operate::Minus:
				for(int i=0; i< Matrix<Type>::rowCount ;++i)
					this->mainData[firstLine][i] += (this->mainData[secondLine][i]*rate*-1);
				break;

			case operate::Mutiply:
				for(int i=0; i< Matrix<Type>::rowCount ;++i)
					this->mainData[firstLine][i] *= this->mainData[secondLine][i]*rate;
				break;

			case operate::Divide:
				for(int i=0; i< Matrix<Type>::rowCount ;++i)
					this->mainData[firstLine][i] /= this->mainData[secondLine][i]*rate;
				break;

			default:
				return;
		}
	}


	inline int whereFirst(int count)
	{
		for(int i=0; i<=colCount ;++i)
			if(this->mainData[count][i] != 0)
				return i;	
		return -1;
	}

	void changeLine(int first, int second)
	{
		if(first == second)
			return;

		auto buf = this->mainData[0];

		for(int i=0; i<Matrix<Type>::colCount ;++i)
			buf[i] = this->mainData[first][i];

		for(int i=0; i<Matrix<Type>::colCount ;++i)
			this->mainData[first][i] = this->mainData[second][i];

		for(int i=0; i<Matrix<Type>::colCount ;++i)
			this->mainData[second][i] = buf[i];
	}

	void descend_arrange()
	{
		int lineRef[Matrix<Type>::rowCount];

		for(int i=0; i<Matrix<Type>::colCount ;++i)
			lineRef[i] = whereFirst(i);

		arrange(lineRef, Matrix<Type>::colCount);

		for(int i=0; i<Matrix<Type>::colCount ;++i)
			changeLine(i,lineRef[i]);
	}

	void solution()
	{
		for(int i=0; i<Matrix<Type>::colCount ;++i)
		{
			int status{whereFirst(i)};

			if(status == -1 || status >= Matrix<Type>::rowCount)
				return;
			//The status is illogical.			

			inlineOperate(i, 1/this->mainData[status][i], Math::operate::Mutiply);

			for(int j=0; j<Matrix<Type>::colCount ;++j)
			{
				if(!this->mainData[status][j] || i==j)
					continue;
				lnlOperate(j, i, Math::operate::Minus, this->mainData[status][j]);
			}
		}

		descend_arrange();
	}

	Type det();
	MatrixOP inverst();

};

};

void merge_recursive(int in[], int reg[], int start, int end);

void arrange(int in[], int len);

#endif
