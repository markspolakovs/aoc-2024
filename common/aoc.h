#pragma once
#include <functional>

typedef void (*aoc_real_main)(char *);

int PART;

int _aoc_main(int argc, char *argv[], aoc_real_main real_main) {
  if (argc == 1) {
    std::fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
    return 1;
  }

  auto part_env_r = getenv("PART");
  if (part_env_r != nullptr) {
    auto part_env = std::string(part_env_r);
    if (part_env == "1") {
      PART = 1;
    } else if (part_env == "2") {
      PART = 2;
    } else {
      std::fprintf(stderr, "Invalid PART, must be 1 or 2\n");
      return 1;
    }
  } else {
    PART = 1;
  }

  (*real_main)(argv[1]);
  return 0;
}

#define AOC(real_main)                                                         \
  int main(int argc, char *argv[]) { return _aoc_main(argc, argv, real_main); }
