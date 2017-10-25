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
}