#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"
#include "Matrix.h"

class Dense {
 public:

  /**
   * Inits a new layer with given parameters.
   * Ctor accepts 2 matrices and activation function
   * @param weights - weights matrix
   * @param bias - bias vector
   * @param activation_func - RELU \ SOFTMAX
   */
  Dense (Matrix weights, Matrix bias, activation_func func);

/**
   * Returns the weights of this layer.
   * @return w
   */
    Matrix get_weights () const;

  /**
   * Returns the bias of this layer.
   * @return b
   */
    Matrix get_bias () const;

  /**
   * Returns the activation function of this layer.
   * @return activation_func func
   */
  activation_func get_activation () const;

  /**
   *Applies the layer on input and returns output matrix
   *Layers operate as per section 2.2.1
   *e.g: Dense layer(w, b, act); Matrix output = layer(input);
   * @param m - a picture ( vectorized matrix )
   * @return new transformed matrix

   */
  Matrix operator() ( const Matrix &x) ;

 private:
  Matrix weights, bias;
  activation_func func;
};



#endif //DENSE_H
