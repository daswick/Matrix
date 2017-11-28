#include "Matrix.h"

Matrix::Matrix(int row, int col)
{
	initialize(row, col);
}

Matrix::Matrix(Matrix & m)
{
	initialize(m.nRow, m.nCol);

	copy(m);
}

const void Matrix::operator = (const Matrix & rhs)
{
	this->~Matrix();

	initialize(rhs.nRow, rhs.nCol);

	copy(rhs);
}

Matrix Matrix::operator + (Matrix & rhs)
{
	if (nRow != rhs.nRow || nCol != rhs.nCol)
		throw invalid_argument("Matrices not compatible for addition");

	Matrix sum(nRow, nCol);

	for (int i = 0; i < nRow; i++)
		for (int j = 0; j < nCol; j++)
			sum.matrix[i][j] = matrix[i][j] + rhs.matrix[i][j];

	return sum;
}

Matrix Matrix::operator - (Matrix & rhs)
{
	if (nRow != rhs.nRow || nCol != rhs.nCol)
		throw invalid_argument("Matrices not compatible for subtraction");

	Matrix diff(nRow, nCol);

	for (int i = 0; i < nRow; i++)
		for (int j = 0; j < nCol; j++)
			diff.matrix[i][j] = matrix[i][j] - rhs.matrix[i][j];

	return diff;
}

void Matrix::operator += (Matrix & rhs)
{
	*this = *this + rhs;
}

void Matrix::operator -= (Matrix & rhs)
{
	*this = *this - rhs;
}

Matrix Matrix::operator * (int s)
{
	Matrix product(nRow, nCol);

	for (int i = 0; i < nRow; i++)
		for (int j = 0; j < nCol; j++)
			product.matrix[i][j] = matrix[i][j] * s;

	return product;
}

Matrix Matrix::operator * (const Matrix & m)
{
	if (nCol != m.nRow)
		throw logic_error("Matrices not compatible for multiplication");

	Matrix product(nRow, m.nCol);

	for (int i = 0; i < product.nRow; i++)
		for (int j = 0; j < product.nCol; j++)
			for (int k = 0; k < nCol; k++)
				product.matrix[i][j] += matrix[i][k] * m.matrix[k][j];

	return product;
}

Matrix Matrix::operator *= (int s)
{
	Matrix product = *this * s;
	return product;
}

Matrix Matrix::operator *= (const Matrix & m)
{
	Matrix product = *this * m;
	return product;
}

bool Matrix::operator == (Matrix & rhs)
{
	if (nRow != rhs.nRow || nCol != rhs.nCol)
		return false;

	for (int i = 0; i < nRow; i++)
		for (int j = 0; j < nCol; j++)
			if (matrix[i][j] != rhs.matrix[i][j])
				return false;

	return true;
}

bool Matrix::operator != (Matrix & rhs)
{
	return !( *this == rhs );
}

Matrix Matrix::submatrix (int start_row, int end_row, int start_col, int end_col)
{
	checkBounds(start_row, start_col);
	checkBounds(end_row, end_col);

	if (end_row < start_row || end_col < start_col)
		throw logic_error("Dimensions entered invalid");

	int newrow = end_row - start_row + 1;
	int newcol = end_col - start_col + 1;

	Matrix sub(newrow, newcol);

	for (int i = start_row; i <= end_row; i++)
		for (int j = start_col; j <= end_col; j++)
			sub.assign(i - start_row, j - start_col, matrix[i][j]);

	return sub;
}

Matrix Matrix::append (Matrix & rhs)
{
	if (nRow != rhs.nRow)
		throw logic_error("Matrix dimensions not compatible for appending");

	Matrix app(nRow, nCol + rhs.nCol);

	app.copy(*this);

	for (int i = 0; i < nRow; i++)
		for (int j = 0; j < rhs.nCol; j++)
			app.assign(i, j + nCol, rhs.matrix[i][j]);

	return app;
}

void Matrix::assign(int row, int col, int entry)
{
	checkBounds(row, col);

	matrix[row][col] = entry;
}

bool Matrix::isSquare()
{
	return ( nRow == nCol );
}

bool Matrix::isZeroMatrix()
{
	for (int i = 0; i < nRow; i++)
		for (int j = 0; i < nCol; j++)
			if (matrix[i][j] != 0)
				return false;

	return true;
}

bool Matrix::isSymmetric()
{
	if (!isSquare())
		return false;

	for (int i = 0; i < nRow; i++)
		for (int j = 0; j < nCol; j++)
			if (matrix[i][j] != matrix[j][i])
				return false;

	return true;
}

