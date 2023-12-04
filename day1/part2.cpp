#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <sys/_types/_size_t.h>

struct match_position {
  int num; // integer representation of the matched number
};

struct first_and_last {
  match_position first;
  match_position last;
};

// converts numbers in text format integer format
// inputs of "zero" returns 0, "one" returns 1, and so on.
// inputs of "0" returns 0, "1" returns 1, and so on.
int string_to_int(std::string text) {
  if (text.length() == 1) {
    return stoi(text);
  }
  const std::string cases[] = {"zero", "one", "two",   "three", "four",
                               "five", "six", "seven", "eight", "nine"};
  const size_t length = sizeof(cases) / sizeof(cases[0]);
  for (int i = 0; i < length; i++) {
    if (text == cases[i])
      return i;
  }
  return -1;
}

// returns the first and last indexes of text-matched numbers and their
// integer representation
// e.g., if the input string is "two1nine", then
first_and_last match_numbers(std::string text) {
  first_and_last positions = {{-1}, {-1}};
  // match for any of the following numbers
  // the "positive lookahead" allows for matching both "eight" and "three" in
  // "eighthree"
  const std::regex pattern(
      "(?=(\\d|one|two|three|four|five|six|seven|eight|nine|zero))");

  std::sregex_iterator it(text.begin(), text.end(), pattern);
  std::sregex_iterator end;
  bool flag = true;

  while (it != end) {
    std::smatch match = *it;
    // store first match
    if (flag) {
      positions.first.num =
          string_to_int(match.str(1)); // HACK: in order to match overlaps
      flag = false;
    }
    // store last match
    positions.last.num = string_to_int(match.str(1)); // HACK:
    ++it; // move iterator to next match
  }
  return positions;
}

// same problem as part 1 but need to match letters
int main(int argc, char *argv[]) {
  std::ifstream file;
  file.open("input1.txt");
  std::string line;
  int sum = 0;

  if (!file.is_open()) {
    std::cout << "file is not open" << std::endl;
    return 0;
  }

  while (file) {
    getline(file, line);
    if (file.eof()) {
      goto submit;
    }
    first_and_last match = match_numbers(line);
    // std::cout << line << "," << match.first.num << "," << match.last.num
    //           << std::endl;
    int increment;
    std::string combined;
    try {
      // create combined string and convert to integer
      combined =
          std::to_string(match.first.num) + std::to_string(match.last.num);
      increment = stoi(combined);
      // std::cout << line << "," << combined << "," << increment << ",";
      sum += increment;
      increment = 0;
    } catch (std::invalid_argument const &ex) {
      perror("stoi");
      exit(EXIT_FAILURE);
    }
  }
submit:
  std::cout << std::to_string(sum) << std::endl;
  return 0;
}
