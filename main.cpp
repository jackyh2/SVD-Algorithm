#include <iostream>
#include <iomanip>

#include "SVD.h"

void printAdditionalInfo(Matrix M, SVD svd); 

	/*
	*	INPUT: ./ImageCompression < input > output
	*	input format:
	*	 two space separated numbers m and n, which denote the number of rows and columns of the matrix
	*	 m x n space separated numbers, which denote the entries in the matrix M.
	*	
	*	OUTPUT: It will print out 3 matrices: U, Sigma, V each separated by a space.
	*   U is an m x n matrix with orthonormal columns (U is unitary)
			(technically it is m x m but there may be a few (up to m - n) columns 
			 which are just 0's: ignore those)
		Sigma is an m x n diagonal matrix with the kth diagonal entry being the kth largest singular value
		V is an n x n matrix with orthonormal columns (V is unitary)
		M = U x Sigma x V^*
	*/

int main() {

	std::setprecision(6);
	std::cout << std::fixed;

	int m, n;
	std::cin >> m >> n;

	std::vector<std::vector<double>> data(m, std::vector<double>(n));

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			std::cin >> data[i][j];
		}
	}

	Matrix M(data);

	SVD svd(M);

	//printAdditionalInfo(M, svd);

	svd.printSVD();

}

void printAdditionalInfo(Matrix M, SVD svd) {
	std::cout << M << std::endl;

	std::cout << svd.getU()*svd.getSigma()*(svd.getV().adjoint()) << std::endl;

	//The code below prints out the maximum difference entrywise between M and U x Sigma x V^*.
	//Should be 0.
	std::cout << maxMetric(M, svd.getU()*svd.getSigma()*(svd.getV().adjoint())) << std::endl << std::endl;
}