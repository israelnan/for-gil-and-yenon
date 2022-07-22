#include "Dense.h"

Dense::Dense (Matrix weights, Matrix bias, activation_func func):
weights (weights), bias (bias), func(func)
{}

 Matrix Dense::get_weights () const
{
  return this->weights;
}

 Matrix Dense::get_bias () const
{
  return this->bias;
}

activation_func Dense::get_activation () const
{
  return (this->func);
}

Matrix Dense::operator() (const Matrix &x)
{
//  Matrix w = this->get_weights ();
//  Matrix b = this->get_bias ();
//  return (*func) ((w * x) + b);
//
  if (x.get_rows()!=weights.get_cols()){
      throw std::length_error(LENGTH_ERROR);
  }
  Matrix result = weights*x;
  result+= bias;
  return func(result);
}

