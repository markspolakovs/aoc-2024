# Advent of Code 2024 in C++

Running:

```sh
$ cmake -S . -B build -G Ninja
$ cmake --build build
$ build/dayX/dayX path/to/input.txt
```

Adding a new day: create a folder `dayxx`, and in it place a CMakeLists like

```cmake
add_executable(dayXX dayXX.cpp ${HEADER_FILES})
```

and a `dayXX.cpp` that looks something like

```cpp
#include "aoc.h"

void solve_dayXX(char *input_file_path) {
  if (PART == 1) {
    // solve part 2
  } else {
    // solve part 2
  }
}

AOC(solve_dayXX)
```

Then you can run it with `PART=1 build/dayXX/dayXX path/to/input.txt` or `PART=2`.

## Why C++?

I know some C, but very little C++, especially not the "modern" flavour. Given I occasionally work with C++ code at work I thought this would be a good opportunity to learn more of the language.
