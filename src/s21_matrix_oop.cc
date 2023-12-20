#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  this->cols_ = other.cols();
  this->rows_ = other.rows();

  matrix_ = new double*[this->rows_];
  for (int i = 0; i < this->rows_; i++) {
    matrix_[i] = new double[this->cols_];
  }

  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::set_cols(int cols) {
  if (cols < 0) {
    throw std::invalid_argument("Columns cannot be negative");
  }

  if (cols_ == cols) {
    return;
  } else if (cols_ < cols) {
    double** new_matrix = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
      new_matrix[i] = new double[cols];
      for (int j = 0; j < cols_; j++) {
        new_matrix[i][j] = matrix_[i][j];
      }
      for (int j = cols_; j < cols; j++) {
        new_matrix[i][j] = 0.0;
      }
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = new_matrix;
    cols_ = cols;
  } else {
    double** new_matrix = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
      new_matrix[i] = new double[cols];
      for (int j = 0; j < cols; j++) {
        new_matrix[i][j] = matrix_[i][j];
      }
    }
    for (int i = 0; i < rows_; i++) {
      for (int j = cols; j < cols_; j++) {
        delete[] matrix_[i];
      }
    }
    delete[] matrix_;
    matrix_ = new_matrix;
    cols_ = cols;
  }
}

void S21Matrix::set_rows(int rows) {
  if (rows < 0) {
    throw std::invalid_argument("Rows cannot be negative");
  }

  if (rows_ == rows) {
    return;
  } else if (rows_ < rows) {
    double** new_matrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
      new_matrix[i] = new double[cols_];
    }
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        new_matrix[i][j] = matrix_[i][j];
      }
      delete[] matrix_[i];
    }
    for (int i = rows_; i < rows; i++) {
      for (int j = 0; j < cols_; j++) {
        new_matrix[i][j] = 0.0;
      }
    }
    delete[] matrix_;
    matrix_ = new_matrix;
    rows_ = rows;
  } else {
    double** new_matrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
      new_matrix[i] = new double[cols_];
    }
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols_; j++) {
        new_matrix[i][j] = matrix_[i][j];
      }
    }
    for (int i = rows; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = new_matrix;
    rows_ = rows;
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = other.matrix_;

  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if (this->cols_ != other.cols_ || this->rows_ != other.rows_) {
    return false;
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (this->matrix_[i][j] != other.matrix_[i][j]) {
        return false;
      }
    }
  }

  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::runtime_error("Dimensions of matrices do not match.");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::runtime_error("Dimensions of matrices do not match.");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (this->cols_ != other.rows_) {
    throw std::runtime_error(
        "Number of columns in the first matrix should match number of rows in "
        "the second matrix.");
  }

  S21Matrix result(this->rows_, other.cols_);

  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result.matrix_[i][j] = 0.0;
      for (int k = 0; k < this->cols_; k++) {
        result.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  *this = S21Matrix(result);
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix transposed(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      transposed.matrix_[j][i] = matrix_[i][j];
    }
  }
  return transposed;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::runtime_error("Matrix must be square to calculate complements.");
  }

  S21Matrix complements(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      complements.matrix_[i][j] =
          pow(-1, i + j) * this->Minor(i, j).Determinant();
    }
  }
  return complements;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::runtime_error("Matrix must be square to calculate determinant.");
  }

  if (rows_ == 1) {
    return matrix_[0][0];
  }

  if (rows_ == 2) {
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  }

  double det = 0.0;
  for (int j = 0; j < cols_; j++) {
    det += matrix_[0][j] * pow(-1, j) * this->Minor(0, j).Determinant();
  }
  return det;
}

S21Matrix S21Matrix::Minor(int row, int col) {
  S21Matrix minorMat(rows_ - 1, cols_ - 1);
  int x = 0, y = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (i != row && j != col) {
        minorMat.matrix_[x][y] = matrix_[i][j];
        y++;
        if (y == cols_ - 1) {
          y = 0;
          x++;
        }
      }
    }
  }
  return minorMat;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw std::runtime_error("Matrix must be square to calculate its inverse.");
  }

  double det = this->Determinant();

  S21Matrix complements = this->CalcComplements();
  S21Matrix transposedComplements = complements.Transpose();

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      transposedComplements.matrix_[i][j] /= det;
    }
  }

  return transposedComplements;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  if (this->cols_ != other.rows_) {
    throw std::runtime_error(
        "Number of columns in the first matrix should match number of rows in "
        "the second matrix.");
  }

  S21Matrix result(rows(), cols());
  for (int i = 0; i < this->rows(); i++) {
    for (int j = 0; j < this->cols(); j++) {
      result.matrix_[i][j] = this->matrix_[i][j] + other.matrix_[i][j];
    }
  }

  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  if (this->cols_ != other.rows_) {
    throw std::runtime_error(
        "Number of columns in the first matrix should match number of rows in "
        "the second matrix.");
  }

  S21Matrix result(rows(), cols());
  for (int i = 0; i < this->rows(); i++) {
    for (int j = 0; j < this->cols(); j++) {
      result.matrix_[i][j] = this->matrix_[i][j] - other.matrix_[i][j];
    }
  }

  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  if (this->cols_ != other.rows_) {
    throw std::runtime_error(
        "Number of columns in the first matrix should match number of rows in "
        "the second matrix.");
  }

  S21Matrix result(this->rows_, other.cols_);

  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result.matrix_[i][j] = 0;
      for (int k = 0; k < this->cols_; k++) {
        result.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  return result;
}

S21Matrix S21Matrix::operator*(int num) {
  S21Matrix result(rows(), cols());

  for (int i = 0; i < this->rows(); i++) {
    for (int j = 0; j < this->cols(); j++) {
      result.matrix_[i][j] = this->matrix_[i][j] * num;
    }
  }

  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) {
  if (this->cols_ != other.rows_) {
    return false;
  }

  for (int i = 0; i < this->rows(); i++) {
    for (int j = 0; j < this->cols(); j++) {
      if (this->matrix_[i][j] != other.matrix_[i][j]) {
        return false;
      }
    }
  }
  return true;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this == &other) {
    return *this;
  }

  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;

  rows_ = other.rows_;
  cols_ = other.cols_;

  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }

  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  if (this->cols_ != other.rows_) {
    throw std::runtime_error(
        "Number of columns in the first matrix should match number of rows in "
        "the second matrix.");
  }

  for (int i = 0; i < this->rows(); i++) {
    for (int j = 0; j < this->cols(); j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }

  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  if (this->cols_ != other.rows_) {
    throw std::runtime_error(
        "Number of columns in the first matrix should match number of rows in "
        "the second matrix.");
  }

  for (int i = 0; i < this->rows(); i++) {
    for (int j = 0; j < this->cols(); j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }

  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  if (this->cols_ != other.rows_) {
    throw std::runtime_error(
        "Number of columns in the first matrix should match the number of rows "
        "in the second matrix for matrix multiplication.");
  }

  S21Matrix result(this->rows_, other.cols_);

  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result.matrix_[i][j] = 0;

      for (int k = 0; k < this->cols_; k++) {
        result.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  *this = result;

  return *this;
}

double& S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || row < 0 || col >= cols_ || col < 0) {
    throw std::runtime_error("Index is out of range");
  }

  return matrix_[row][col];
}
