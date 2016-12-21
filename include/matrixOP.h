#ifndef MATRIXOP
#define MATRIXOP

#include "matrix.h"
#include <iostream>
#include <stdlib.h>
#include <random>
#include <ctime>

namespace Math
{

struct Point{
	int x;
	int y;
};

template<class Type>
class MatrixOP : public Matrix<Type>
{

public:

	MatrixOP(int row,int col) : Matrix<Type>{row, col}
	{}

	MatrixOP(const Matrix<Type>& init) : Matrix<Type>{init}
	{}

	MatrixOP(std::initializer_list<std::initializer_list<Type>> initList) : Matrix<Type>{initList}
	{}

	~MatrixOP()
	{}

// Operator inheritance==========================================================

	friend inline std::ostream& operator<<(std::ostream& os, const MatrixOP<Type>& out)
	{
		char chr;
		for(int i=0; i<out.rowCount ;++i)
		{
			os << "[ ";

			for(int j=0; j<out.colCount;++j)
			{
				chr = j == out.colCount-1 ? 0:',';
				os << out(i,j) << ' ' << chr;
			}

			os << "]\n";
		}

		return os;
	}


	inline MatrixOP<Type> operator+(const MatrixOP<Type>& added)
	{return MatrixOP{Matrix<Type>::operator+(added)};}
	inline MatrixOP<Type> operator+(const Type& opVal)
	{return MatrixOP{Matrix<Type>::operator+(opVal)};}

	inline MatrixOP<Type> operator-(const MatrixOP<Type>& minus)
	{return MatrixOP{Matrix<Type>::operator-(minus)};}
	inline MatrixOP<Type> operator-(const Type& opVal)
	{return MatrixOP{Matrix<Type>::operator-(opVal)};}

	inline MatrixOP<Type> operator*(const MatrixOP<Type>& mutiplied)
	{
		if(Matrix<Type>::colCount != mutiplied.rowCount)
		{
				std::cerr << "\033[1;31mWarning\033[0m:: the MatrixOP size are not aligned :" <<
				" (" << Matrix<Type>::rowCount << ',' << Matrix<Type>::colCount << ") (" <<
				mutiplied.rowCount << ',' << mutiplied.colCount << ")\n";

			exit(-1);
		}

		return MatrixOP{Matrix<Type>::operator*(mutiplied)};
	}
	inline MatrixOP<Type> operator*(const Type& opVal)
	{return MatrixOP{Matrix<Type>::operator*(opVal)};}

	inline MatrixOP<Type> operator/(const MatrixOP<Type>& divided)
	{
		if(Matrix<Type>::colCount != divided.rowCount)
		{
				std::cerr << "\033[1;31mWarning\033[0m:: the MatrixOP size are not aligned :" <<
				" (" << Matrix<Type>::rowCount << ',' << Matrix<Type>::colCount << ") (" <<
				divided.rowCount << ',' << divided.colCount << ")\n";

			exit(-1);
		}

		return *this * divided.inverse();
	}
	inline MatrixOP<Type> operator/(const Type& opVal)
	{return MatrixOP{Matrix<Type>::operator/(opVal)};}

	inline MatrixOP<Type>& operator=(const MatrixOP<Type>& designated)
	{
		Matrix<Type>::operator=(designated);
		return *this;
	}

	inline bool operator==(const MatrixOP<Type>& matched)
	{return Matrix<Type>::operator==(matched);}

	inline bool operator!=(const MatrixOP<Type>& matched)
	{return Matrix<Type>::operator!=(matched);}

	inline Type operator()(int row, int col) const
	{
		return Matrix<Type>::operator()(row, col);
	}

	void showShape()
	{
		std::cout << Matrix<Type>::rowCount << " : " << Matrix<Type>::colCount << '\n';
	}

//===============================================================================


// Line operate==================================================================

