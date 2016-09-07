#include "matrixOP.h"

using namespace Math;

/////////////////////////////////////////////////////////////////////////MatrixOP

template<class Type>
inline int MatrixOP<Type>::whereFirst(int count)
{
	for(int i=0; i<=count ;++i)
		if(this->mainData[i][count] != 0)
			return i;	
	return -1;
}

template<class Type>
void MatrixOP<Type>::changeLine(int first, int second)
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

template<class Type>
void MatrixOP<Type>::descend_arrange()
{
	int lineRef[colCount];

	for(int i=0; i<colCount ;++i)
		lineRef[i] = whereFirst(i);

	arrange(lineRef, colCount);

	for(int i=0; i<colCount ;++i)
		changeLine(i,lineRef[i]);
}

template<class Type>
void MatrixOP<Type>::solution()
{
	for(int i=0; i<colCount ;++i)
	{
		int status{whereFirst(i)};

		if(status == -1 || status >= rowCount)
			return;
		//The status is illogical.			

		inlineOperate(i, 1/this->mainData[status][i], Math::operate::Mutiply);

		for(int j=0; j<colCount ;++j)
		{
			if(!this->mainData[status][j] || i==j)
				continue;
			lnlOperate(j, i, Math::operate::Minus, this->mainData[status][j]);
		}
	}

	descend_arrange();
}

/////////////////////////////////////////////////////////////////////////////////////////////MatrixOP

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
