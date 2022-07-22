#include "Matrix.h"

#ifndef ACTIVATION_H
#define ACTIVATION_H


typedef Matrix(*activation_func) (const Matrix &m);

namespace activation
{

/**
 * RELU activation function: x=>0 equals x, x<0 equals 0
 * @param m  Matrix
 * @return Matrix element-wise with activation function
 */
    Matrix relu (const Matrix &m);

/**
 * SOFTMAX activation function:
 * -for every 0<=i<=rows , 0<=j<=cols in matrix
 * m the function softmax(m)= (1/(sum of e^(m(i,j) ))e^(x) when e^() is
 * exponential function and x is a vector in R^(n)
 * @param m  Matrix
 * @return Matrix element-wise with activation function
 */
    Matrix softmax (const Matrix &m);
}

#endif //ACTIVATION_H

