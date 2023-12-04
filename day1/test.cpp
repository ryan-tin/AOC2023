#include <iostream>
#include <regex>
#include <string>

int main() {
  std::string input = "eighthree";

  // Define a regular expression pattern with lookahead assertion
  std::regex pattern(
      "(?=(\\d|one|two|three|four|five|six|seven|eight|nine|zero))");

  // Search for the pattern in the input string
  std::sregex_iterator it(input.begin(), input.end(), pattern);
  std::sregex_iterator end;

  while (it != end) {
    // Print the matched substring
    std::cout << "Match: " << it->str(1) << std::endl;

    // Move to the next match
    ++it;
  }
  return 0;
}

