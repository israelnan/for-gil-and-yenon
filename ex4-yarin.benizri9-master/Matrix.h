#include <cmath>
#include <iostream>
#include <stdexcept>
#ifndef MATRIX_H
#define MATRIX_H
#define LENGTH_ERROR "Not same length"
#define RANGE_ERROR "ERROR: try to access un legal memory"

#define PRINT_RATIO 0.1
#define ERROR_INPUT "ERROR: not valid input"
/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims {
    int rows, cols;
} matrix_dims;

class Matrix {
 public:

  /**
  * Constructs Matrix of size rows × cols initialize all elements to 0.
  * @param rows - int number of rows
  * @param cols - int number of columns
  */
  Matrix (int rows, int cols);

  /**
  *default ctor:
  * Constructs Matrix of size 1×1. initialize the single element to 0
  */
  Matrix ();

  /**
  * copy constructor:
  * Constructs matrix from another Matrix m.
  * @param m matrix
  */
  Matrix (const Matrix &m);

  /**
  * destructor for class Matrix - frees mat from memory
  */
  ~Matrix ();

  /**
  * @return amount of rows as int
  */
  int get_rows () const;

  /**
  * @return amount of columns as int
  */
  int get_cols () const;

  /**
   * converts a matrix into its transpose matrix
   * i.e: (A.transpose())ij = Aji.
   * @return matrix
   */
  Matrix &transpose ();

  /**
   * Transforms a matrix into a column vector (section 3.1.2).
    Supports function calling concatenation.
    e.g.: Matrix m(5,4); m.vectorize();
    m.get cols() == 1 & m.get rows() == 20
   * @return matrix
   */
  Matrix &vectorize ();

  /**
  Prints matrix elements, no return value.
   Prints space after each element (including last element in row).
   Prints newline after each row (including last row).
  */
  void plain_print () const;


  /**
   *Returns a matrix which is the elementwise multiplication
   *(Hadamard product) of this matrix and another matrix m
   * @return float
   *
   */
  Matrix dot ( const Matrix& b) const;

/**
 * Returns the Frobenius norm of the given matrix (root of dot of same matrix)
 * @return float
 */
  float norm () const;

  /**
	 * + operator: Matrix a, b; → a + b
	 * @param b  const Matrix&
	 * @return  by value (a + b) new matrix of sum
	 */
  Matrix operator+ (const Matrix &b);

  /**
	 * assignment operator - Matrix a, b; → a = b
	 * @param b  matrix
	 * @return current matrix after assignment to b
	 */
  Matrix &operator= (const Matrix &b);

  /**
	 * Matrix multiplication Matrix a, b; → a * b
	 * when a.cols = b.rows
	 * @param a - const Matrix&
	 * @param b - const Matrix&
	 * @return by value multiplication matrix (a * b)
	 */
  Matrix operator* (const Matrix &b);

  /**
	 Scalar multiplication on the right Matrix m; float c; → m * c
	 * @param c - scalar value
	 * @return by value matrix (m * c)
	 */
  Matrix operator* (float c)const ;

/**
 * Scalar multiplication on the left Matrix m; float c; → c * m
 * @param c -  scalar value
 * @param m -  matrix
 * @return by value matrix (m * c)
 */
  friend Matrix operator* (float c, const Matrix &m);

/**
	 * Matrix addition accumulation Matrix a, b; → a += b
	 * @param b  const Matrix &b
	 * @return by reference matrix a+b
	 */
  Matrix &operator+= (const Matrix &b);

  /**
	Parenthesis indexing For i,j indices, Matrix m:
    m(i,j) will return the i,j element in the matrix
    e.g: Matrix m(5,4); m(1,3) = 10; float x = m(1,3); // x==10
	 * @param i int i row index
	 * @param j int i column index
	 * @return this->matrix[i*cols+j] the i,j element in the matrix
	 */
  float& operator() (int i, int j) ;
/**
  * Parenthesis indexing For i,j indices CONST VERSION
  * Matrix m: m(i,j) will return the i,j element in the matrix
  * e.g.
  * Matrix m(5,4);
  * m(1,3) = 10;
  * float x = m(1,3); // x==10
  * @param i row index
  * @param j column index
  * @return i,j element in the matrix
 */
  float operator() (int i, int j) const;

/**
 Brackets indexing For i index, Matrix m:
  m[i] will return the i’th element (section 3.1.2)
  e.g.
  Matrix m(5,4);
  m[3] = 10;
  float x = m[3]; // x==10
 * @param i  index
   * @return i’th element in the matrix
   */
  float& operator[] (int i);

/**
   * Brackets indexing For i index CONST VERSION
   * @param i  index
   * @return i’th element in the matrix
   */
  float operator[] (int i) const;

/**
    * Pretty export of matrix as per section 3.1.1 in ex4.pdf file
    * @param os output stream
    * @param m matrix
    * @return os
    */
  friend std::ostream &operator<< (std::ostream &os, const Matrix &m);

/**
 * Fills matrix elements: has to read input
 * stream fully, otherwise it’s an error
 * (don't trust the user to validate it).
 * @param is input stream
 * @param m matrix
 * @return is
 */
  friend std::istream &operator>> (std::istream &is, const Matrix &m);

 private:
  int rows, cols;
  float *matrix;

};
#endif //MATRIX_H