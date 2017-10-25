#ifndef DLX_H
#define DLX_H

#include <vector>

class Matrix {
private:
	std::vector<std::vector<double>> m;
	int nRows;
	int nCols;

public:
	Matrix(int r, int c); //r rows, c columns - default initialised to 0 matrix.
	Matrix(const std::vector<std::vector<double>>& data);

	int numRows();
	int numCols();
	double getElem(int r, int c);
	void setElem(int r, int c, double val);

	Matrix& setZeroMatrix();
	Matrix& setIdentityMatrix();

	Matrix adjoint();

	void printMatrix() const;
	void printMatrix(std::ostream& os) const;

};

Matrix operator*(const Matrix& a, const Matrix& b);

std::ostream& operator<<(std::ostream& os, const Matrix& m);










#endif