#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>

bool has_roll(const std::string& line, int index) {
  return index >= 0 && line.length() >= index && line[index] == '@';
}

int rolls_available(std::string& prev, std::string& current, std::string& next, bool remove) {
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

      if (nearby_rolls < 4) {
        available++;

        if (remove)
          current[i] = '.';
      }
    }
  }

  return available;
}

int total_available(std::vector<std::string>& lines, bool remove) {
  std::string blank;
  auto total = rolls_available(blank, lines[0], lines[1], remove);

  for (int i = 1; i < lines.size() - 1; i++)
    total += rolls_available(lines[i - 1], lines[i], lines[i + 1], remove);

  total += rolls_available(lines[lines.size() - 2], lines[lines.size() - 1], blank, remove);

  return total;
}

int total_part1(std::vector<std::string>& lines) {
  return total_available(lines, false);
}

int total_part2(std::vector<std::string>& lines) {
  int prev_total;
  int total{};
  do {
    prev_total = total;
    total += total_available(lines, true);
  } while (prev_total != total);

  return total;
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

    std::vector<std::string> lines;
    std::string line;
    while(std::getline(fin, line)) {
      lines.push_back(line);
    }

    if (lines.size() >= 3) {
      *out << "part1: " << total_part1(lines) << std::endl;
      *out << "part2: " << total_part2(lines) << std::endl;
    }

    return EXIT_SUCCESS;
 } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
