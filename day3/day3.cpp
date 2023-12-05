#include <fstream>
#include <iostream>
#include <regex>
using namespace std;

#define FILE_1 "input.txt"
#define FILE_2 "input.txt"

typedef struct {
  int start;
  int end;
} p_range;

typedef struct {
  int part_num;
  p_range range;
} part;

// returns the sum of parts in a line that have adjacent symbols
int sum_parts_with_adjacent_symbols(vector<part> *t_parts,
                                    vector<int> *t_minus_1_sym,
                                    vector<int> *t_sym, vector<int> *t_plus_1) {
  vector<int> *s_lines[] = {t_minus_1_sym, t_sym, t_plus_1};
  int subtotal = 0;
  for (part p : *t_parts) {
    for (vector<int> *sl : s_lines) {
      if (sl == nullptr)
        continue;
      for (int s_loc : *sl) {
        if (s_loc >= p.range.start - 1 && s_loc <= p.range.end + 1) {
          subtotal += p.part_num;
          goto next_part;
        }
      }
    }
  next_part:
  }
  return subtotal;
}

int part_1() {
  ifstream file;
  file.open(FILE_1);
  if (!file.is_open()) {
    cout << "file could not be opened" << endl;
    return -1;
  }

  string curr_line;
  sregex_iterator end;
  const regex p_pattern("(\\d+)"); // match part numbers
  vector<part> t_part, c_part;
  const regex s_pattern("([^\\d.\\n])"); // match symbols
  vector<int> t_minus_1_sym, t_sym, c_sym;
  bool first_line = true;
  int sum = 0;
  // (target line is one above the current line)
  while (file) {
    // move symbols
    t_part = c_part;
    t_minus_1_sym = t_sym; // t - 1
    t_sym = c_sym;         // t
    if (file.eof())
      break;
    getline(file, curr_line);
    // store current line symbol locations in vector c_sym (t + 1)
    sregex_iterator s_it(curr_line.begin(), curr_line.end(), s_pattern);
    c_sym.clear();
    while (s_it != end) {
      c_sym.push_back(s_it->position()); // add symbol's position to vector
      ++s_it;
    }
    // store current line part locations/numbers in c_part
    sregex_iterator p_it(curr_line.begin(), curr_line.end(), p_pattern);
    c_part.clear();
    while (p_it != end) {
      p_range range;
      range.start = p_it->position();
      range.end = p_it->position() + p_it->length() - 1;
      part p;
      p.range = range;
      p.part_num = stoi(p_it->str());
      c_part.push_back(p);
      ++p_it;
    }
    // if its the first line, set firstline flag to false and continue to next
    // line
    if (first_line) {
      first_line = false;
      continue;
    }
    int matching_parts = sum_parts_with_adjacent_symbols(
        &t_part, &t_minus_1_sym, &t_sym, &c_sym);
    sum += matching_parts;
  }
  return sum;
}

// returns subtotal of gear ratios of valid gears of the target line
int get_gear_ratio_subtotal(vector<int> *t_gears,
                                    vector<part> *t_minus_1_parts,
                                    vector<part> *t_parts,
                                    vector<part> *c_parts) {
  vector<part> *all_parts[] = {t_minus_1_parts, t_parts, c_parts};
  int subtotal = 0;
  for (int gear : *t_gears) {
    vector<int> adjacent_to_gear;
    for (vector<part> *pl : all_parts) {
      for (part p : *pl) {
        if (gear >= p.range.start - 1 && gear <= p.range.end + 1) {
          adjacent_to_gear.push_back(p.part_num);
        }
      }
    }
    if (adjacent_to_gear.size() == 2) {
      int gear_ratio = adjacent_to_gear[0] * adjacent_to_gear[1];
      subtotal += gear_ratio;
    }
  }
  return subtotal;
}

// find the sum of all gear ratios
// a gear is any * symbol that is adjacent to EXACTLY two parts
// a gear ratio is the result of multiplying those two numbers together
int part_2() {
  ifstream file;
  file.open(FILE_2);
  if (!file.is_open()) {
    cout << "file could not be opened" << endl;
    return -1;
  }

  const regex p_pattern("(\\d+)");
  const regex g_pattern("(\\*)");
  vector<int> t_gears, c_gears;
  vector<part> t_parts, t_minus_1_parts, c_parts;
  sregex_iterator end;
  int sum = 0;

  string line;
  while (file) {
    t_gears = c_gears;
    t_minus_1_parts = t_parts;
    t_parts = c_parts;
    if (file.eof())
      break;
    getline(file, line);
    // for each "*" find all adjacent parts
    sregex_iterator g_it(line.begin(), line.end(), g_pattern);
    c_gears.clear();
    while (g_it != end) {
      c_gears.push_back(g_it->position());
      ++g_it;
    }
    sregex_iterator p_it(line.begin(), line.end(), p_pattern);
    c_parts.clear();
    while (p_it != end) {
      p_range range;
      range.start = p_it->position();
      range.end = p_it->position() + p_it->length() - 1;
      part p;
      p.range = range;
      p.part_num = stoi(p_it->str());
      c_parts.push_back(p);
      ++p_it;
    }
    // add valid gear ratios to sum
    sum += get_gear_ratio_subtotal(&t_gears, &t_minus_1_parts, &t_parts, &c_parts);
  }
  return sum;
}

int main(int argc, char *argv[]) {
  int p1 = part_1();
  cout << "part1: " << p1 << endl;
  int p2 = part_2();
  cout << "part2: " << p2 << endl;
}
