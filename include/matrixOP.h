#ifndef MATRIXOP
#define MATRIXOP

#include "matrix.h"
#include <iostream>

namespace Math
{

template<class Type>
class MatrixOP : public Matrix<Type>
{

public:

	MatrixOP(int row,int col) : Matrix<Type>{row, col}
	{}

	MatrixOP(Matrix<Type> init) : Matrix<Type>{init}
	{}

	MatrixOP(std::initializer_list<std::initializer_list<Type>> initList) : Matrix<Type>{initList}
	{}

	~MatrixOP()
	{}

// Operator inheritance

	friend inline std::ostream& operator<<(std::ostream& os, const MatrixOP<Type>& out)
	{
		char chr;
		for(int i=0; i<out.rowCount ;++i)
		{
			os << "[ ";

			for(int j=0; j<out.colCount;++j)
			{
				chr = j == out.colCount-1 ? 0 : ',';
				os << out[i][j] << " " << chr;
			} 
			os << "]\n";
		}	

		return os;
	}


	inline MatrixOP<Type> operator+(const MatrixOP<Type>& added)
	{return Matrix<Type>::operator+(added);}

	inline MatrixOP<Type> operator-(const MatrixOP<Type>& minus)
	{return Matrix<Type>::operator-(minus);}

	inline MatrixOP<Type> operator*(const MatrixOP<Type>& mutiplied)
	{return MatrixOP{Matrix<Type>::operator*(mutiplied)};}

	inline MatrixOP<Type>& operator=(const MatrixOP<Type>& designated)
	{
		Matrix<Type>::operator=(designated);
		return *this;
	}

	inline bool operator==(const MatrixOP<Type>& matched)
	{return Matrix<Type>::operator==(matched);}

	inline bool operator!=(const MatrixOP<Type>& matched)
	{return Matrix<Type>::operator!=(matched);}

	inline Type* operator[](int row) const
	{
		if(row >=Matrix<Type>::rowCount)	
			return nullptr;
		return this->mainData[row];
	}

//--

// Line operate

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
					this->mainData[firstLine][i] = (this->mainData[secondLine][i]*rate) + this->mainData[firstLine][i];
					break;

				case operate::Minus:
					for(int i=0; i< Matrix<Type>::rowCount ;++i)
						this->mainData[firstLine][i] = (this->mainData[secondLine][i]*rate*-1) + this->mainData[firstLine][i];
					break;

				case operate::Mutiply:
					for(int i=0; i< Matrix<Type>::rowCount ;++i)
						this->mainData[firstLine][i] = (this->mainData[secondLine][i]*rate) * this->mainData[firstLine][i];
					break;

				case operate::Divide:
					for(int i=0; i< Matrix<Type>::rowCount ;++i)
						this->mainData[firstLine][i] = (this->mainData[secondLine][i]*rate) / this->mainData[firstLine][i];
					break;

				default:
					return;
			}
	}

	inline int whereFirst(int count)
	{
		for(int i=0; i<=Matrix<Type>::colCount ;++i)
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

	inline void descend_arrange(bool recordFlag, MatrixOP<Type>& recordOne)
	{
		int lineRef[Matrix<Type>::rowCount];

		for(int i=0; i<Matrix<Type>::colCount ;++i)
			lineRef[i] = whereFirst(i);

		arrange(lineRef, Matrix<Type>::colCount);

		for(int i=0; i<Matrix<Type>::colCount ;++i)
		{
			changeLine(i,lineRef[i]);
			if(recordFlag)
				recordOne.changeLine(i,lineRef[i]);
		}
	}

	inline void descend_arrange()
	{
		int lineRef[Matrix<Type>::rowCount];

		for(int i=0; i<Matrix<Type>::colCount ;++i)
			lineRef[i] = whereFirst(i);

		arrange(lineRef, Matrix<Type>::colCount);

		for(int i=0; i<Matrix<Type>::colCount ;++i)
			changeLine(i,lineRef[i]);
	}


//--
	MatrixOP<Type> solution()
	{

		MatrixOP<Type> rt{*this};
		int status{rt.whereFirst(0)};

		for(int i=0; i<Matrix<Type>::rowCount ;++i)
		{
			
			status = rt.whereFirst(i);

			if(status == -1 || status >= Matrix<Type>::colCount)
				return MatrixOP<Type>{0,0};
			//The status is illogical.

			rt.inlineOperate(i, 1/rt[i][status], Math::operate::Mutiply);

			for(int j=0; j<Matrix<Type>::rowCount ;++j)
			{

				if(rt[j][status] == 0 || i==j)
					continue;
				rt.lnlOperate(j, i, Math::operate::Minus, rt[j][status]);

			}

		}

		rt.descend_arrange();

		return rt;
	}

	MatrixOP<Type> inverse()
	{
	
		if(Matrix<Type>::rowCount != Matrix<Type>::colCount)
			return MatrixOP<Type>{0,0};
	
		MatrixOP<Type> rt{Matrix<Type>::rowCount, Matrix<Type>::colCount};
		MatrixOP<Type> solutionOne{*this};

		for(int i=0; i<Matrix<Type>::rowCount ;++i)
			rt[i][i] = 1;	

		int status{solutionOne.whereFirst(0)};

		for(int i=0; i<Matrix<Type>::rowCount ;++i)
		{
			
			status = solutionOne.whereFirst(i);

			if(status == -1 || status >= Matrix<Type>::colCount)
				return MatrixOP<Type>{0,0};
			//The status is illogical.

			rt.inlineOperate(i, 1/solutionOne[i][status], Math::operate::Mutiply);
			solutionOne.inlineOperate(i, 1/solutionOne[i][status], Math::operate::Mutiply);


			for(int j=0; j<Matrix<Type>::rowCount ;++j)
			{

				if(solutionOne[j][status] == 0 || i==j)
					continue;
				rt.lnlOperate(j, i, Math::operate::Minus, solutionOne[j][status]);
				solutionOne.lnlOperate(j, i, Math::operate::Minus, solutionOne[j][status]);

			}

		}

		solutionOne.descend_arrange(true, rt);

		return rt;


	}

	Type det();
};

};

void merge_recursive(int in[], int reg[], int start, int end);

void arrange(int in[], int len);

#endif