	void inline_operate(int lineCount, Type value, operate op)//inline_operate
	{
		int basic{lineCount*Matrix<Type>::colCount};

		switch(op)
		{
			case operate::Add:
				for(int i=0; i< Matrix<Type>::rowCount ;++i)
					this->mainData[basic + i] += value;
				break;

			case operate::Minus:
				for(int i=0; i< Matrix<Type>::rowCount ;++i)
					this->mainData[basic + i] -= value;
				break;

			case operate::Mutiply:
				for(int i=0; i< Matrix<Type>::rowCount ;++i)
					this->mainData[basic + i] *= value;
				break;

			case operate::Divide:
				for(int i=0; i< Matrix<Type>::rowCount ;++i)
					this->mainData[basic + i] /= value;
				break;
	
			default:
				return;
		}
	}

	void lines_operate(int firstLine, int secondLine, operate op, Type rate = 1)//lines_operate
	{
		int basic{firstLine*Matrix<Type>::colCount};

		switch(op)
		{
			case operate::Add:
				for(int i=0; i< Matrix<Type>::colCount ;++i)
					this->mainData[basic + i] += (*this)(secondLine, i)*rate;
				break;

			case operate::Minus:
				for(int i=0; i< Matrix<Type>::colCount ;++i)
					this->mainData[basic + i] = (*this)(firstLine, i) - (*this)(secondLine, i)*rate;
				break;

			case operate::Mutiply:
				for(int i=0; i< Matrix<Type>::colCount ;++i)
					this->mainData[basic + i] *= (*this)(secondLine, i)*rate;
				break;

			case operate::Divide:
				for(int i=0; i< Matrix<Type>::colCount ;++i)
					this->mainData[basic + i] = (*this)(firstLine, i) / ((*this)(secondLine, i)*rate);
				break;

			default:
				return;
		}
	}

//=======================================================================================

	void rndSet(Type up, Type down)
	{
		std::uniform_real_distribution<Type> unif(down, up);
		std::default_random_engine rnd(time(0));
		int basic{0};

		for(int i=0; i<Matrix<Type>::rowCount ;++i)
		{
			for(int j=0; j<Matrix<Type>::colCount ;++j)
				this->mainData[basic + j] = unif(rnd);
			basic += Matrix<Type>::colCount;
		}
	}

	inline Type sum()
	{
		Type rt{0};

		for(int i=0; i<Matrix<Type>::rowCount ;++i)
			for(int j=0; j<Matrix<Type>::colCount ;++j)
				rt += (*this)(i, j);

		return rt;
	}

	inline bool set(int row, int col, Type val)
	{return Matrix<Type>::set(row, col, val);}

	inline int pivot_Pos(int count)		//Get pivot position
	{
		for(int i=0; i<=Matrix<Type>::colCount ;++i)
			if( (*this)(count ,i) != 0)
				return i;	
		return -1;
	}

	MatrixOP<Type> sub(const Point& pointA, const Point& pointB) //need test
	{
		MatrixOP<Type> rt{abs(pointA.x-pointB.x)+1, abs(pointA.y-pointB.y)+1};

		Point refPoint{(pointA.x>=pointB.x?pointB.x:pointA.x),
					   (pointA.y>=pointB.y?pointB.y:pointA.y)};

		for(int i=0; i<rt.rowCount ;++i)
			for(int j=0; j<rt.colCount ;++j)
				rt.set(i, j, (*this)(refPoint.x + i, refPoint.y + j) );

		return rt;
	}

	MatrixOP<Type> sub_by_point(const Point Epoint) //need test
	{
		MatrixOP<Type> rt{Matrix<Type>::rowCount-1, Matrix<Type>::colCount-1};

		for(int i=0; i<Matrix<Type>::rowCount ;++i)
			for(int j=0; j<Matrix<Type>::colCount ;++j)
				if(i !=	Epoint.x && j != Epoint.y && i > 0 && j > 0)
					rt.set(i-1, j-1, (*this)(i, j));
		
		return rt;
	}

