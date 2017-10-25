#include <iostream>
#include <cassert>
#include <iomanip>

#include "Matrix.h"

Matrix::Matrix(int r, int c) {
	assert(r > 0);
	assert(c > 0);

	m = std::vector<std::vector<double>>(r, std::vector<double>(c));
	nRows = r;
	nCols = c;
}

Matrix::Matrix(const std::vector<std::vector<double>>& data) {

	assert(data.size() > 0);
	for (int i = 0; i < data.size() - 1; ++i) {
		assert(data[i].size() == data[i + 1].size());
	}

	m = data;
	nRows = m.size();
	nCols = m[0].size();
}

int Matrix::numRows() {
	return nRows;
}

int Matrix::numCols() {
	return nCols;
}

double Matrix::getElem(int r, int c) {
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

Matrix& Matrix::setZeroMatrix() {
	for (auto r = m.begin(); r != m.end(); ++r) {
		for (auto c = r->begin(); c != r->end(); ++c) {
			*c = 0;
		}
	}
	return *this;
}

Matrix& Matrix::setIdentityMatrix() {
	assert (nRows == nCols);

	for (int r = 0; r < nRows; ++r) {
		for (int c = 0; c < nCols; ++c) {
			if (r != c) {
				m[r][c] = 0;
			} else {
				m[r][c] = 1;
			}
		}
	}

	return *this;
}

Matrix Matrix::adjoint() {
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
	//std::setprecision(2);
	//os << std::fixed;
	for (auto r = m.begin(); r != m.end(); ++r) {
		for (auto c = r->begin(); c != r->end(); ++c){
			os << *c << " ";
		}
		os << std::endl;
	}

}

Matrix operator*(const Matrix& a, const Matrix& b) {
	assert(a.numCols() == b.numRows());

	Matrix res(a.numRows(), b.numCols());

	
}


std::ostream& operator<<(std::ostream& os, const Matrix& m) {
	m.printMatrix(os);
	return os;
}
