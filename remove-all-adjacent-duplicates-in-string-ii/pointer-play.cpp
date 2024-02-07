#include <string>
#include <utility>
#include <vector>

using namespace std;

string remove_duplicates(string input, int run_length);

class Solution {
public:
    string removeDuplicates(string s, int k) {
       return remove_duplicates(std::move(s), k); 
    }
};

string remove_duplicates(string input, int run_length) {
  struct Run {
    char letter;
    int count;
  };
  vector<Run> runs;

  const char* const begin = input.data();
  const char* const end = begin + input.size();
  for (auto p = begin; p != end; ++p) {
    if (runs.empty()) {
      runs.push_back(Run{*p, 1});
    } else if (runs.back().letter != *p) {
      runs.push_back(Run{*p, 1});
    } else if (runs.back().count == run_length - 1) {
      runs.pop_back();
    } else {
      ++runs.back().count;
    }
  }

  // Reuse the input storage for the output.
  std::string& result = input;
  result.resize(0);
  for (const auto [letter, count] : runs) {
    result.insert(result.size(), count, letter);
  }

  return std::move(result);
}
