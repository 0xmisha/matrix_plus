#ifndef S21_MATRIX_H_
#define S21_MATRIX_H_

#include <cmath>
#include <stdexcept>

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(S21Matrix&& other);
  S21Matrix(const S21Matrix& other);
  ~S21Matrix();

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);

  int rows() const { return rows_; };
  int cols() const { return cols_; };
  void set_rows(int rows);
  void set_cols(int cols);

  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix Minor(int row, int col);
  S21Matrix InverseMatrix();

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(int num);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  double& operator()(int row, int col);

 private:
  int rows_, cols_;
  double** matrix_;
};

#endif  // S21_MATRIX_H_