// nope nope nope nope

// #define DEBUGGING

#ifdef DEBUGGING
#include <iostream>
#define DEBUG for (bool XyZ = true; XyZ; std::cout << std::endl, XyZ = false) std::cout
#else
struct Ignore {};
template <typename T>
Ignore operator<<(const Ignore&, T&&) { return Ignore{}; }
#define DEBUG if (false) Ignore{}
#endif

#include <unordered_map>
#include <vector>

// for use by main() only...
#include <iostream>

using namespace std;

bool is_valid_partition(const vector<int>& nums);

class Solution {
public:
    bool validPartition(vector<int>& nums) {
       return is_valid_partition(nums); 
    }
};

template <typename Ret, typename Arg, typename Func>
auto memoized(Func&& func) {
  std::unordered_map<Arg, Ret> table;
  
  auto wrapper = [&table](Arg arg, auto recur) -> Ret {
    auto found = table.find(arg);
    if (found != table.end()) {
      return *found;
    }
    return table.emplace(arg, func(arg, recur)).first->second;
  };

  return [&](Arg arg) {
    return wrapper(arg, wrapper);
  };
}

bool is_valid_partition(const vector<int>& nums) {
}