	MatrixOP<Type> transpose()
	{

		MatrixOP<Type> rt{Matrix<Type>::colCount, Matrix<Type>::rowCount};

		bool status = Matrix<Type>::rowCount > Matrix<Type>::colCount;

		if(status)
		{
			for(int i=0; i<Matrix<Type>::colCount ;++i)
				for(int j=0; j<Matrix<Type>::rowCount ;++j)
					rt.set(i, j, (*this)(j, i));
		}
		else
		{
			for(int i=0; i<Matrix<Type>::rowCount ;++i)
				for(int j=0; j<Matrix<Type>::colCount ;++j)
					rt.set(j, i, (*this)(i, j));
		}
		
		return rt;	
	}

//====================================================================================

	void changeLine(int first, int second)
	{
		if(first == second)
			return;

		auto buf = new Type[Matrix<Type>::colCount];
		int basic{first * Matrix<Type>::colCount};

		for(int i=0; i<Matrix<Type>::colCount ;++i)
			buf[i] = (*this)(first, i);

		for(int i=0; i<Matrix<Type>::colCount ;++i)
			this->mainData[basic + i] = (*this)(second, i);

		basic = second * Matrix<Type>::colCount;
		for(int i=0; i<Matrix<Type>::colCount ;++i)
			this->mainData[basic + i] = buf[i];
	}

	inline void descend_arrange(MatrixOP<Type>& recordOne)
	{
		int lineRef[Matrix<Type>::rowCount];

		for(int i=0; i<Matrix<Type>::colCount ;++i)
			lineRef[i] = pivot_Pos(i);

		arrange(lineRef, Matrix<Type>::colCount);

		for(int i=0; i<Matrix<Type>::colCount ;++i)
		{
			changeLine(i,lineRef[i]);
			recordOne.changeLine(i,lineRef[i]);
		}
	}

	inline void descend_arrange()
	{
		int lineRef[Matrix<Type>::rowCount];

		for(int i=0; i<Matrix<Type>::colCount ;++i)
			lineRef[i] = pivot_Pos(i);

		arrange(lineRef, Matrix<Type>::colCount);

		for(int i=0; i<Matrix<Type>::colCount ;++i)
			changeLine(i,lineRef[i]);
	}

	MatrixOP<Type> Gauss_solution()
	{
		MatrixOP<Type> rt{*this};
		int status{0};

		for(int i=0; i<Matrix<Type>::rowCount ;++i)
		{
			status = rt.pivot_Pos(i);

			if(status == -1 || status >= Matrix<Type>::colCount)
				return MatrixOP<Type>{0,0};
			//The status is illogical.

				rt.inline_operate(i, 1/rt(i, status), Math::operate::Mutiply);

			for(int j=0; j<Matrix<Type>::rowCount ;++j)
			{
				if(rt(j, status) == 0 || i==j)
					continue;
				rt.lines_operate(j, i, Math::operate::Minus, rt(j, status));
			}
		}

		rt.descend_arrange();

		return rt;
	}

	MatrixOP<Type> inverse()
	{
		if(Matrix<Type>::rowCount != Matrix<Type>::colCount)
			return MatrixOP<Type>{0,0};
		//If the matrix isn't a square matrix, the function will return a empty matrix.
	
		MatrixOP<Type> rt{Matrix<Type>::rowCount, Matrix<Type>::colCount};
		MatrixOP<Type> solutionOne{*this};
		//Use the Gauss solution to get inverse.
		//Right part is rt, a identity matrix.
		//Left part is solutionOne, a source matrix.

		for(int i=0; i<Matrix<Type>::rowCount ;++i)
			rt.set(i, i, 1);
		//Set the rt to a identity matrix.

		int status{0};

		for(int i=0; i<Matrix<Type>::rowCount ;++i)
		{
			status = solutionOne.pivot_Pos(i);

			if(status == -1 || status >= Matrix<Type>::colCount)
				return MatrixOP<Type>{0,0};
			//The status is illogical.

			rt.inline_operate(i, 1/solutionOne(i, status), Math::operate::Mutiply);
			solutionOne.inline_operate(i, 1/solutionOne(i, status), Math::operate::Mutiply);

			for(int j=0; j<Matrix<Type>::rowCount ;++j)
			{
				if(solutionOne(j, status) == 0 || i==j)
					continue;
				rt.lines_operate(j, i, Math::operate::Minus, solutionOne(j, status));
				solutionOne.lines_operate(j, i, Math::operate::Minus, solutionOne(j, status));
			}
		}

		solutionOne.descend_arrange(rt);

		return rt;
	}

