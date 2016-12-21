# LNAB

[![License](https://img.shields.io/badge/license-MIT-red.svg)](LICENSE)<br/>
LNAB is a linear algebra framework which focus on the matrix and vector operate. 
It is speedy , easy to express and modularity.
There are many functions in the class `MatrixOP` like to add, minus, multiply, divide ,inverse and Gaussian Elimination.
There are not only just these functions, but also more and more linear algebra functions will be added in the future.

## Basis of Class `Matrix` and Class `MatrixOP`

There are two classes in LNAB. 
They are `Matrix` and `MatrixOP`, respectively. 
You may have a question to that why the matrix was divided into two different classes.
`Matrix` one contain added, minus, multiply and divide operation.
`MatrixOP` one also contains them. In addition, it contains inverse, Elimination and line operation… 
This is because that someone may just use basic operation of the matrix.

#### Declare `Matrix` `MatrixOP`

If you want to declare a m×n matrix by `Matrix` and `MatrixOP`, you can write that like the following.<br/>

*Notice: These two classes of `Matrix` and `MatrixOP` have same way to construct. So I only write the way to construct of `Matrix`.*
```C++
using namespace Math;
//They all declare at Math namespace.

template<class type>
//The type you want.

Matrix<type>   matrix_declare{m,n};
//The m and n is int type.
```

And then you also can use the data set, the 2d array, the other `Matrix` or `MatrixOP` class to construct it. 
See the following.

```C++
Matrix<type>   matrix_data{{1,0,0},{0,1,0},{0,0,1}};
//Notice the type you have given.
//It look like this.|1 0 0|
//                  |0 1 0|
//                  |0 0 1|

Matrix<type>   matrix_2d{array, arrayx, arrayY};
//The array is defined as the following.
//type array[arrayx][arrayY];

Matrix<type> matrix_om{otherMatrix};
//The otherMatrix must have the same type with matrix_om.
```
As described above, you have known that how to declare a `Matrix` or `MatrixOP`. 
Next, we will discuss the operator of them and some functions there.

#### Apply `Matrix` `MatrixOP`

After you have declared a `Matrix` or a `MatrixOP`, what can you do with them? 

##### Operator
Let's us see their operator. <br/> 
They have such operators `+ - * / = == != ()`. 
Afterward, you must want to know how to use them. 
See the following.

*Notice: These two classes of `Matrix` and `MatrixOP` have same way to use operator. So I only write one way(`Matrix`) to express.*
```C++
Matrix<type> m1{{1,0},{2,3}};
Matrix<type> m2{{3,4},{8,7}};

Matrix<type> m3{};
//empty matrix

type val = m1(0,0);
//It will give you the value at the position(0,0).
//val = 1

m3 = m1 + m2;
//Rewrite m3 as {{4,4},{10,10}}
m3 = m1 + 1;
//Rewrite m3 as m1 added 1, {{2,1},{3,4}}

m3 = m1 - m2;
//Rewrite m3 as {{-2,-4},{-6,-4}}
m3 = m1 - 2;
//Rewrite m3 as m1 minused 2, {{-1,-2},{0,1}}

m3 = m1 * m2;
//Rewrite m3 as {{3,0},{16,21}}
m3 = m1 * 3;
//Rewrite m3 as m1 multiplied 3, {{3,0},{6,9}}

m3 = m1 / m2;
//Note: If the classes m1 and m2 are Matrix , the element of m1 will just divide by the element of m2.
//Note: If the classes m1 and m2 are MatrixOP, the m2 will inverse() first and then multiply with m1.

bool t = m1 == m2;
//It will compare every element in class Matrix or MatrixOP.
//Then the t will be false.

bool t = m1 != m2;
//It's just as above. The t will be true.
```
And there are some points you need to know. <br/>

+ The parameters must be the same type with class `Matrix` or class `MatrixOP` here.
+ In operator `+ - * /`, the constant value can put above in the `MatrixOP`.
+ In operator `*`, the size of classes `Matrix` and `MatrixOP` has to match.
+ If you don't match the class `Matrix`, it will return an empty `Matrix` and won't notice you.
+ Also, if you don't match the class `MatrixOP`, it will terminate and show the error message.

##### Functions

See the function of `Matrix`.
```C++
bool set(int row, int col, Type val);
bool is_same_size(const Matrix<Type>& matched);
```
The `set(int,int,Type)` function will set the element of the position(`row`,`col`) by `val`.
If the input is in range, it will return true.<br>
The `is_same_size(Matrix<Type>)` function will compare the size. If they are matched, it will return true.<br/>

See the function of `MatrixOP`.

```C++
void changeLine(int first, int second);
void inline_operate(int line, Type value, operate op);
void lines_operate(int fLine, int sLine, operate op, Type rate = 1);
```
The `changeLine(int ,int)` swap two rows in `MatrixOP` by the `first` and `second`.<br/>
The `inline_operate(int, Type, operate)` make the element of `line` row calculate with `value` by `operate` meaning.<br/>
The `operate` is an enum be defined as the following.
```C++
enum operate{Add, Minus, Mutiply, Divide};
```
The `lines_operatr(int, int, operate, Type)` make `fLine` row calculate with `sLine` row by `operate` meaning.
Notice, the element of `sLine` row will be multiplied by `rate`.<br/>

```C++
inline Type sum();
void rndSet(Type up, Type down);
MatrixOP<Type> sub(const Point& pointA, const Point& pointB);
MatrixOP<Type> sub_by_point(const Point Epoint);
```
The `sum()` will return a value of the sum of all elements in `MatrixOP`.<br/>
The `rndSet(Type, Type)` will set the elements of `MatrixOP` to a random value between `up` and `down`.<br/>
The `sub(Point, Point)` will cut the `MatrixOP` from `PointA` to `PointB`. <br/>
The `sub_by_point(Point)` will cut the `MatrixOP` by `Epoint`.<br/>
See the following code to understand more exhaustive.
```C++
MatrixOP<int> cuted{{1,2,3},{4,5,6},{7,8,9}};
MatrixOP<int> sub{};

Point p1{0,0};
//Top right
Point p2{1,1};
//Center

sub = cuted.sub(p1, p2);
//The `sub` will be reviced as {{1,2},{4,5}}.
sub = cuted.sub_by_point(p2);
//The `sub will be reviced as {{1,3},{7,9}}.
```

```C++
MatrixOP<Type> transpose();
MatrixOP<Type> Gauss_solution();
MatrixOP<Type> inverse();
Type det();
```

They will work like their name. 
Expect `det()`, all of them will return class `MatrixOP`. 
And then, the `det()` will return the value of `type` type. 
It's just that easy, so we don't write the code to show you how to implement. <br/><br/>

Now you have already learned how to use them. 
If you want to see some program with LNAB, you can go to there:<br/>
https://github.com/he88723/Machine_Learning <br/>

There are some code written with LNAB.

# Contributing
1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: ` git push origin my-new-feature`
5. Submit a pull request :D
