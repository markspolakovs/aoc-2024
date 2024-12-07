#include "aoc.h"

#include <fstream>
#include <vector>

struct Problem {
  uint64_t answer;
  std::vector<uint64_t> numbers;
};

std::vector<Problem> parse(char *input_path) {
  std::ifstream in(input_path);
  std::vector<Problem> result;

  std::string line;
  while (std::getline(in, line)) {
    if (line.length() == 0)
      continue;
    Problem problem;
    auto colon = line.find(':');
    problem.answer = std::stoull(line.substr(0, colon));

    auto start = colon + 2;
    auto end = line.find(' ', start);
    while (end != std::string::npos) {
      auto val = std::stoull(line.substr(start, end));
      problem.numbers.push_back(val);
      start = end + 1;
      end = line.find(' ', start);
    }
    problem.numbers.push_back(std::stoull(line.substr(start)));

    result.push_back(problem);
  }
  return result;
}

bool match(Problem &problem, int i, uint64_t acc) {
  if (i == problem.numbers.size()) {
    return acc == problem.answer;
  }
  if (acc > problem.answer) {
    // no chance
    return false;
  }
  auto lhs = acc;
  auto rhs = problem.numbers[i];
  auto r1 = match(problem, i + 1, lhs + rhs);
  auto r2 = match(problem, i + 1, lhs * rhs);
  if (PART == 1)
    return r1 || r2;
  auto digits_rhs = floor(log10(rhs)) + 1;
  auto concat = (lhs * pow(10, digits_rhs)) + rhs;
  auto r3 = match(problem, i + 1, concat);
  return r1 || r2 || r3;
}

void solve(char *input_path) {
  auto problem = parse(input_path);
  uint64_t sum_working = 0;
  for (auto p : problem) {
    auto r = match(p, 1, p.numbers[0]);
    if (r) {
      sum_working += p.answer;
    }
  }
  std::printf("%llu\n", sum_working);
}

AOC(solve)
