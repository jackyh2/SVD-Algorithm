# SVD-Algorithm

The Singular Value Decomposition of a matrix A is a way to factor A into the product of three different matrices, each with special properties. Due to these properties, the SVD can be widely applied to many different problems.

This repo contains an implementation in C++ of the one sided Jacobi eigenvalue algorithm to calculate a SVD for any real matrix.




Input to the algorithm: 
First line consists of two space separated numbers m and n, which denote the number of rows and columns in the matrix.
Then m lines follow, where each line consists of n space separated real numbers representing the matrix.

Output:
Three matrices U, Sigma, V such that A = U x Sigma x V^*
