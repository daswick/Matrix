#pragma once
#include <iostream>
#include <exception>
using namespace std;

class Matrix
{
	public:
		Matrix(int row = 1, int col = 1);
		Matrix(Matrix & m);
		
		const void operator = (const Matrix & rhs);
		Matrix operator + (Matrix & rhs);
		Matrix operator - (Matrix & rhs);
		void operator += (Matrix & rhs);
		void operator -= (Matrix & rhs);
		Matrix operator * (int s);
		Matrix operator * (const Matrix & m);
		Matrix operator *= (int s);
		Matrix operator *= (const Matrix & m);

		bool operator == (Matrix & rhs);
		bool operator != (Matrix & rhs);

		Matrix submatrix (int start_row, int end_row, int start_col, int end_col);
		Matrix append (Matrix & rhs);

		void assign(int row, int col, int entry);
		bool isSquare();
		bool isZeroMatrix();
		bool isSymmetric();
		bool isSkewSymmetric();
		bool isDiagonal();
		const int at(int row, int col) const;
		const int numRows();
		const int numCols();
		const int capacity();

		friend ostream & operator << (ostream & out, Matrix & m);
		friend int trace(Matrix & m);
		friend int determinant(Matrix & m);

		void transpose();
		void clear();
		void resize(int row, int col);

		~Matrix();
		
	private:
		int nRow;
		int nCol;
		int ** matrix;

		const void initialize(int row, int col);
		const void copy(const Matrix & m);
		const void checkBounds(int row, int col) const;

		void interchangeRows(int row1, int row2);
		void scalarMultipleRow(int row, int c);
		void addRows(int row1, int row2);
		Matrix deleteRowAndCol (const Matrix & m, int row, int col);
};