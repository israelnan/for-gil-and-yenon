#include "MlpNetwork.h"
#include "Activation.h"

MlpNetwork::MlpNetwork (Matrix *weights, Matrix *biases) :
    first_layer(weights[0], biases[0], ::activation::relu),
    second_layer(weights[1], biases[1], ::activation::relu),
    third_layer(weights[2], biases[2], ::activation::relu),
    fourth_layer(weights[3], biases[3], ::activation::softmax)
{}


digit MlpNetwork::get_prediction (const Matrix &final_output)
{
  digit prediction={0,0};
  int argmax_index = 0;
  float max_liklihood = 0;
  for (int i = 0; i < NUMBER_OF_CLASSES; i++)
    {
      if (final_output[i] > max_liklihood)
        {
          argmax_index = i;
          max_liklihood = final_output[i];
        }
    }
  prediction.probability = max_liklihood;
  prediction.value = argmax_index;
  return prediction;
}

digit MlpNetwork::operator() (const Matrix &x)
{

  Matrix first_output = first_layer (x);
  Matrix second_output = second_layer (first_output);
  Matrix third_output = third_layer (second_output);
  Matrix final_output = fourth_layer (third_output);
  return get_prediction (final_output);
}
