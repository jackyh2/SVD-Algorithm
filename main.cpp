#include <iostream>

#include "Matrix.h"

int main() {
	std::vector<std::vector<double>> t(3);
	t[0].push_back(3.5);
	t[0].push_back(4.5);
	t[0].push_back(5.5);
	t[1].push_back(2.5);
	t[1].push_back(1.5);
	t[1].push_back(0.5);
	t[2].push_back(9);
	t[2].push_back(10);
	t[2].push_back(11);

	Matrix m(t);

	//m.setZeroMatrix();


	m.printMatrix();

	std::cout << std::endl;

	Matrix h = m.adjoint();

	std::cout << h;

	std::cout << std::endl << std::endl;

	std::vector<std::vector<double>> a1(3);
	a1[0] = {1, 2, 3};
	a1[1] = {2, 3, 4};
	a1[2] = {3, 4, 5};

	std::vector<std::vector<double>> b1(3);

	b1[0] = {-1, 1, 1};
	b1[1] = {2, 2, 2};
	b1[2] = {3, 1, 2};

	Matrix a(a1);
	Matrix b(b1);

	//std::cout << a << std::endl;
	//std::cout << b << std::endl;
	//std::cout << -1 * b << std::endl;
	//a -= b;
	//std::cout << a << std::endl;

	//Matrix adj = a * a.adjoint();
	Matrix adj;
	//std::cout << adj.isSymmetric() << std::endl;

	//std::cout << adj;

	adj.setIdentityMatrix(3);

	std::cout << adj;

	std::cout << adj.hasOrthonormalColumns() << std::endl;

	std::cout << adj.frobeniusNorm() << std::endl;
}