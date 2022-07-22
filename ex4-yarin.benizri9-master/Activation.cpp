#include "Activation.h"

 Matrix activation::relu (const Matrix &m){
  Matrix res_matrix = Matrix(m);
  for (int i = 0; i < m.get_rows(); i++)
    {
      for (int j = 0; j < m.get_cols(); j++)
        {
          if (m[i*m.get_cols() +j] < 0)
            {
              res_matrix(i,j) = 0;
            }
        }
    }
  return res_matrix;
}

Matrix activation::softmax (const Matrix &m){
  float exp_sum = 0;
  for (int i = 0; i < m.get_rows(); i++)
    {
      for (int j = 0; j < m.get_cols(); j++)
        {
          exp_sum += std::exp(m(i,j));
        }
    }
  Matrix res_matrix = Matrix(m.get_rows(), m.get_cols());
  for (int i = 0; i < m.get_rows(); i++)
    {
      for (int j = 0; j < m.get_cols(); j++)
        {
          float exp_val = std::exp(m(i,j));
          res_matrix(i,j) = (1 / exp_sum) * exp_val;
        }
    }
  return res_matrix;
}






