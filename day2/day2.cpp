#include <fstream>
#include <iostream>
#include <regex>
#include <stdexcept>
using namespace std;

#define FILE_1 "input.txt"
#define FILE_2 "input.txt"

// sum the game numbers that would have been possible if we had the following
// only 12 red cubes, 13 green cubes, and 14 blue cubes
int part_1() {
  ifstream file;
  file.open(FILE_1);
  if (!file.is_open()) {
    cout << "file could not be opened" << endl;
    return -1;
  }

  struct cubes {
    int red;
    int green;
    int blue;
  };
  const cubes LIMIT = {.red = 12, .green = 13, .blue = 14};
  string line;
  int game_num = 0;
  int sum = 0;
  const regex pattern("(\\d*) (blue|green|red)");
  while (file) {
  next_line:
    game_num++;
    getline(file, line);
    if (file.eof())
      break;
    sregex_iterator it(line.begin(), line.end(), pattern);
    sregex_iterator end;

    while (it != end) {
      string color = it->str(2);
      int num_cubes;
      try {
        num_cubes = stoi(it->str(1));
      } catch (invalid_argument &e) {
        cout << e.what() << endl;
      } catch (out_of_range &e) {
        cout << e.what() << endl;
      }
      if (color == "red") {
        if (num_cubes > LIMIT.red)
          goto next_line;
      } else if (color == "green") {
        if (num_cubes > LIMIT.green)
          goto next_line;
      } else {
        if (num_cubes > LIMIT.blue)
          goto next_line;
      }
      ++it;
    }
    sum += game_num;
  }
  return sum;
}

int part_2() {
  ifstream file;
  file.open(FILE_2);
  if (!file.is_open()) {
    cout << "file could not be opened" << endl;
    return -1;
  }
  struct rgb_min {
    int red = 0;
    int green = 0;
    int blue = 0;
  };
  const regex pattern("(\\d*) (red|green|blue)");
  int sum = 0;
  string line;
  while (file) {
    getline(file, line);
    if (file.eof())
      break;
    rgb_min min = {0, 0, 0};
    sregex_iterator it(line.begin(), line.end(), pattern);
    sregex_iterator end;
    while (it != end) {
      string color = it->str(2);
      int num_cubes;
      try {
        num_cubes = stoi(it->str(1));
      } catch (invalid_argument &e) {
        cout << e.what() << endl;
      } catch (out_of_range &e) {
        cout << e.what() << endl;
      }
      if (color == "red") {
        if (min.red < num_cubes) {
          min.red = num_cubes;
        }
      } else if (color == "green") {
        if (min.green < num_cubes) {
          min.green = num_cubes;
        }
      } else {
        if (min.blue < num_cubes) {
          min.blue = num_cubes;
        }
      }
      ++it;
    }
    int power = min.red * min.green * min.blue;
    sum += power;
  }
  return sum;
}

int main(int argc, char *argv[]) {
  int p1 = part_1();
  cout << "part1: " << p1 << endl;
  int p2 = part_2();
  cout << "part2: " << p2 << endl;
}
