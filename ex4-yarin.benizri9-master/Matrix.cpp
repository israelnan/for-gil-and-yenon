#include "Matrix.h"




//Constructors:

Matrix::Matrix (int rows, int cols)
    : rows (rows), cols (cols), matrix (nullptr)
{
  if (rows <= 0 || cols <= 0) // checking valid input
    {
      throw std::length_error (LENGTH_ERROR);
    }
  matrix = new float[rows * cols];
  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
        {
          matrix[i * cols + j] = 0;
        }
    }
}

Matrix::Matrix () : Matrix (1, 1)
{}

Matrix::Matrix (const Matrix &m) : Matrix (m.rows, m.cols)
{
  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
        {
          this->matrix[i * cols + j] = m.matrix[i * cols + j];
        }
    }
}

Matrix::~Matrix ()
{
  delete[] this->matrix;
  this->matrix = nullptr;
}

//Methods & Functions:

int Matrix::get_cols () const
{
  return cols;
}

int Matrix::get_rows () const
{
  return rows;
}

Matrix &Matrix::transpose ()
{
  auto *transpose_mat = new (std::nothrow) float[cols * rows];
  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
        {
          transpose_mat[j * rows + i] = this->matrix[i * cols + j];
        }
    }
  delete[] this->matrix;
  this->matrix = transpose_mat;
  int tmp_rows = this->get_rows ();
  this->rows = this->get_cols ();
  this->cols = tmp_rows;
  return *this;
}

Matrix &Matrix::vectorize ()
{
  this->rows = this->cols * this->rows;
  this->cols = 1;
  return *this;
}

void Matrix::plain_print () const
{
  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
        {
          std::cout << this->matrix[i * cols + j] << " ";
        }
      std::cout << std::endl;
    }
}

Matrix Matrix::dot (const Matrix &m) const
{
  if (this->rows != m.rows || this->cols != m.cols)
    {
      throw std::length_error (LENGTH_ERROR);
    }
  Matrix dot_matrix = Matrix (this->rows, this->cols);

  for (int i = 0; i < this->rows; i++)
    {
      for (int j = 0; j < this->cols; j++)
        {
          dot_matrix.matrix[i * cols + j] = this->matrix[i * cols + j] *
                                            m.matrix[i * cols + j];
        }
    }
  return dot_matrix;
}

float Matrix::norm () const
{
  Matrix square_matrix = this->dot (*this);
  float square_sum = 0;
  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
        {
          square_sum += square_matrix.matrix[i * cols + j];
        }
    }
  return std::sqrt (square_sum);
}

//Operators:

Matrix Matrix::operator+ (const Matrix &b)
{
  if (this->rows != b.rows || this->cols != b.cols)
    {
      throw std::length_error (LENGTH_ERROR);
    }
  Matrix sum_matrix = Matrix (this->rows, this->cols);
  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
        {
          sum_matrix.matrix[i * sum_matrix.cols + j] =
              this->matrix[i * this->cols + j] + b.matrix[i * b.cols + j];
        }
    }
  return sum_matrix;
}

Matrix &Matrix::operator= (const Matrix &b)
{
  if (this != &b) // self assignment check
    {
      delete[] this->matrix;
      this->matrix = new (std::nothrow) float[b.rows * b.cols];
      this->rows = b.rows;
      this->cols = b.cols;
      for (int i = 0; i < this->rows; i++)
        {
          for (int j = 0; j < this->cols; j++)
            {
              this->matrix[i * cols + j] = b.matrix[i * cols + j];
            }
        }
    }
  return *this;
}

Matrix Matrix::operator* (const Matrix &b)
{
  if (this->cols != b.rows) //a*b multiplication not defined
    {
      throw std::length_error (LENGTH_ERROR);
    }
  Matrix multiplication_matrix = Matrix (this->rows, b.cols);
  float sum = 0;
  for (int i = 0; i < this->rows; i++)
    {
      for (int j = 0; j < b.cols; j++)
        {
          for (int t = 0; t < b.rows; t++)
            {
              sum += this->matrix[i * this->cols + t] *
                     b.matrix[t * b.cols + j];
            }
          multiplication_matrix.matrix[i * multiplication_matrix.cols
                                       + j] = sum;
          sum = 0;
        }
    }
  return multiplication_matrix;
}

Matrix Matrix::operator* (float c) const
{
  Matrix multiplication_matrix = Matrix (this->rows, this->cols);
  for (int i = 0; i < this->rows; i++)
    {
      for (int j = 0; j < this->cols; j++)
        {
          multiplication_matrix.matrix[i * multiplication_matrix.cols + j] =
              this->matrix[i * this->cols + j] * c;
        }
    }
  return multiplication_matrix;
}

Matrix operator* (float c, const Matrix &m)
{
  return m * c;
}

Matrix &Matrix::operator+= (const Matrix &b)
{
  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
        {
          this->matrix[i * this->cols + j] += b.matrix[i * b.cols + j];
        }
    }
  return *this;
}

float &Matrix::operator() (int i, int j)
{
  if (i * cols + j < 0 || i >= rows || j >= cols || j < 0 || i < 0)
    {
      throw std::out_of_range (RANGE_ERROR);
    }
  return this->matrix[i * cols + j];
}

float Matrix::operator() (int i, int j) const
{
  if (i * cols + j < 0 || i >= rows || j >= cols || j < 0 || i < 0)
    {
      throw std::out_of_range (RANGE_ERROR);
    }
  return this->matrix[i * cols + j];
}

float &Matrix::operator[] (int i)
{
  if (i < 0 || i > cols * rows - 1)
    {
      throw std::out_of_range (RANGE_ERROR);
    }
  return this->matrix[i];
}

float Matrix::operator[] (int i) const
{
  if (i < 0 || i > cols * rows - 1)
    {
      throw std::out_of_range (RANGE_ERROR);
    }
  return this->matrix[i];
}

std::ostream &operator<< (std::ostream &os, const Matrix &m)
{
  for (int i = 0; i < m.get_rows (); i++)
    {
      for (int j = 0; j < m.get_cols (); j++)
        {
          if (m (i, j) > PRINT_RATIO)
            {
              os << "**";
            }
          else
            {
              os << "  ";
            }
        }
      os << std::endl;
    }
  return os;
}

std::istream &operator>> (std::istream &is, const Matrix &m)
{
  Matrix a = m;
  is.read ((char *) m.matrix,
           sizeof (float) * m.get_rows () * m.get_cols ());
  if (!is.good ())
    {
      throw std::runtime_error (ERROR_INPUT);
    }
  return is;
}
