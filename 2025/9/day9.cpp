#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>

struct Coordinate {
  long long x{};
  long long y{};
};

std::vector<Coordinate> import_coordinates(std::istream& in) {
  std::vector<Coordinate> coordinates;
  std::string x_str, y_str;
  while (std::getline(in, x_str, ',') && std::getline(in, y_str)) {
    coordinates.emplace_back(std::stoll(x_str), std::stoll(y_str));
  }

  return coordinates;
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

    auto coordinates = import_coordinates(fin);

    long long largest_area{};
    for (int i = 0; i < coordinates.size(); i++) {
      for (int j = i + 1; j < coordinates.size(); j++) {
        auto area = (std::abs(coordinates[i].x - coordinates[j].x) + 1) * (std::abs(coordinates[i].y - coordinates[j].y) + 1);
        largest_area = std::max(area, largest_area);
      }
    }

    *out
      << largest_area << std::endl;

    return EXIT_SUCCESS;
 } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
