#ifndef SVD_H
#define SVD_H

#include "Matrix.h"

class SVD {
private:
	Matrix U;
	Matrix Sigma;
	Matrix V;

	int rank;

	void calculate_SVD(Matrix A);

public:
	SVD(Matrix A, int r);

	void printSVD() const;
	void printSVD(std::ostream& os) const;

	Matrix getU() const;
	Matrix getSigma() const;
	Matrix getV() const;
};



#endif