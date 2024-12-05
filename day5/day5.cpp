#include <algorithm>
#include <fstream>
#include <map>
#include <stdexcept>
#include <vector>

#include "aoc.h"

struct Puzzle {
  std::multimap<int, int> order_rules;
  std::vector<std::vector<int>> updates;
};

Puzzle parse(char *input_file_path) {
  Puzzle ret;
  std::ifstream stream(input_file_path);

  std::string line;
  while (std::getline(stream, line) && line != "") {
    auto sep_idx = line.find("|");
    auto lhs = std::stoi(line.substr(0, sep_idx));
    auto rhs = std::stoi(line.substr(sep_idx + 1));
    ret.order_rules.insert({lhs, rhs});
  }

  while (std::getline(stream, line) && line != "") {
    std::vector<int> rule;

    auto start = 0;
    auto end = line.find(',');
    while (end != std::string::npos) {
      auto num = line.substr(start, end - start);
      rule.push_back(std::stoi(num));
      start = end + 1;
      end = line.find(',', start);
    }
    rule.push_back(std::stoi(line.substr(start)));

    if (rule.size() % 2 == 0) {
      throw std::logic_error(
          std::format("line '{}' parsed had even length", line));
    }

    ret.updates.push_back(rule);
  }
  return ret;
}

bool is_correctly_ordered(Puzzle &puzzle, std::vector<int> &line) {
  for (auto i = 0; i < line.size(); i++) {
    auto pivot = line[i];
    for (auto [mba_start, mba_end] = puzzle.order_rules.equal_range(pivot);
         mba_start != mba_end; mba_start++) {
      auto mba = (*mba_start).second;
      auto it = std::find(line.begin(), line.end(), mba);
      if (it != line.end()) {
        auto real_idx = it - line.begin();
        if (real_idx < i) {
          return false;
        }
      }
    }
  }
  return true;
}

void fix(Puzzle &puzzle, std::vector<int> &line) {
check:
  while (!is_correctly_ordered(puzzle, line)) {
    for (auto i = 0; i < line.size(); i++) {
      auto pivot = line[i];
      for (auto [mba_start, mba_end] = puzzle.order_rules.equal_range(pivot);
           mba_start != mba_end; mba_start++) {
        auto mba = (*mba_start).second;
        auto it = std::find(line.begin(), line.end(), mba);
        if (it != line.end()) {
          auto real_idx = it - line.begin();
          if (real_idx < i) {
            line[i] = mba;
            line[real_idx] = pivot;
            goto check;
          }
        }
      }
    }
  }
}

void solve_day5(char *input_file_path) {
  auto puzzle = parse(input_file_path);

  if (PART == 1) {

    auto sum_of_middle_entries_of_correct = 0;
    for (auto line : puzzle.updates) {
      if (is_correctly_ordered(puzzle, line)) {
        auto middle = line[line.size() / 2];
        sum_of_middle_entries_of_correct += middle;
      }
    }

    std::printf("result (part 1): %d\n", sum_of_middle_entries_of_correct);

  } else {
    auto sum_of_middle_entries_of_incorrect = 0;

    for (auto line : puzzle.updates) {
      if (!is_correctly_ordered(puzzle, line)) {
        fix(puzzle, line);
        auto middle = line[line.size() / 2];
        sum_of_middle_entries_of_incorrect += middle;
      }
    }

    std::printf("result (part 2): %d\n", sum_of_middle_entries_of_incorrect);
  }
}

AOC(solve_day5)
