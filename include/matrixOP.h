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

	~MatrixOP()
	{}

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

	inline int whereFirst(int count);
	void changeLine(int first, int second);
	void descend_arrange();
	void solution();

	Type det();
	MatrixOP inverst();

};

};

void merge_recursive(int in[], int reg[], int start, int end)

void arrange(int in[], int len)

#endif
