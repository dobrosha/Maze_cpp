#include "maze.h"

namespace s21 {
void Maze::set_size(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  allocate_walls();
}

void Maze::allocate_walls() {
  v_walls_ = Matrix(rows_, cols_);
  u_walls_ = Matrix(rows_, cols_);
}

void Maze::set_from_file(std::string filename) {
  file_ = std::ifstream(filename);
  parse_size();
  allocate_walls();
  parse_walls(v_walls_);
  escape_line(file_);
  parse_walls(u_walls_);
}

void Maze::parse_size() {
  std::string line;
  getline(file_, line);
  size_t sub_pos = 0;
  rows_ = std::stoi(line, &sub_pos);
  cols_ = std::stoi(line.substr(sub_pos + 1), &sub_pos);
  if ((rows_ < 0 || rows_ > 50) || (cols_ < 0 || cols_ > 50)) {
    throw std::invalid_argument("Wrong maze size");
  }
}

void Maze::parse_walls(s21::Matrix &matrix) {
  for (int i = 0; i < rows_; i++) {
    std::string line;
    getline(file_, line);
    for (int j = 0, k = 0; j < cols_; j++, k += 2) {
      matrix(i, j) = check_value(line.at(k));
    }
  }
}

inline void escape_line(std::ifstream &myfile) {
  std::string line;
  getline(myfile, line);
}

void Maze::save_maze(std::string filename) {
  std::ofstream file;
  file.open(filename);
  if (file.is_open()) {
    file << rows_ << " " << cols_ << std::endl;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        file << v_walls_(i, j) << " ";
      }
      file << std::endl;
    }
    file << std::endl;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        file << u_walls_(i, j) << " ";
      }
    }
  }
  file.close();
}

}  // namespace s21
