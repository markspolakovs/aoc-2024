#include <cstdio>
#include <fstream>
#include <regex>
#include <iostream>

void solve_part1(char* path) {
  std::ifstream fd(path);
  std::string content((std::istreambuf_iterator<char>(fd)), std::istreambuf_iterator<char>());
  std::regex mul_re("mul\\(([0-9]+),([0-9]+)\\)");

  std::sregex_iterator it(content.begin(), content.end(), mul_re);

  auto sum = 0;
  for (decltype(it) last; it != last; it++) {
    auto match = *it;
    auto lhs = std::stoi(match[1]);
    auto rhs = std::stoi(match[2]);
    sum += (lhs * rhs);
  }

  std::printf("sum: %d\n", sum);
}

void solve_part2(char* path) {
  std::ifstream fd(path);
  std::string content((std::istreambuf_iterator<char>(fd)), std::istreambuf_iterator<char>());
  std::regex mul_re("(?:do\\(\\)|don't\\(\\)|mul\\(([0-9]+),([0-9]+)\\))");

  std::sregex_iterator it(content.begin(), content.end(), mul_re);

  auto sum = 0;
  bool enabled = true;
  for (decltype(it) last; it != last; it++) {
    auto match = *it;
    if (match.str().rfind("don't", 0) == 0) {
      enabled = false;
    } else if (match.str().rfind("do", 0) == 0) {
      enabled = true;
    } else if (enabled) {
      auto lhs = std::stoi(match[1]);
      auto rhs = std::stoi(match[2]);
      sum += (lhs * rhs);
    }
  }

  std::printf("sum: %d\n", sum);
}

constexpr int part = 2;

int main(int argc, char* argv[]) {
  if (argc == 1) {
    std::fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
    return 1;
  }

  if (part == 1) {
    solve_part1(argv[1]);
  } else {
    solve_part2(argv[1]);
  }

  return 0;
}
