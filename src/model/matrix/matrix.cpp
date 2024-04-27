#include "matrix.h"

namespace s21 {

Matrix::Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

Matrix::Matrix(int rows, int cols) { allocate_matrix(rows, cols); }

Matrix::Matrix(const s21::Matrix &other) : Matrix(other.rows_, other.cols_) {
  copy_matrix(other.matrix_);
}

Matrix::~Matrix() { destroy_matrix(); }

Matrix Matrix::operator=(const s21::Matrix &other) {
  if (this != &other) {
    destroy_matrix();
    allocate_matrix(other.rows_, other.cols_);
    copy_matrix(other.matrix_);
  }
  return *this;
}

bool &Matrix::operator()(int i, int j) { return matrix_[i][j]; }

void Matrix::allocate_matrix(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  matrix_ = new bool *[rows];
  for (int i = 0; i < rows; i++) {
    matrix_[i] = new bool[cols]();
  }
}

void Matrix::copy_matrix(bool **other_matrix) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other_matrix[i][j];
    }
  }
}

void Matrix::destroy_matrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

bool check_value(const char value) {
  if (value != '0' && value != '1') {
    throw std::invalid_argument("Incorrect value");
  }
  return value == '1';
}

}  // namespace s21