bool Matrix::isSkewSymmetric()
{
	if (!isSquare())
		return false;

	for (int i = 0; i < nRow; i++)
		for (int j = 0; j < nCol; j++)
			if (matrix[i][j] != ( -1 * matrix[j][i] ))
				return false;

	return true;
}

bool Matrix::isDiagonal()
{
	if (!isSquare())
		return false;

	for (int i = 0; i < nRow; i++)
		for (int j = 0; j < nCol; j++)
			if (i != j && matrix[i][j] != 0)
				return false;

	return true;
}

const int Matrix::at(int row, int col) const
{
	checkBounds(row, col);

	return matrix[row][col];
}

const int Matrix::numRows()
{
	return nRow;
}

const int Matrix::numCols()
{
	return nCol;
}

const int Matrix::capacity()
{
	return (nRow * nCol);
}

ostream & operator << (ostream & out, Matrix & m)
{
	for (int i = 0; i < m.numRows(); i++)
	{
		for (int j = 0; j < m.numCols(); j++)
			printf("%4d", m.at(i, j));
		out << endl;
	}
	return out;
}

int trace(Matrix & m)
{
	if (!m.isSquare())
		throw invalid_argument("Matrix is not square");

	int sum = 0;
	for (int i = 0; i < m.nRow; i++)
		sum += m.at(i, i);

	return sum;
}

int determinant(Matrix & m)
{
	if (!m.isSquare())
		return NULL;

	if (m.nCol == 1)
		return m.at(0, 0);

	if (m.nCol == 2)
		return ( ( m.at(0, 0) * m.at(1, 1) ) - ( m.at(0, 1) * m.at(1, 0) ) );

	int det = 0;
	for (int i = 0; i < m.nCol; i++)
		det += ( m.at(0, i) *  determinant(m.deleteRowAndCol(m, 0, i)) ) * ( ( i % 2 == 1 ) ? -1 : 1 );

	return det;
}

void Matrix::transpose()
{
	Matrix copy(*this);

	this->~Matrix();

	initialize(nCol, nRow);

	for (int i = 0; i < nRow; i++)
		for (int j = 0; j < nCol; j++)
			matrix[i][j] = copy.matrix[j][i];
}

void Matrix::clear()
{
	for (int i = 0; i < nRow; i++)
		for (int j = 0; j < nCol; j++)
			matrix[i][j] = 0;
}

void Matrix::resize(int row, int col)
{
	Matrix clone(*this);

	this->~Matrix();

	initialize(row, col);

	copy(clone);
}

Matrix::~Matrix()
{
	for (int i = 0; i < nRow; i++)
		delete[] matrix[i];
	delete[] matrix;
}

const void Matrix::initialize(int row, int col)
{
	nRow = row;
	nCol = col;

	matrix = new int *[row];

	for (int i = 0; i < row; i++)
	{
		matrix[i] = new int[col];
		for (int j = 0; j < col; j++)
			matrix[i][j] = 0;
	}
}

const void Matrix::copy(const Matrix & m)
{
	int row = ( nRow < m.nRow ) ? nRow : m.nRow;
	int col = ( nCol < m.nCol ) ? nCol : m.nCol;

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			matrix[i][j] = m.matrix[i][j];
}

const void Matrix::checkBounds(int row, int col) const
{
	if (row > nRow || row < 0 || col > nCol || col < 0)
		throw range_error("Matrix index out of range");
}

void Matrix::interchangeRows(int row1, int row2)
{
	checkBounds(row1, 0);
	checkBounds(row2, 0);

	swap(matrix[row1], matrix[row2]);
}

void Matrix::scalarMultipleRow(int row, int c)
{
	checkBounds(row, 0);

	for (int i = 0; i < nCol; i++)
		matrix[row][i] *= c;
}

void Matrix::addRows(int row1, int row2)
{
	checkBounds(row1, 0);
	checkBounds(row2, 0);

	for (int i = 0; i < nCol; i++)
		matrix[row2][i] += matrix[row1][i];
}

Matrix Matrix::deleteRowAndCol (const Matrix & m, int row, int col)
{
	int newrow = m.nRow - 1;
	int newcol = m.nCol - 1;

	Matrix sub(newrow, newcol);

	for (int i = 0; i < m.nRow; i++)
	{
		for (int j = 0; j < m.nCol; j++)
		{
			if (i == row || j == col)
				continue;
			else
				sub.assign(( i > row ) ? i - 1 : i, ( j > col ) ? j - 1 : j, m.matrix[i][j]);
		}
	}

	return sub;
}