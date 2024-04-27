#include "maze.h"

namespace s21 {

bool random_bool() {
  std::random_device rd;
  std::default_random_engine engine(rd());
  std::uniform_int_distribution<int> dist(0, 1);
  return static_cast<bool>(dist(engine));
}

void Maze::clear() {
  line_.clear();
  counter_ = 1;
}

void Maze::fill_empty_value() {
  for (int i = 0; i < cols_; i++) {
    line_.push_back(kEmpty);
  }
}

void Maze::assign_unique_set() {
  for (int i = 0; i < cols_; i++) {
    if (line_[i] == kEmpty) {
      line_[i] = counter_;
      counter_++;
    }
  }
}

void Maze::merge_set(int index, int element) {
  int mutableSet = line_[index + 1];
  for (int j = 0; j < cols_; j++) {
    if (line_[j] == mutableSet) {
      line_[j] = element;
    }
  }
}

void Maze::add_vertical_walls(int row) {
  for (int i = 0; i < cols_ - 1; i++) {
    bool choise = random_bool();
    if (choise == true || line_[i] == line_[i + 1]) {
      v_walls_(row, i) = true;
    } else {
      merge_set(i, line_[i]);
    }
  }
  v_walls_(row, cols_ - 1) = true;
}

int Maze::calculate_unique_set(int element) {
  int countUniqSet = 0;
  for (int i = 0; i < cols_; i++) {
    if (line_[i] == element) {
      countUniqSet++;
    }
  }
  return countUniqSet;
}

void Maze::add_under_walls(int row) {
  for (int i = 0; i < cols_; i++) {
    bool choise = random_bool();
    if (calculate_unique_set(line_[i]) != 1 && choise == true) {
      u_walls_(row, i) = true;
    }
  }
}

int Maze::calculate_under_walls(int element, int row) {
  int countHorizontalWalls = 0;
  for (int i = 0; i < cols_; i++) {
    if (line_[i] == element && u_walls_(row, i) == false) {
      countHorizontalWalls++;
    }
  }
  return countHorizontalWalls;
}

void Maze::checked_under_walls(int row) {
  for (int i = 0; i < cols_; i++) {
    if (calculate_under_walls(line_[i], row) == 0) {
      u_walls_(row, i) = false;
    }
  }
}

void Maze::prepare_new_line(int row) {
  for (int i = 0; i < cols_; i++) {
    if (u_walls_(row, i) == true) {
      line_[i] = kEmpty;
    }
  }
}

void Maze::checked_end_line() {
  for (int i = 0; i < cols_ - 1; i++) {
    if (line_[i] != line_[i + 1]) {
      v_walls_(rows_ - 1, i) = false;
      merge_set(i, line_[i]);
    }
    u_walls_(rows_ - 1, i) = true;
  }
  u_walls_(rows_ - 1, cols_ - 1) = true;
}

void Maze::add_end_line() {
  assign_unique_set();
  add_vertical_walls(rows_ - 1);
  checked_end_line();
}

void Maze::generate_maze() {
  fill_empty_value();
  for (int j = 0; j < rows_ - 1; j++) {
    assign_unique_set();
    add_vertical_walls(j);
    add_under_walls(j);
    checked_under_walls(j);
    prepare_new_line(j);
  }
  add_end_line();
  clear();
}

}  // namespace s21
