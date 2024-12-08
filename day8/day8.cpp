#include "aoc.h"

#include <fstream>
#include <map>
#include <set>

typedef std::pair<int, int> Coord;

struct Puzzle {
  std::unordered_map<char, std::set<Coord>> nodes;
  int size;
};

Puzzle parse(char *input_path) {
  Puzzle puzzle{.size = 0};
  std::ifstream in(input_path);

  std::string line;
  auto y = 0;
  while (std::getline(in, line)) {
    if (puzzle.size == 0) {
      puzzle.size = line.length();
    }
    for (auto x = 0; x < line.length(); x++) {
      if (line[x] != '.') {
        puzzle.nodes[line[x]].insert({x, y});
      }
    }
    y++;
  }

  return puzzle;
}

int distance(Coord a, Coord b) {
  return abs(a.first - b.first) + abs(a.second - b.second);
}

void print(Puzzle &puzzle, std::set<Coord> &antinodes) {
  for (auto y = 0; y < puzzle.size; y++) {
    for (auto x = 0; x < puzzle.size; x++) {
      Coord coord{x, y};
      if (antinodes.find(coord) != antinodes.end()) {
        std::printf("#");
      } else {
        auto found = false;
        for (auto &it : puzzle.nodes) {
          if (it.second.find(coord) != it.second.end()) {
            std::printf("%c", it.first);
            found = true;
            break;
          }
        }
        if (!found) {
          std::printf(".");
        }
      }
    }
    std::printf("\n");
  }
}

inline bool collinear(Coord a, Coord b, Coord c) {
  return (a.first - b.first) * (a.second - c.second) ==
         (a.first - c.first) * (a.second - b.second);
}

void solve(char *input_path) {
  auto puzzle = parse(input_path);

  std::set<Coord> antinodes;
  for (auto &it0 : puzzle.nodes) {
    if (it0.second.size() < 2)
      continue;
    auto freq = it0.first;
    for (auto n1 : it0.second) {
      for (auto n2 : it0.second) {
        if (n1 == n2)
          continue;
        auto dx = n2.first - n1.first;
        auto dy = n2.second - n1.second;

        auto antinode = std::pair{n1.first + dx * 2, n1.second + dy * 2};
        if (antinode.first >= 0 && antinode.first < puzzle.size &&
            antinode.second >= 0 && antinode.second < puzzle.size) {
          antinodes.insert(antinode);
        }

        antinode = {n1.first - dx, n1.second - dy};
        if (antinode.first >= 0 && antinode.first < puzzle.size &&
            antinode.second >= 0 && antinode.second < puzzle.size) {
          antinodes.insert(antinode);
        }

        if (PART == 2) {
          for (auto y = 0; y < puzzle.size; y++) {
            for (auto x = 0; x < puzzle.size; x++) {
              auto m = std::pair{x, y};
              if (collinear(n1, n2, m)) {
                antinodes.insert(m);
              }
            }
          }
        }
      }
    }
  }

  // print(puzzle, antinodes);
  std::printf("unique antinodes: %zu\n", antinodes.size());
}

AOC(solve)
