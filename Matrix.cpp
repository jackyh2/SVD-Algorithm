#include <iostream>
#include <cassert>

#include "Matrix.h"

Matrix::Matrix(int r, int c) {
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

void Matrix::setZeroMatrix() {
	for (auto r = m.begin(); r != m.end(); ++r) {
		for (auto c = r->begin(); c != r->end(); ++c) {
			*c = 0;
		}
	}
}

void Matrix::setIdentityMatrix() {
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
}


void Matrix::printMatrix() {

	for (auto r = m.begin(); r != m.end(); ++r) {
		for (auto c = r->begin(); c != r->end(); ++c){
			std::cout << *c << " ";
		}
		std::cout << std::endl;
	}

}
