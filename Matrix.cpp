#include <iostream>
#include <cassert>
#include <iomanip>
#include <cmath>

#include "Matrix.h"

bool sameDouble(double a, double b) {
	return fabs(a - b) < eps;
}

double dotProduct(const std::vector<double>& a, const std::vector<double>& b) {
	assert(a.size() == b.size());
	double sum = 0;
	for (int i = 0; i < a.size(); ++i) {
		sum += a[i]*b[i];
	}
	return sum;
}

Matrix::Matrix() {
	//default to 3 by 3 zero matrix
	Matrix(3, 3);
}

Matrix::Matrix(int r, int c) {
	assert(r > 0);
	assert(c > 0);

	m = std::vector<std::vector<double>>(r, std::vector<double>(c));
	nRows = r;
	nCols = c;
}

Matrix::Matrix(const std::vector<std::vector<double>>& data) {

	updateMatrix(data);
}

Matrix& Matrix::operator=(const Matrix& a) {
	if (this != &a) {
		m = a.getMatrix();
		nRows = a.numRows();
		nCols = a.numCols();
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& a) {
	if (this != &a) {
		Matrix tmp(m);
		*this = tmp * a;
	}
	return *this;
}

Matrix& Matrix::operator*=(double k) {
	Matrix tmp(m);
	*this = tmp * k;
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& a) {
	if (this != &a) {
		Matrix tmp(m);
		*this = tmp + a;
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& a) {
	if (this != &a) {
		Matrix tmp(m);
		*this = tmp - a;
	}
	return *this;
}

int Matrix::numRows() const {
	return nRows;
}

int Matrix::numCols() const {
	return nCols;
}

double Matrix::getElem(int r, int c) const {
	assert(r >= 0);
	assert(c >= 0);
	assert(r < nRows);
	assert(c < nCols);

	return m[r][c];
}

void Matrix::setElem(int r, int c, double val) {
	assert(r >= 0);
	assert(c >= 0);
	assert(r < nRows);
	assert(c < nCols);

	m[r][c] = val;
}

std::vector<std::vector<double>> Matrix::getMatrix() const {
	return m;
}

bool Matrix::isSymmetric() const {
	for (int r = 0; r < nRows; ++r) {
		for (int c = 0; c < nCols; ++c) {
			if (!sameDouble(m[r][c], m[c][r])) return false;
		}
	}
	return true;
}

bool Matrix::isDiagonal() const {
	for (int r = 0; r < nRows; ++r) {
		for (int c = 0; c < nCols; ++c) {
			if (r == c) continue;
			if (!sameDouble(m[r][c], 0.0)) return false;
		}
	}
	return true;
}

bool Matrix::hasOrthonormalColumns() const {
	Matrix tmp = adjoint();
	std::vector<std::vector<double>> matrix = tmp.getMatrix();

	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = 0; j < matrix.size(); ++j) {
			if (i == j) {
				if (!sameDouble(dotProduct(matrix[i], matrix[j]), 1)) {
					return false;
				}
			} else {
				if (!sameDouble(dotProduct(matrix[i], matrix[j]), 0)) {
					return false;
				}
			}
		}
	}
	return true;
}

double Matrix::frobeniusNorm() const {
	double norm = 0;
	for (int i = 0; i < nRows; ++i) {
		for (int j = 0; j < nCols; ++j) {
			norm += m[i][j]*m[i][j];
		}
	}
	return sqrt(norm);
}

void Matrix::updateMatrix(const std::vector<std::vector<double>>& data) {
	assert(data.size() > 0);
	for (int i = 0; i < data.size() - 1; ++i) {
		assert(data[i].size() == data[i + 1].size());
	}

	m = data;
	nRows = m.size();
	nCols = m[0].size();
}

Matrix& Matrix::setZeroMatrix() {
	for (auto r = m.begin(); r != m.end(); ++r) {
		for (auto c = r->begin(); c != r->end(); ++c) {
			*c = 0;
		}
	}
	return *this;
}

Matrix& Matrix::setIdentityMatrix(int n) {
	m = std::vector<std::vector<double>>(n, std::vector<double>(n));

	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			if (r != c) {
				m[r][c] = 0;
			} else {
				m[r][c] = 1;
			}
		}
	}
	nRows = n;
	nCols = n;

	return *this;
}

Matrix Matrix::adjoint() const {
	Matrix adj(nCols, nRows);

	for (int c = 0; c < nCols; ++c) {
		for (int r = 0; r < nRows; ++r) {
			adj.setElem(c, r, m[r][c]);
		}
	}
	return adj;
}

void Matrix::printMatrix() const {
	printMatrix(std::cout);
}


void Matrix::printMatrix(std::ostream& os) const {
	for (auto r = m.begin(); r != m.end(); ++r) {
		for (auto c = r->begin(); c != r->end(); ++c){
			if (!sameDouble(*c, 0)) {
				os << *c << " ";
			} else {
				os << 0.000000 << " ";
			}
		}
		os << std::endl;
	}

}

Matrix getGivensRotation(int r, int c, double cs, double sn, int n) {
	Matrix givens;
	givens.setIdentityMatrix(n);
	givens.setElem(r, r, cs);
	givens.setElem(r, c, sn);
	givens.setElem(c, r, -sn);
	givens.setElem(c, c, cs);
	return givens;
}

Matrix operator*(const Matrix& a, const Matrix& b) {
	
	assert(a.numCols() == b.numRows());

	Matrix res(a.numRows(), b.numCols());

	for (int i = 0; i < a.numRows(); ++i) {
		for (int j = 0; j < b.numCols(); ++j) {
			double val = 0;
			for (int k = 0; k < a.numCols(); ++k) {
				val += a.getElem(i, k)*b.getElem(k, j);
			}
			res.setElem(i, j, val);
		}
	}

	return res;
}

Matrix operator*(double k, const Matrix& b) {
	
	Matrix res(b.numRows(), b.numCols());

	for (int i = 0; i < b.numRows(); ++i) {
		for (int j = 0; j < b.numCols(); ++j) {
			res.setElem(i, j, k*b.getElem(i, j));
		}
	}

	return res;
}

Matrix operator*(const Matrix& b, double k) {
	return (k * b);
}

Matrix operator+(const Matrix& a, const Matrix& b) {
	assert(a.numCols() == b.numCols() && a.numRows() == b.numRows());

	Matrix res(a.numRows(), a.numCols());

	for (int i = 0; i < a.numRows(); ++i) {
		for (int j = 0; j < b.numCols(); ++j) {
			res.setElem(i, j, a.getElem(i, j) + b.getElem(i, j));
		}
	}
	return res;
}

Matrix operator-(const Matrix& a, const Matrix& b) {
	Matrix c = a;
	Matrix d = b;
	d *= -1;
	Matrix res = c + d;
	return res;
}

bool operator==(const Matrix& a, const Matrix& b) {
	if (a.numCols() != b.numCols() || a.numRows() != b.numRows()) return false;

	for (int r = 0; r < a.numRows(); ++r) {
		for (int c = 0; c < a.numCols(); ++c) {
			if (!sameDouble(a.getElem(r, c), b.getElem(r, c))) return false;
		}
	}
	return true;
}

double maxMetric(const Matrix& a, const Matrix& b) {
	assert(a.numCols() == b.numCols() && a.numRows() == b.numRows());

	double distance = 0;

	for (int r = 0; r < a.numRows(); ++r) {
		for (int c = 0; c < a.numCols(); ++c) {
			distance = fmax(distance, fabs(a.getElem(r, c) - b.getElem(r, c)));
		}
	}
	return distance;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
	m.printMatrix(os);
	return os;
}
