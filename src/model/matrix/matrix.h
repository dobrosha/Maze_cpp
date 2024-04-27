#ifndef SRC_MATRIX_H
#define SRC_MATRIX_H

#include <stdexcept>

/*
Будем использовать матрицу, чтобы сохранять туда количество rows, columns
+ записывать 2 матрицы: с обозначениями правых границ лабиринта (1) и с
обозначениями нижних границ лабиринта (2) Например:

4 4
0 0 0 1
1 0 1 1
0 1 0 1
0 0 0 1

1 0 1 0
0 0 1 0
1 1 0 1
1 1 1 1
*/

namespace s21 {
class Matrix {
 public:
  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix& other);
  ~Matrix();
  int get_rows() { return rows_; }
  int get_cols() { return cols_; }
  Matrix operator=(const Matrix& other);
  bool& operator()(int i, int j);

 private:
  int rows_, cols_;
  bool** matrix_;
  void allocate_matrix(int rows, int cols);
  void destroy_matrix();
  void copy_matrix(bool** other_matrix);
};
bool check_value(const char value);

}  // namespace s21
#endif  // SRC_MATRIX_H
