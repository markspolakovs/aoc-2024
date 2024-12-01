#include <utility>
#include <string>
#include <fstream>
#include <map>

std::pair<std::vector<int>, std::vector<int>> read_input(std::string path) {
  std::ifstream fd(path);
  std::vector<int> left, right;

  std::string str;
  int lhs, rhs;
  while (std::getline(fd, str)) {
    auto space = str.find(' ');
    lhs = std::stoi(str.substr(0, space));
    rhs = std::stoi(str.substr(space + 1));
    left.push_back(lhs);
    right.push_back(rhs);
  }

  return { left, right };
}

int main(int argc, char* argv[]) {
  if (argc == 0) {
    std::fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
    return 1;
  }
  auto [lhs, rhs] = read_input(std::string(argv[1]));

  std::printf("lhs: %d, rhs: %d\n", lhs.size(), rhs.size());

  std::map<int, int> times_in_rhs;
  for (auto it : rhs) {
    times_in_rhs[it]++;
  }

  auto total_similarity = 0;
  for (auto it : lhs) {
    auto times = times_in_rhs[it];
    total_similarity += (it * times);
  }

  std::printf("similarity: %d\n", total_similarity);

  return 0;
}
