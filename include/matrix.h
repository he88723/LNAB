#ifndef Matrix_H
#define Matrix_H

#include <initializer_list>

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
			mainData = new Type*[rowCount];

			for(int i=0; i<rowCount ;++i)
			{
				mainData[i] = new Type[colCount];
		
				for(int j=0; j<colCount ;++j)
					mainData[i][j] = 0;

			}
		}
		else
			mainData = nullptr;
		
	}

	Matrix(const Matrix<Type>& matrix) : rowCount{matrix.rowCount} , colCount{matrix.colCount}
	{
	
		mainData = new Type*[rowCount];

		for(int i=0; i<rowCount ;++i)
		{
		
			mainData[i] = new Type[colCount];

			for(int j=0; j<colCount ;++j)
				mainData[i][j] = matrix.mainData[i][j];
		
		}
	
	}

	Matrix(std::initializer_list<std::initializer_list<Type>> initList)
	   	: rowCount{(Type)initList.size()} , colCount{(Type)(*initList.begin() ).size()}
	{
		mainData = new Type*[rowCount];

		for(int i=0; i<rowCount ;++i)
		{
			mainData[i] = new Type[colCount];

			for(int j=0; j<colCount ;++j)
				mainData[i][j] = *(((initList.begin()+i)->begin()) + j);
		}
	
	}

	~Matrix()
	{
	
		for	(int i=0; i<rowCount ;++i)
			delete mainData[i];
		
		delete mainData;
	}

	bool is_same_size(const Matrix<Type>& matched)
	{

		if(this->colCount != matched.colCount)
			return false;
		else if(this->rowCount != matched.rowCount)
			return false;
		
		return true;

	}

//Operator For Matrix======================================================

	int* operator[](int row)
	{return this->mainData[row];}

	Matrix<Type> operator+(const Matrix<Type>& added)
	{
		if(is_same_size(added))
			return Matrix();

		Matrix rt{this->colCount, this->rowCount};

		for(int i=0; i<added.rowCount ;++i)
			for(int j=0; j<added.colCount ;++j)
				rt.mainData[i][j] = this->mainData[i][j] + added.mainData[i][j];
		return rt;
	}

	Matrix<Type>  operator-(const Matrix<Type>& minus)
	{
		if(is_same_size(minus))
			return Matrix();

		Matrix rt{this->colCount, this->rowCount};

		for(int i=0; i<minus.rowCount ;++i)
			for(int j=0; j<minus.colCount ;++j)
				rt.mainData[i][j] = this->mainData[i][j] - minus.mainData[i][j];
		return rt;
	}

	Matrix<Type>  operator*(const Matrix<Type>& mutiplied)
	{
		if(this->rowCount != mutiplied.colCount)
			return Matrix();
	
		Matrix rt{this->colCount, mutiplied.rowCount};

		int count{0};

		for(int count; count<this->colCount;)
			for(int i=0; i<mutiplied.colCount ;++i)
				for(int j=0; j<this->rowCount ;++j)
					rt.mainData[count][i] += this->mainData[j][count] * mutiplied.mainData[i][j];
		return rt;
	}

//	Matrix<Type>  operator/(const Matrix<Type>& devided)
//	{return (*this)*reciprocal(devided);}
	//A/B = A*(1/B)
	
	Matrix<Type>& operator=(const Matrix<Type>& designated)
	{
		for(int i=0; i<this->rowCount ;++i)
			for(int j=0; j<this->colCount ;++j)
				designated.mainData[i][j] = *this[i][j];
		return *this;
	}

	bool  	operator==(const Matrix<Type>& matched)
	{
		if(this->rowCount != matched.rowCount ||
		   this->colCount != matched.colCount)
			return false;
	
		for(int i=0; i<this->rowCount ;++i)
			for(int j=0; j<this->colCount ;++j)
				if(this->mainData[i][j] != matched.mainData[i][j])
					return false;
		return true;
	}

	bool	operator!=(const Matrix<Type>& matched)
	{return !(*this == matched);}

//==================================================================

	void inlineOperate(int lineCount, Type value, operate op)
	{
		switch(op)
		{
			case operate::Add:
				for(int i=0; i<rowCount ;++i)
					mainData[i][lineCount] += value;
				break;

			case operate::Minus:
				for(int i=0; i<rowCount ;++i)
					mainData[i][lineCount] -= value;
				break;

			case operate::Mutiply:
				for(int i=0; i<rowCount ;++i)
					mainData[i][lineCount] *= value;
				break;

			case operate::Divide:
				for(int i=0; i<rowCount ;++i)
					mainData[i][lineCount] /= value;
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
					mainData[i][firstLine] += mainData[i][secondLine]*rate;
				break;

			case operate::Minus:
				for(int i=0; i<rowCount ;++i)
					mainData[i][firstLine] -= mainData[i][secondLine]*rate;
				break;

			case operate::Mutiply:
				for(int i=0; i<rowCount ;++i)
					mainData[i][firstLine] *= mainData[i][secondLine]*rate;
				break;

			case operate::Divide:
				for(int i=0; i<rowCount ;++i)
					mainData[i][firstLine] += mainData[i][secondLine]*rate;
				break;

			default:
				return;
		}
	}

	int  whereFirst(int count)
	{
		for(int i=0; i<count ;++i)
			if(this -> mainData[i][count])
				return i;	
		return -1;
	}

	void changeLine(int first, int second)
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

		descend_arrange();
	}

///////////////////////////////////////////////////////////////////////////////////////////////

	int colCount ,rowCount;
	Type** mainData;
};

};

#endif
