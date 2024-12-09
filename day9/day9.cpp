#include "aoc.h"

#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

int findLastBlockIdx(std::vector<int> &blocks, int start) {
  for (auto i = blocks.size() - 1; i >= start; i--) {
    if (blocks[i] != -1) {
      return i;
    }
  }
  return -1;
}

struct Block {
  int id;
  uint size;
};

void solve(char *input_path) {
  std::ifstream in(input_path);
  std::string line;

  if (PART == 1) {
    std::vector<int> blocks;
    while (std::getline(in, line)) {
      blocks.reserve(line.size());
      auto is_block = true;
      auto id = 0;
      for (auto &c : line) {
        auto len = std::stoi(std::string(1, c));
        for (auto i = 0; i < len; i++) {
          if (is_block) {
            blocks.push_back(id);
          } else {
            blocks.push_back(-1);
          }
        }
        if (is_block)
          id++;
        is_block = !is_block;
      }
    }

    for (auto i = 0; i < blocks.size(); i++) {
      if (blocks[i] == -1) {
        auto last = findLastBlockIdx(blocks, i);
        if (last == -1)
          break;
        blocks[i] = blocks[last];
        blocks[last] = -1;
      }
    }

    uint64_t checksum = 0;
    for (auto i = 0; i < blocks.size(); i++) {
      if (blocks[i] == -1)
        continue;
      checksum += (i * blocks[i]);
    }
    std::printf("%llu\n", checksum);
  } else {
    std::list<Block> blocks;

    while (std::getline(in, line)) {
      auto is_block = true;
      int id = 0;
      for (auto &c : line) {
        auto len = std::stoul(std::string(1, c));
        if (is_block) {
          blocks.push_back(Block{.id = id, .size = static_cast<uint>(len)});
        } else {
          blocks.push_back(Block{.id = -1, .size = static_cast<uint>(len)});
        }
        if (is_block)
          id++;
        is_block = !is_block;
      }
    }

    auto max_id = blocks.back().id;
    for (auto id = max_id; id >= 0; id--) {
      auto block = std::find_if(blocks.rbegin(), blocks.rend(),
                                [id](auto &b) { return b.id == id; });
      if (block == blocks.rend())
        continue;
      auto block_pos =
          std::find_if(blocks.begin(), blocks.end(),
                       [block](auto &b) { return b.id == block->id; });
      auto space = std::find_if(blocks.begin(), blocks.end(), [block](auto &b) {
        return b.id == -1 && b.size >= block->size;
      });
      if (space == blocks.end())
        continue;
      auto block_offset = std::distance(blocks.begin(), block_pos);
      auto space_offset = std::distance(blocks.begin(), space);
      if (block_offset < space_offset)
        continue;
      auto leftover = space->size - block->size;
      space->id = id;
      space->size = block->size;
      auto next = std::next(space, 1);
      if (next != blocks.end() && next->id == -1) {
        next->size += leftover;
      } else {
        blocks.insert(next, {-1, leftover});
      }
      block->id = -1;
    }

    uint64_t checksum = 0;
    auto i = 0;
    for (auto &b : blocks) {
      if (b.id == -1) {
        i += b.size;
        continue;
      }
      for (auto j = 0; j < b.size; j++) {
        checksum += (i * b.id);
        i++;
      }
    }
    std::printf("%llu\n", checksum);
  }
}
AOC(solve)
