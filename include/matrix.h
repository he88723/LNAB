#ifndef Matrix_H
#define Matrix_H

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

	Matrix(const Matrix& matrix) : rowCount{matrix.rowCount} , colCount{matrix.colCount}
	{
	
		mainData = new Type*[rowCount];

		for(int i=0; i<rowCount ;++i)
		{
		
			mainData[i] = new Type[colCount];

			for(int j=0; j<colCount ;++j)
				mainData[i][j] = matrix[i][j];
		
		}
	
	}

	~Matrix()
	{
	
		for	(int i=0; i<rowCount ;++i)
			delete mainData[i];
		
		delete mainData;
	}

	bool is_same_size(const Matrix& matched)
	{

		if(this->colCount != matched.colCount)
			return false;
		else if(this->rowCount != matched.rowCount)
			return false;
		
		return true;

	}

	int* operator[](int row)
	{return mainData[row];}

	Matrix  operator+(const Matrix&);
	Matrix  operator-(const Matrix&);	
	Matrix  operator*(const Matrix&);
	Matrix  operator/(const Matrix& devided)
	{return (*this)*reciprocal(devided);}
	//A/B = A*(1/B)
	
	Matrix& operator=(Matrix&);

	bool  	operator==(const Matrix&);
	bool	operator!=(const Matrix& matched)
	{return !(*this == matched);}

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

	int  whereFirst(int count);

	void changeLine(int first, int second);

	void solution();

//	void reciprocal();

	void descend_arrange();

///////////////////////////////////////////////////////////////////////////////////////////////

	int colCount ,rowCount;

private:
	Type** mainData;
};

};

#endif
