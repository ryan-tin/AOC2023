#include <fstream>
#include <iostream>
#include <map>
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
  const regex pattern("(\\d+)");
  sregex_iterator end;
  // keep track of how many of each card we have
  map<int, int> num_of_cards; // key is the card number
  num_of_cards.emplace(1, 1);
  int total_cards = 0;
  string line;
  while (file) {
    getline(file, line);
    if (file.eof())
      break;
    int card_num = 0; 
    smatch card_num_match;
    string card_substr = line.substr(0, line.find(":"));
    if (regex_search(card_substr, card_num_match, pattern)) {
      card_num = stoi(card_num_match[0]);
    }
    string winning_nums =
        line.substr(line.find(":") + 1, line.find("|") - line.find(":") - 1);
    string our_nums =
        line.substr(line.find("|") + 1, line.length() - line.find("|") - 1);
    unordered_set<int> win_set;
    sregex_iterator win_it(winning_nums.begin(), winning_nums.end(), pattern);
    while (win_it != end) {
      win_set.insert(stoi(win_it->str()));
      ++win_it;
    }
    // check how many matches for this line
    sregex_iterator our_it(our_nums.begin(), our_nums.end(), pattern);
    int win_count = 0;
    while (our_it != end) {
      if (win_set.find(stoi(our_it->str())) != win_set.end())
        win_count++;
      ++our_it;
    }
    // find num of copies of the current card we have so far
    int copies;
    if (num_of_cards.find(card_num) == num_of_cards.end()) {
      copies = 1;
    } else {
      copies = num_of_cards.at(card_num);
    }
    // add copies of future cards from this card's wins
    while (win_count > 0) {
      if (num_of_cards.find(card_num + win_count) == num_of_cards.end()) {
        num_of_cards.emplace(card_num + win_count, 1);
      }
      num_of_cards[card_num + win_count] += copies;
      --win_count;
    }
    // special case where no wins & no copies
    if (num_of_cards.find(card_num) == num_of_cards.end()) {
      num_of_cards.emplace(card_num, 1);
    }
    total_cards += num_of_cards.at(card_num);
  }
  return total_cards;
}

int main(int argc, char *argv[]) {
  // int p1 = part_1();
  // cout << "p1: " << p1 << endl;
  int p2 = part_2();
  cout << "p2: " << p2 << endl;
}
