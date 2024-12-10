#include "aoc.h"

#include <map>
#include <set>
#include <fstream>

typedef std::pair<int, int> Coord;
struct Puzzle {
  int size = 0;
  std::map<Coord, int> nodes;
};

Puzzle parse(char* path) {
  Puzzle result;
  std::ifstream fd(path);
  std::string line;
  auto y = 0;
  while (std::getline(fd, line)) {
    if (result.size == 0) {
      result.size = line.length();
    }
    auto x = 0;
    for (auto c : line) {
      result.nodes[{x,y}] = std::stoi(std::string(1, c));
      x++;
    }
    y++;
  }
  return result;
}

int count_trailheads(Puzzle& puzzle, Coord start, int progress, std::set<Coord>& visited) {
  if (puzzle.nodes[start] == 9) {
    if (PART == 1) {
      if (visited.contains(start)) {
        return 0;
      }
    }
    visited.insert(start);
    return 1;
  }
  auto result = 0;
  for (auto delta : std::vector<Coord>{{0,1},{0,-1},{1,0},{-1,0}}) {
    Coord coord = {start.first+delta.first, start.second+delta.second};
    if (
      coord.first < 0 || coord.second < 0 ||
      coord.first >= puzzle.size || coord.second >= puzzle.size
    ) {
      continue;
    }
    if (puzzle.nodes[coord] != progress + 1) {
      continue;
    }
    result += count_trailheads(puzzle, coord, progress + 1, visited);
  }
  return result;
}

void solve(char* path) {
  auto puzzle = parse(path);
  auto sum = 0;
  for (auto& [coord, value] : puzzle.nodes) {
    if (value == 0) {
      auto visited = std::set<Coord>{};
      auto count = count_trailheads(puzzle, coord, 0, visited);
      sum += count;
    }
  }
  std::printf("%d\n", sum);
}
AOC(solve)
