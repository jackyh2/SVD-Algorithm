#include <cassert>
#include <cmath>
#include <iostream>
#include "SVD.h"

SVD::SVD(Matrix A, int r) {
	assert(r <= A.numRows() && r <= A.numCols());
	rank = r;
	calculate_SVD(A);
}

double sgn(double x) {
	if (sameDouble(x, 0)) return 0;
	if (x < 0) return -1;
	return 1;
}

void SVD::calculate_SVD(Matrix A) {

	int m = A.numRows();
	int n = A.numCols();

	U = A;

	V.setIdentityMatrix(n);

	double squaredNorm = U.frobeniusNorm();
	squaredNorm *= squaredNorm;

	double s = 0;
	bool first = true;

	while (sqrt(s) > eps*squaredNorm || first == true) {

		s = 0;
		first = false;

		for (int i = 0; i < n - 1; ++i) {
			for (int j = i + 1; j < n; ++j) {
				double a = 0;
				double b = 0;
				double c = 0;

				for (int k = 0; k < m; ++k) {
					double Uki = U.getElem(k, i);
					double Ukj = U.getElem(k, j);
					a += Uki*Uki;
					b += Ukj*Ukj;
					c += Uki*Ukj;
				}

				s += c*c;

				double zeta = (b - a)/(2.0*c);
				double t = sgn(zeta)/(fabs(zeta) + sqrt(1 + zeta*zeta));
				double cs = 1.0/sqrt(1 + t*t);
				double sn = cs*t;

				Matrix GivensRotation = getGivensRotation(i, j, cs, sn, n);

				U *= GivensRotation;
				V *= GivensRotation;

			}
		}
	}

	Sigma.setIdentityMatrix(n);

	std::vector<double> singularValues;

	for (int i = 0; i < n; ++i) {
		double singularValue = 0;
		for (int k = 0; k < m; ++k) {
			double val = A.getElem(k, i);
			singularValue += val*val;
		}
		singularValue = sqrt(singularValue);

		singularValues.push_back(singularValue);
		//Sigma.setElem(i, i, singularValue);
	}

	std::sort(singularValues.begin(), singularValues.end());

	std::reverse(singularValues.begin(), singularValues.end());

	for (int i = 0; i < singularValues.size(); ++i) {
		Sigma.setElem(i, i, singularValues[i]);
	}

	Matrix SigmaInverse = Sigma;
	for (int i = 0; i < n; ++i) {
		double val = SigmaInverse.getElem(i, i);
		if (!sameDouble(val, 0)) {
			SigmaInverse.setElem(i, i, 1.0/val);
		}
	}

	U *= SigmaInverse;
}

void SVD::printSVD() const {
	U.printMatrix();
	std::cout << std::endl;
	Sigma.printMatrix();
	std::cout << std::endl;
	V.printMatrix();
	std::cout << std::endl;
}
void SVD::printSVD(std::ostream& os) const {
	U.printMatrix(os);
	os << std::endl;
	Sigma.printMatrix(os);
	os << std::endl;
	V.printMatrix(os);
}

Matrix SVD::getU() const {
	return U;
}

Matrix SVD::getSigma() const {
	return Sigma;
}

Matrix SVD::getV() const {
	return V;
}