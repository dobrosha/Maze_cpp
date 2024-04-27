#ifndef SRC_MAZE_H
#define SRC_MAZE_H

#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "./matrix/matrix.h"

namespace s21 {

// constexpr?
const int kEmpty = 0;

class Maze {
 private:
  Matrix v_walls_, u_walls_;
  int rows_ = 0, cols_ = 0;
  std::ifstream file_;
  std::vector<int> line_;
  int counter_ = 1;

 public:
  void set_size(int rows, int cols);
  int get_rows() { return rows_; }
  int get_cols() { return cols_; }
  void set_from_file(std::string filename);
  Matrix& get_vertical_walls() { return v_walls_; }
  Matrix& get_under_walls() { return u_walls_; }
  void generate_maze();
  void save_maze(std::string filename);

 private:
  void allocate_walls();
  void parse_size();
  void parse_walls(Matrix& matrix);
  void fill_empty_value();
  void assign_unique_set();
  void add_vertical_walls(int row);
  void merge_set(int index, int element);
  int calculate_unique_set(int element);
  int calculate_under_walls(int element, int row);
  void checked_under_walls(int row);
  void add_under_walls(int row);
  void prepare_new_line(int row);
  void add_end_line();
  void checked_end_line();
  void clear();
};

inline void escape_line(std::ifstream& myfile);

}  // namespace s21

#endif  // SRC_MAZE_H
