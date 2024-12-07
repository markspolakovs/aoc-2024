#include <cstdio>
#include <fstream>
#include <set>
#include <string>
#include <utility>

#include "aoc.h"
#include <iostream>

typedef std::pair<int, int> Coord;

struct Puzzle {
  int grid_size = 0;
  Coord guard_start;
  std::set<Coord> obstructions;
};

Puzzle parse(char *input_path) {
  Puzzle result;
  std::ifstream in(input_path);

  std::string line;
  auto y = -1;
  while (std::getline(in, line)) {
    y++;
    if (result.grid_size == 0) {
      result.grid_size = line.length();
    }
    for (int x = 0; x < line.length(); x++) {
      auto ch = line[x];
      if (ch == '#') {
        result.obstructions.insert({x, y});
      } else if (ch == '^') {
        result.guard_start = {x, y};
      }
    }
  }

  return result;
}

Coord rotate(Coord dir) {
  auto ret = std::pair(dir);
  if (dir.first == -1) {
    ret.first = 0;
    ret.second = -1;
  } else if (dir.second == -1) {
    ret.second = 0;
    ret.first = 1;
  } else if (dir.first == 1) {
    ret.first = 0;
    ret.second = 1;
  } else if (dir.second == 1) {
    ret.second = 0;
    ret.first = -1;
  }
  return ret;
}

bool would_loop(Puzzle &puzzle, Coord &extra_obstruction) {
  auto guard_pos = std::pair(puzzle.guard_start);
  Coord guard_dir = {0, -1};
  std::set<std::tuple<Coord, Coord>> visited;
  Coord next;

  while (true) {
    visited.insert({guard_pos, guard_dir});
    next = {guard_pos.first + guard_dir.first,
            guard_pos.second + guard_dir.second};
    if (next.first == -1 || next.first == puzzle.grid_size ||
        next.second == -1 || next.second == puzzle.grid_size) {
      return false;
    }
    if ((puzzle.obstructions.find(next) != puzzle.obstructions.end()) ||
        (next == extra_obstruction)) {
      auto old_guard_dir = guard_dir;
      guard_dir = rotate(guard_dir);
      next = {guard_pos.first + guard_dir.first,
              guard_pos.second + guard_dir.second};
      if (visited.find({guard_pos, old_guard_dir}) != visited.end() &&
          visited.find({next, guard_dir}) != visited.end()) {
        return true;
      }
    } else {
      guard_pos = next;
    }
  }
}

void solve(char *input_path) {
  auto puzzle = parse(input_path);

  auto guard_pos = std::pair(puzzle.guard_start);
  Coord guard_dir = {0, -1};
  std::set<Coord> visited;
  Coord next;
  if (PART == 1) {
    while (true) {
      visited.insert(guard_pos);

      next = {guard_pos.first + guard_dir.first,
              guard_pos.second + guard_dir.second};
      if (next.first == -1 || next.first == puzzle.grid_size ||
          next.second == -1 || next.second == puzzle.grid_size) {
        break;
      }
      if (puzzle.obstructions.find(next) != puzzle.obstructions.end()) {
        guard_dir = rotate(guard_dir);
      } else {
        guard_pos = next;
      }
    }

    std::printf("unique visited: %zu\n", visited.size());
  } else {
    std::set<Coord> loop_obstruction_spots;

    auto total = puzzle.grid_size * puzzle.grid_size;
    auto done = 0;
    for (int y = 0; y < puzzle.grid_size; y++) {
      for (int x = 0; x < puzzle.grid_size; x++) {
        done++;
        if ((done % 100) == 0 && done > 0) {
          std::printf("progress: %d/%d\n", done, total);
        }
        auto obs = std::pair{x, y};
        if (obs == puzzle.guard_start ||
            puzzle.obstructions.find(obs) != puzzle.obstructions.end()) {
          continue;
        }
        if (would_loop(puzzle, obs)) {
          loop_obstruction_spots.insert(obs);
        }
      }
    }

    std::printf("obstruction spots: %zu\n", loop_obstruction_spots.size());
    // for (auto spot : loop_obstruction_spots) {
    //   std::printf("\t%dx%d\n", spot.first, spot.second);
    // }
  }
}

AOC(solve)
