#include "Matrix.h"

void matrixTest1()
{
	Matrix m(2, 2);
	m.assign(0, 0, 1);
	m.assign(0, 1, 2);
	m.assign(1, 0, 3);
	m.assign(1, 1, 4);

	cout << "Matrix m equals: " << endl;
	cout << m << endl;

	Matrix n(2, 2);
	n.assign(0, 0, 2);
	n.assign(0, 1, 3);
	n.assign(1, 0, 4);
	n.assign(1, 1, 6);

	cout << "Matrix n equals:" << endl;
	cout << n << endl;

	Matrix o(2, 2);
	o = m + n;

	cout << "Matrix O, the sum of matrices M and N, is: " << endl;
	cout << o << endl;

	Matrix p(2, 2);
	p = m - n;

	cout << "Matrix M - Matrix N is: " << endl;
	cout << p << endl;

	cout << "The trace of Matrix O is " << trace(o) << endl << endl;

	if (o.isSquare())
		cout << "Matrix O is square" << endl;
	else
		cout << "Matrix O is not square" << endl;

	o.transpose();

	cout << "\nTranspose of O is: " << endl;
	cout << o << endl;

	Matrix q(2, 2);

	cout << "Matrix O times 3 is: " << endl;
	q = o * 3;

	cout << q << endl;

	Matrix x(2, 2);
	x = m * o;

	cout << "Matrix M times Matrix O is: " << endl;
	cout << x << endl;
}

void matrixTest2()
{
	Matrix m(3, 2);

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 2; j++)
			m.assign(i, j, ( i + j ));

	cout << "Matrix M is: " << endl;
	cout << m << endl;

	Matrix n(2, 3);

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 3; j++)
			n.assign(i, j, ( i + j ));

	cout << "Matrix N is: " << endl;
	cout << n << endl;

	Matrix o = m * n;

	cout << "M * N = " << endl;
	cout << o << endl;
}

void matrixTest3()
{
	Matrix m(3, 3);
	m.assign(0, 0, 1);
	//m.assign(1, 0, 4);
	m.assign(1, 1, 2);
	m.assign(2, 2, 3);

	if (m.isDiagonal())
		cout << "Matrix is a diagonal matrix" << endl;
	else
		cout << "Matrix is not a diagonal matrix" << endl;

	if (m.isSymmetric())
		cout << "Matrix is symmetric" << endl;
	else
		cout << "Matrix is not symmetric" << endl;
}

void matrixTest4()
{
	/*	
	Matrix m(4, 4);

	for (int i = 0; i < 16; i++)
		m.assign(( i / 4 ), ( i % 4 ), i);
	*/
	
	Matrix m(3, 3);
	for (int i = 0; i < 6; i++)
		m.assign(( i / 3 ), ( i % 3 ), ( i + 1 ));

	m.assign(2, 0, 7);
	m.assign(2, 1, 9);
	m.assign(2, 2, 8);
	

	cout << m << endl;

	cout << determinant(m) << endl;	
}

void matrixTest5()
{
	Matrix m1(3, 3);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			m1.assign(i, j, (i + j));

	Matrix m2(3, 3);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			m2.assign(i, j, ( i + 1 + j ));

	Matrix m3 = m1.append(m2);

	cout << m3 << endl;
}

void matrixTest6()
{
	Matrix m1(4, 4);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m1.assign(i, j, ( i + j ));

	cout << m1 << endl;

	m1.resize(3, 3);

	cout << m1 << endl;

	Matrix m2(3, 3);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			m2.assign(i, j, ( 3 * i + 4 * j + 2));
	
	cout << m2 << endl;

	m2 -= m1;

	cout << m2 << endl;

	Matrix m3 = m1 + m2;

	cout << m3 << endl;
}

void matrixTest7()
{
	Matrix m(3, 5);

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++)
			m.assign(i, j, ( i * 2 + j + 3 ));

	cout << m << endl;

	m.transpose();

	cout << m << endl;
}

int main()
{
	//matrixTest1();
	//matrixTest2();
	//matrixTest3();
	//matrixTest4();
	//matrixTest5();
	//matrixTest6();
	matrixTest7();

	system("pause");
	return 0;
}