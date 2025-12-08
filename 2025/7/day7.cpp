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
    auto tachyon_manifold = std::make_unique<bool[]>(width);
    auto pos = line.find('S');
    assert(pos != std::string::npos);
    tachyon_manifold[pos] = true;

    int split_count{};

    while(std::getline(fin, line)) {
      int splitter_pos{};
      for(;;) {
        splitter_pos = line.find('^', splitter_pos);
        if (splitter_pos == std::string::npos) {
          break;
        } else if (tachyon_manifold[splitter_pos]) {
          split_count++;
          tachyon_manifold[splitter_pos] = false;
          tachyon_manifold[splitter_pos - 1] = true;
          tachyon_manifold[splitter_pos + 1] = true;
        }
        splitter_pos++;
      }
    }

    *out
      <<  split_count << std::endl;

    return EXIT_SUCCESS;
 } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
