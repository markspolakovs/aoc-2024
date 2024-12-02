#include <cstdio>
#include <fstream>
#include <sstream>

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

bool is_safe_part1(std::vector<int> report) {
  auto direction = 0;
  auto last = 0;
  for (auto val = report.begin(); val != report.end(); val++) {
    auto delta = *val - last;
    if (direction == 0) {
      if (last == 0) {
        last = *val;
        continue;
      }
      direction = sgn(delta);
    }
    if (abs(delta) < 1 || abs(delta) > 3) {
      return false;
    }
    if (sgn(delta) != direction) {
      return false;
    }
    last = *val;
  }
  return true;
}

bool is_safe_part2(std::vector<int> report) {
  if (is_safe_part1(report)) {
    return true;
  }
  for (auto i = 0; i < report.size(); i++) {
    std::vector<int> vec(report);
    vec.erase(vec.begin() + i);
    if (is_safe_part1(vec)) {
      return true;
    }
  }
  return false;
}

void solve_part1(char* input) {
  auto total_safe = 0;
  std::ifstream fd(input);
  std::string str;
  while (std::getline(fd, str)) {
    std::vector<int> vec;
    std::istringstream stream(str);
    std::istream_iterator<std::string> begin(stream), end;
    for (auto it = begin; it != end; it++) {
      vec.push_back(std::stoi(*it));
    }
    if (is_safe_part1(vec))
      total_safe++;
  }

  std::printf("safe: %d\n", total_safe);
}

void solve_part2(char* input) {
  auto total_safe = 0;
  std::ifstream fd(input);
  std::string str;
  while (std::getline(fd, str)) {
    std::vector<int> vec;
    std::istringstream stream(str);
    std::istream_iterator<std::string> begin(stream), end;
    for (auto it = begin; it != end; it++) {
      vec.push_back(std::stoi(*it));
    }
    if (is_safe_part2(vec))
      total_safe++;
  }

  std::printf("safe: %d\n", total_safe);
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    std::fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
    return 1;
  }

  // solve_part1(argv[1]);
  solve_part2(argv[1]);

  return 0;
}