	Type det()
	{
		if(Matrix<Type>::rowCount != Matrix<Type>::colCount)
			return 0;

		if(Matrix<Type>::rowCount == 2)
			return ( (*this)(0,0) * (*this)(1,1) ) -
				   ( (*this)(0,1) * (*this)(1,0) );

		Type rt{0};

		Type postive{1};

		for(int i=0; i<Matrix<Type>::rowCount ;++i)
		{
			rt += postive * sub_by_point(Point{0,i}).det();
			postive *= -1;
		}
		//It reduces dimensionality until the matrix be a 2*2 matrix.

		return rt;
	}

	inline MatrixOP<Type> dot_product(const MatrixOP<Type>& mutiplied)
	{
		if(is_same_size(mutiplied))
		{
			std::cerr << "\033[1;31mWarning\033[0m:: the MatrixOP size are not aligned in dot product :" <<
			" (" << Matrix<Type>::rowCount << ',' << Matrix<Type>::colCount << ") (" <<
			mutiplied.rowCount << ',' << mutiplied.colCount << ")\n";

			exit(-1);
		}

		MatrixOP<Type> rt{mutiplied};

		int basic{0};
		for(int i=0; i<rt.rowCount ;++i)
		{
			basic = i*Matrix<Type>::colCount;
			for(int j=0; j<rt.colCount ;++j)
				rt.set(i, j, rt(i, j) * this->mainData[basic + j]);
		}
		
		return rt;
	}	

	void setAll(Type func(Type))
	{
		int basic{0};

		for(int i=0; i<Matrix<Type>::rowCount ;++i)
		{
			basic = i*Matrix<Type>::colCount;
			for(int j=0; j<Matrix<Type>::colCount ;++j)
				this->mainData[basic + j] = func(this->mainData[basic+j]);
		}
	}

	inline void zero()
	{
		for(int i=0; i<Matrix<Type>::rowCount ;++i)
			for(int j=0; j<Matrix<Type>::colCount ;++j)
				set(i, j, 0);
	}

};

template<class maType, class Type>
MatrixOP<maType> operator+(const Type& val, const MatrixOP<maType> ma)
{
	MatrixOP<maType> rt{ma};

	for(int i=0; i<rt.rowCount ;++i)
		for(int j=0; j<rt.colCount ;++j)
			rt.set(i, j, rt(i,j) + static_cast<maType>(val));

	return rt;
}

template<class maType, class Type>
MatrixOP<maType> operator-(const Type& val, const MatrixOP<maType> ma)
{
	MatrixOP<maType> rt{ma};

	for(int i=0; i<rt.rowCount ;++i)
		for(int j=0; j<rt.colCount ;++j)
			rt.set(i, j, static_cast<maType>(val) - rt(i,j));

	return rt;
}

template<class maType, class Type>
MatrixOP<maType> operator*(const Type& val, const MatrixOP<maType> ma)
{
	MatrixOP<maType> rt{ma};

	for(int i=0; i<rt.rowCount ;++i)
		for(int j=0; j<rt.colCount ;++j)
			rt.set(i, j, rt(i,j) * static_cast<maType>(val));

	return rt;
}

template<class maType, class Type>
MatrixOP<maType> operator/(const Type& val, const MatrixOP<maType> ma)
{
	MatrixOP<maType> rt{ma};

	for(int i=0; i<rt.rowCount ;++i)
		for(int j=0; j<rt.colCount ;++j)
			rt.set(i, j, static_cast<maType>(val) / rt(i,j));

	return rt;
}

//Add operator for former const val

};


//Out function provide for MatrixOP function
void merge_recursive(int in[], int reg[], int start, int end);

void arrange(int in[], int len);

inline int abs(int in)
{return in<0?-in:in;}


#endif
