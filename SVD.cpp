#include <cassert>
#include <cmath>
#include <iostream>
#include "SVD.h"

SVD::SVD(Matrix A) {
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

	//Set U to be A. 
	U = A;

	//Set V to be the n x n identity matrix.
	V.setIdentityMatrix(n);

	double squaredNorm = U.frobeniusNorm();
	squaredNorm *= squaredNorm;

	double s = 0;
	bool first = true;

	//repeat until convergence
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


				//Find the values of cos(theta) and sin(theta).
				double zeta;
				if (!sameDouble(c, 0)) {
					zeta = (b - a)/(2.0*c);
				} else {
					zeta = std::numeric_limits<double>::max();
				}

				double t;
				if (!sameDouble(c, 0)) {
					t = sgn(zeta)/(fabs(zeta) + sqrt(1 + zeta*zeta));
				} else {
					t = 0;
				}

				double cs = 1.0/sqrt(1 + t*t);
				double sn = cs*t;

				//Construct the givens rotation matrix
				Matrix GivensRotation = getGivensRotation(i, j, cs, sn, n);

				U *= GivensRotation;
				V *= GivensRotation;

			}
		}
	}

	
	//scrape all the singular values from the matrix U. These are just the l_2 norms of the columns.
	std::vector<std::pair<int, double>> singularValues;

	for (int i = 0; i < n; ++i) {
		double singularValue = 0;
		for (int k = 0; k < m; ++k) {
			double val = U.getElem(k, i);
			singularValue += val*val;
		}
		singularValue = sqrt(singularValue);


		if (!sameDouble(singularValue,0)) singularValues.push_back(std::make_pair(i,singularValue));
	}


	//Sort the singular values so we can present Sigma in the form such that the singular values
	//are in decreasing order of magnitude
	std::sort(singularValues.begin(), singularValues.end(),[](const std::pair<int, double> &lhs,
													const std::pair<int, double> &rhs) {
														return lhs.second < rhs.second;
													});

	std::reverse(singularValues.begin(), singularValues.end());


	//Write to the Sigma matrix
	Sigma = A;
	Sigma.setZeroMatrix();

	for (int i = 0; i < singularValues.size(); ++i) {
		Sigma.setElem(i, i, singularValues[i].second);
	}

	//Calculate the inverse of the Sigma matrix.
	Matrix SigmaInverse = Sigma.adjoint(); 
	SigmaInverse.setZeroMatrix();

	for (int i = 0; i < singularValues.size(); ++i) {
		double val = Sigma.getElem(i, i);
		
		SigmaInverse.setElem(i, i, 1.0/val);
		
	}


	//Reorder the columns of U and V according to the singular values which we sorted above.
	Matrix tmpU = U;
	Matrix tmpV = V;

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {

			double tmp1;
			if (j < singularValues.size()) {
				tmp1 = tmpU.getElem(i, singularValues[j].first);
			} else {
				tmp1 = tmpU.getElem(i, j);
			}
			
			U.setElem(i, j, tmp1);
			
		}
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			double tmp1;
			if (j < singularValues.size()) {
				tmp1 = tmpV.getElem(i, singularValues[j].first);
			} else {
				tmp1 = tmpV.getElem(i, j);
			}
			V.setElem(i, j, tmp1);
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