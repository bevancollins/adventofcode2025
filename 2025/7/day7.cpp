#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <memory>


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

    std::string line;
    std::getline(fin, line);
    assert(!line.empty());

    auto width = line.length();
    auto quantum_tachyon_manifold = std::make_unique<long long[]>(width);
    auto pos = line.find('S');
    assert(pos != std::string::npos);
    quantum_tachyon_manifold[pos] = 1;

    int split_count{};

    while(std::getline(fin, line)) {
      int splitter_pos{-1};
      for(;;) {
        splitter_pos = line.find('^', splitter_pos + 1);
        assert(splitter_pos == std::string::npos || splitter_pos < width - 1);
        if (splitter_pos == std::string::npos) {
          break;
        } else if (quantum_tachyon_manifold[splitter_pos] != 0) {
          split_count++;

          quantum_tachyon_manifold[splitter_pos - 1] += quantum_tachyon_manifold[splitter_pos];
          quantum_tachyon_manifold[splitter_pos + 1] += quantum_tachyon_manifold[splitter_pos];
          quantum_tachyon_manifold[splitter_pos] = 0;
        }
      }
    }

    long long timelines{};
    for (int i = 0; i < width; i++)
      timelines += quantum_tachyon_manifold[i];

    *out
      << "part 1: " << split_count << std::endl
      << "part 2: " << timelines << std::endl;

    return EXIT_SUCCESS;
 } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
