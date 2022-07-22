//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"

#define MLP_SIZE 4

#define NUMBER_OF_CLASSES 10
/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit {
	unsigned int value;
	float probability;
} digit;

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
									{64,  128},
									{20,  64},
									{10,  20}};
const matrix_dims bias_dims[] = {{128, 1},
								 {64,  1},
								 {20,  1},
								 {10,  1}};

/**
 * Accepts 2 arrays of matrices, size 4 each.
 * one for weights and one for biases.
 * constructs the network described (sec. 2.2)
 */
class MlpNetwork
{
 public:
  /**
   * ctor for all layers
   * @param weights container of MLP_SIZE weight matrices
   * @param biases container of 4 MLP_SIZE matrices
   */
  MlpNetwork(Matrix weights[MLP_SIZE], Matrix biases[MLP_SIZE]);

  /**
   * Applies the entire network on input.
   * returns digit struct. MlpNetwork m(...); digit output = m(img);
   * @param x const Matrix &x an image
   * @return digit prediction of the network to the image x
   */
  digit operator()(const Matrix &x);

 private:
  Dense first_layer, second_layer, third_layer, fourth_layer;
  
  static digit get_prediction (const Matrix &final_output) ;
};

#endif // MLPNETWORK_H