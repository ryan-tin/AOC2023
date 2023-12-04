#include <iostream>
#include <fstream>
using namespace std;

#define FILE_1 "input.txt"
#define FILE_2 "input.txt"

int part_1() {
  ifstream file;
  file.open(FILE_1);
  if (!file.is_open()) {
    cout << "file could not be opened" << endl;
    return -1;
  }

  string line;
  while (file) {
    getline(file, line);
    if (file.eof()) break;
  }

  return 0;
}

int part_2() {
  ifstream file;
  file.open(FILE_1);
  if (!file.is_open()) {
    cout << "file could not be opened" << endl;
    return -1;
  }

  string line;
  while (file) {
    getline(file, line);
    if (file.eof()) break;
  }

  return 0;
}

int main(int argc, char* argv[]) {
  int p1 = part_1();
  // int p2 = part_2();
}
