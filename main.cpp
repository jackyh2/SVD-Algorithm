#include <iostream>
#include <iomanip>

#include "SVD.h"

void test(); 

int main() {
	std::setprecision(6);
	std::cout << std::fixed;

	test();
}


void test() {
	
	/*std::vector<std::vector<double>> t(3);
	t[0].push_back(3.5);
	t[0].push_back(4.5);
	t[0].push_back(5.5);
	t[1].push_back(2.5);
	t[1].push_back(1.5);
	t[1].push_back(0.5);
	t[2].push_back(9);
	t[2].push_back(10);
	t[2].push_back(11);

	Matrix m(t);*/

	//m.setZeroMatrix();


	//m.printMatrix();

	//std::cout << std::endl;

	//Matrix h = m.adjoint();

	//std::cout << h;

	//std::cout << std::endl << std::endl;

	/*std::vector<std::vector<double>> a1(3);
	a1[0] = {1, 2, 3};
	a1[1] = {2, 3, 4};
	a1[2] = {3, 4, 5};

	std::vector<std::vector<double>> b1(4);

	b1[0] = {1, 0, 0, 1};
	b1[1] = {0, 1, 1, 1};
	b1[2] = {0, 0, 1, 1};
	b1[3] = {0, 0, 1, 1};

	Matrix a(a1);
	Matrix b(b1);

	b.setIdentityMatrix(4);*/

	



	//std::cout << a << std::endl;
	//std::cout << b << std::endl;
	//std::cout << -1 * b << std::endl;
	//a -= b;
	//std::cout << a << std::endl;

	//Matrix adj = a * a.adjoint();
	
	//std::cout << adj.isSymmetric() << std::endl;


	//std::cout << adj;

	

	/*std::cout << adj;

	std::cout << adj.hasOrthonormalColumns() << std::endl;

	std::cout << adj.frobeniusNorm() << std::endl;

	std::cout << std::endl << std::endl << std::endl;*/

	Matrix c({{-1, 1, 1, 4}, {2, 2, 2, 3}, {3,1,2, 19}, {9, 3, 121, 93}});
	
	SVD ate(c,3);
	//ate.printSVD();
	std::cout << std::endl;
	std::cout << c << std::endl;


	//ate.printSVD();


	std::cout << ate.getU()*ate.getSigma()*(ate.getV().adjoint()) << std::endl;

	//std::cout << std::endl;

	ate.printSVD();

	//std::cout << ate.getU().hasOrthonormalColumns() << std::endl;
}