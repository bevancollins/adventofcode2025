#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>

struct IngredientRange {
  long long begin{};
  long long end{};
};

bool is_fresh(long long ingredient, const std::vector<IngredientRange>& fresh_ingrediant_ranges) {
  for (const auto& range : fresh_ingrediant_ranges)
    if (ingredient >= range.begin && ingredient <= range.end)
      return true;
  return false;
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

    enum ReadMode {
      ReadingRanges = 0,
      ReadingIngredients
    };

    std::vector<IngredientRange> fresh_ingredient_ranges;
    int fresh_count{};
    ReadMode read_mode{ReadingRanges};
    std::string line;
    while (std::getline(fin, line)) {
      if (read_mode == ReadingRanges) {
        if (line.empty()) {
          read_mode = ReadingIngredients;
          continue;
        }

        auto pos = line.find('-');
        assert(pos != std::string::npos);

        auto range_begin = std::stoll(line.substr(0, pos));
        auto range_end = std::stoll(line.substr(pos + 1));
        fresh_ingredient_ranges.emplace_back(range_begin, range_end);
      } else {
        auto ingredient = std::stoll(line);
        if (is_fresh(ingredient, fresh_ingredient_ranges))
          fresh_count++;
      }
    }

    *out << fresh_count << std::endl;

    return EXIT_SUCCESS;
 } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
