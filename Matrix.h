#ifndef DLX_H
#define DLX_H

#include <vector>

class Matrix {
public:
	std::vector<std::vector<double>> m;
	int nRows;
	int nCols;

public:
	Matrix(int r, int c); //r rows, c columns - default initialised to 0 matrix.
	Matrix(const std::vector<std::vector<double>>& data);

	int numRows();
	int numCols();


	void setZeroMatrix();
	void setIdentityMatrix();

	void printMatrix();

};








#endif