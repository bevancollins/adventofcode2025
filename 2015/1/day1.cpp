#include <iostream>
#include <fstream>
#include <cassert>

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

    int floor{};
    int pos_of_first_basement{};
    int pos{};
    char c;
    while (fin >> c) {
      pos++;
      if (c == '(')
        floor++;
      else if (c == ')')
        floor--;

      if (pos_of_first_basement == 0 && floor == -1)
        pos_of_first_basement = pos;
    }

    *out
      << "part 1: " << floor << std::endl
      << "part 2: " << pos_of_first_basement << std::endl;
    return EXIT_SUCCESS;
 } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
