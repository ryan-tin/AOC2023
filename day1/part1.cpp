#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;
// https://adventofcode.com/2023/day/1
// what is the sum of all the calibration values?
// the calibration value is found by combining the first and last digit of a
// line note that the first digit and last digit does not have to be in the
// first/last spot
int main(int argc, char *argv[]) {
  // initialize var to keep track of sum
  // read each line in input
  // find the first and last digit
  // concatenate digit and cast to int
  // add to sum
  // repeat until end of input
  int sum = 0;
  ifstream file;
  file.open("input1.txt");
  // file.open("example1.txt"); // test example
  std::string line;

  if (!file.is_open()) {
    cout << "file is not open" << endl;
    return 0;
  }
  while (file) {
    getline(file, line);
    if (file.eof())
      goto submit; // check for end of file
    std::string::size_type first_sz, second_sz;
    first_sz = line.find_first_of("0123456789");
    second_sz = line.find_last_of("0123456789");
    string combined;
    int increment;
    try {
      combined = string(1, line[first_sz]) +
                 string(1, line[second_sz]); // concatenate numbers e.g., '1' +
                                             // '2' becomes "12"
      increment = stoi(combined);
    } catch (invalid_argument const &ex) {
      perror("stoi");
      exit(EXIT_FAILURE);
    }
    sum += increment;
    increment = 0;
  }
submit:
  cout << to_string(sum) << endl;
  return 0;
}
