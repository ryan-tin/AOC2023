#include <fstream>
#include <iostream>
#include <regex>
#include <unordered_set>
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

  const regex pattern("\\d+");
  sregex_iterator end;
  int sum = 0;
  string line;
  while (file) {
    int win_count = 0;
    getline(file, line);
    if (file.eof())
      break;
    string winning_nums =
        line.substr(line.find(":") + 1, line.find("|") - line.find(":") - 1);
    string our_nums = line.substr(line.find("|") + 1, line.length());
    // put all winning winning numbers in an unordered set
    unordered_set<int> w_nums_set;
    sregex_iterator winning_it(winning_nums.begin(), winning_nums.end(),
                               pattern);
    while (winning_it != end) {
      w_nums_set.insert(stoi(winning_it->str()));
      ++winning_it;
    }
    sregex_iterator our_it(our_nums.begin(), our_nums.end(), pattern);
    while (our_it != end) {
      if (w_nums_set.find(stoi(our_it->str())) != w_nums_set.end())
        win_count++;
      ++our_it;
    }
    if (win_count > 0) {
      sum += pow(2, win_count - 1);
    }
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

  string line;
  while (file) {
    getline(file, line);
    if (file.eof())
      break;
  }

  return 0;
}

int main(int argc, char *argv[]) {
  int p1 = part_1();
  cout << "p1: " << p1 << endl;
  // int p2 = part_2();
}
