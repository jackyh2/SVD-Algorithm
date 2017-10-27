#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix {
private:
	std::vector<std::vector<double>> m;
	int nRows;
	int nCols;

public:
	Matrix();
	Matrix(int r, int c); //r rows, c columns - default initialised to 0 matrix.
	Matrix(const std::vector<std::vector<double>>& data);

	Matrix& operator=(const Matrix& a);
	Matrix& operator*=(const Matrix& a);
	Matrix& operator*=(double k);
	Matrix& operator+=(const Matrix& a);
	Matrix& operator-=(const Matrix& a);

	int numRows() const;
	int numCols() const;
	double getElem(int r, int c) const;
	void setElem(int r, int c, double val);
	std::vector<std::vector<double>> getMatrix() const;
	bool isSymmetric() const;
	bool isDiagonal() const;
	bool hasOrthonormalColumns() const;
	double frobeniusNorm() const;

	void updateMatrix(const std::vector<std::vector<double>>& data);
	Matrix& setZeroMatrix();
	Matrix& setIdentityMatrix(int n);

	Matrix adjoint() const;

	void printMatrix() const;
	void printMatrix(std::ostream& os) const;

};

Matrix operator*(const Matrix& a, const Matrix& b);
Matrix operator*(const Matrix& a, double k);
Matrix operator*(double k, const Matrix& b);
bool operator==(const Matrix& a, const Matrix& b);
Matrix operator+(const Matrix& a, const Matrix& b);
Matrix operator-(const Matrix& a, const Matrix& b);

std::ostream& operator<<(std::ostream& os, const Matrix& m);


#endif