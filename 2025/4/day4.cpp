#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

bool has_roll(const std::string& line, int index) {
  return index >= 0 && line.length() >= index && line[index] == '@';
}

int rolls_available(const std::string& prev, const std::string& current, const std::string& next) {
  int available{};
  for (int i = 0; i < current.length(); i++) {
    if (has_roll(current, i)) {
      int nearby_rolls{};

      if (has_roll(prev, i))        // N
        nearby_rolls++;
      if (has_roll(prev, i + 1))    // NE
        nearby_rolls++;
      if (has_roll(current, i + 1)) // E
        nearby_rolls++;
      if (has_roll(next, i + 1))    // SE
        nearby_rolls++;
      if (has_roll(next, i))        // S
        nearby_rolls++;
      if (has_roll(next, i - 1))    // SW
        nearby_rolls++;
      if (has_roll(current, i - 1)) // W
        nearby_rolls++;
      if (has_roll(prev, i - 1))    // NW
        nearby_rolls++;

      if (nearby_rolls < 4)
        available++;
    }
  }

  return available;
}

int main(int argc, char** argv) {
  assert(argc >= 2);

  try {
    std::ifstream fin;
    fin.exceptions(std::ifstream::badbit);
    fin.open(argv[1]);

    std::ostream* out = &std::cout;
    std::ofstream fout;
    if (argc == 3) {
      fout.exceptions(std::ifstream::badbit);
      fout.open(argv[2]);

      out = &fout;
    }

    int total{};
    std::string prev, current, next;

    bool first = true;
    bool last = false;
    do {
      if (first) {
        first = false;
        if (!std::getline(fin, current)) break;
        if (!std::getline(fin, next)) break;
      } else {
        prev = current;
        current = next;

        if (!std::getline(fin, next)) {
          next = {};
          last = true;
        }
      }

      auto rolls = rolls_available(prev, current, next);
      *out << rolls << std::endl;
      total += rolls;

    } while (!last);

    *out << "part1: " << total << std::endl;

    return EXIT_SUCCESS;
 } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
