#include <cstdio>
#include <fstream>

#include "aoc.h"

constexpr auto XMAS = "XMAS";

bool find_xmas(std::vector<std::vector<char>> &grid, std::pair<int, int> oc,
               std::pair<int, int> delta, int progress) {
  auto x = oc.first + delta.first;
  auto y = oc.second + delta.second;
  if (x < 0 || x >= grid.size() || y < 0 || y >= grid.size()) {
    return false;
  }
  auto search = XMAS[progress + 1];
  auto ch = grid[x][y];
  if (ch != search) {
    return false;
  }
  if (progress == 2) {
    return true;
  }
  return find_xmas(grid, {x, y}, delta, progress + 1);
}

bool find_cross_mas(std::vector<std::vector<char>> &grid,
                    std::pair<int, int> oc) {
  auto [x, y] = oc;
  if (grid[x][y] != 'A')
    return false;
  auto ch1 = grid[x - 1][y - 1];
  auto ch2 = grid[x + 1][y - 1];
  auto ch3 = grid[x + 1][y + 1];
  auto ch4 = grid[x - 1][y + 1];
  if ((ch1 == 'M' && ch3 == 'S') || (ch1 == 'S' && ch3 == 'M')) {
    if ((ch2 == 'M' && ch4 == 'S') || (ch2 == 'S' && ch4 == 'M')) {
      return true;
    }
  }
  return false;
}

void solve(char *input_path) {
  std::ifstream fd(input_path);
  std::vector<std::vector<char>> grid;

  std::string line;
  auto lineno = 0;
  while (std::getline(fd, line)) {
    if (lineno == 0) {
      grid.resize(line.length());
    }
    grid[lineno].resize(line.length());
    for (auto i = 0; i < line.size(); i++) {
      grid[lineno][i] = line[i];
    }
    lineno++;
  }

  auto xmas = 0;
  if (PART == 1) {
    for (auto x = 0; x < grid.size(); x++) {
      for (auto y = 0; y < grid.size(); y++) {
        if (grid[x][y] == 'X') {
          for (auto dx = -1; dx <= 1; dx++) {
            for (auto dy = -1; dy <= 1; dy++) {
              if (dx == 0 && dy == 0)
                continue;
              if (find_xmas(grid, {x, y}, {dx, dy}, 0)) {
                xmas++;
              }
            }
          }
        }
      }
    }
  } else {
    for (auto x = 1; x < grid.size() - 1; x++) {
      for (auto y = 1; y < grid.size() - 1; y++) {
        if (find_cross_mas(grid, {x, y}))
          xmas++;
      }
    }
  }

  printf("xmas: %d\n", xmas);
}

AOC(solve)
